
import numpy as np
import random
import argparse
import tensorflow as tf


from tensorflow.keras.layers import Dense, Dropout, Input
from tensorflow.keras.models import Sequential

# can uncomment this if you are using an RTX GPU
# physical_devices = tf.config.list_physical_devices('GPU') 
# tf.config.experimental.set_memory_growth(physical_devices[0], True)

def main():
    parser = argparse.ArgumentParser(description='CLI Interface for building/training a neural network to model a PUF from raw data.')
    parser.add_argument('-i','--inputfile', help='path/name of file to read training data from', required=True)
    parser.add_argument('-p','--percentdata', help='percentage of supplied training data to use for testing', required=True)

    args  = vars(parser.parse_args())
    ifile = args['inputfile']
    p     = float(args['percentdata'])

    crpData = ChallengeResponseSet(filename=ifile)
    # crpData = ChallengeResponseSet(filename=r'F:\Research\USF-HHL\Labs\02-RO_PUF_ML\20000_64.crps')

    puf = pufModel(crpData)
    crpData.train_test_split(p)
    puf.train(crpData)
    puf.test(crpData)

    # can save the weights to a file
    # puf.save_weights('pufModel-16bit.h5')


class ChallengeResponseSet:
    """
        A set of challenges and corresponding responses. 
        Provides a neat interface with useful functions to work with your CRP data.

        Was adapted from a module within the Pypuf repository: https://github.com/nils-wisiol/pypuf
    """

    def __init__(self, filename=None, challenges=None, responses=None):
        """
        Create a set of challenges and corresponding responses. Note that the order of the
        challenges and responses parameter is relevant.
        :param challenges: List of challenges
        :param responses: List of responses, ordered accordingly
        """
        if filename is not None:
            self.challenges, self.responses = self.read_crps(filename)
        elif challenges is not None and responses is not None:
            self.challenges, self.responses = challenges, responses

        self.train, self.valid, self.test = [None] * 3
        assert len(self.challenges) == len(self.responses)
        self.N = len(self.challenges)
        self.clength = self.challenges.shape[1]


    def read_crps(self, filename):
        """ Reads a file generated by gen_crps.py and returns a pypuf CRP dataset

        Args:
            filename (str): path-to/filename 

        Returns:
            pypuf.tools.ChallengeResponseSet()
        """
        if ".npz" in filename:
            data = np.load(filename)
            n = len(data['challenge'])
            challengeSize = len(data['challenge'][0]) * 4
            numPUFs = len(data['response'][0]) * 4

            # read into np array 
            C = np.array([int(s, 16) for s in data['challenge']], dtype=np.uint64)
            R = np.array([int(s, 16) for s in data['response']], dtype=np.uint16)

            # convert to binary representation
            challenges = np.array(((C[:, None] & (1 << np.arange(challengeSize, dtype=np.uint64)[::-1])) > 0), dtype=int)
            responses = np.array(((R[:, None] & (1 << np.arange(numPUFs, dtype=np.uint16)[::-1]) > 0)), dtype=int)

        else:
            with open(filename, mode="r") as tFile:

                # split binary string, and separate challenges/responses
                # it is hard-coded to take the first 64 values as challenge, and the rest as the response 
                data = np.array([[int(c) for c in line if c != '\n'] for line in tFile.read().splitlines()])
                challenges = data[:, :64]
                responses  = data[:, 64:]
                n = len(challenges)
        
        # use heuristic to select best PUF responses (closest to 50/50 ones and zeros)
        responsesHeuristic = np.abs((np.sum(responses, axis=0) / n) - 0.5)
        test = np.argmin(responsesHeuristic)
        
        # get "best" responses
        bestPUFResponses = responses[:, test]

        # convert CRPs to 1/-1
        bestPUFResponses[bestPUFResponses == 1] = -1
        bestPUFResponses[bestPUFResponses == 0] = 1 
        challenges[challenges == 1] = -1
        challenges[challenges == 0] = 1

        # convert challenges to parity/delay vectors
        challenges = np.cumprod(challenges, axis=1, dtype=np.int8)

        # add parity bit, is this still necessary? no, just use parity vector
        # challenges = np.hstack([challenges, parity])
        return challenges.astype(float), bestPUFResponses.astype(float)

    def random_subset(self, N):
        """
        Gives a random subset of this challenge response set.
        :param N: Either a relative (to the total number) or absolute number of challenges.
        :return: A random subset samples from this challenge response set.
        """
        if N < 1:
            N = int(self.N * N)
        return self.subset(random.sample(range(self.N), N))

    def train_test_split(self, pTrain):
        """ Performs a train test split on the data using the percentage of data for training as an argument

        Args:
            pTrain (float): percentage of data to use for training
        """
        N = int(pTrain * self.N)
        inds = [*range(self.N)]
        random.shuffle(inds)

        self.train = self.subset(inds[:N])
        self.test = self.subset(inds[N:])

        return self.train, self.test

    def train_valid_test_split(self, pTrain, pValid):
        """ Performs a train test split on the data using the percentage of data for training as an argument

        Args:
            pTrain (float): percentage of data to use for training
        """
        nTrain = int(pTrain * self.N)
        nValid = nTrain + int(pValid * self.N)
        inds = [*range(self.N)]
        random.shuffle(inds)

        self.train = self.subset(inds[:nTrain])
        self.valid = self.subset(inds[nTrain:nValid])
        self.test = self.subset(inds[nValid:])

        return self.train, self.valid, self.test        

    def block_subset(self, i, total):
        """
        Gives the i-th block of this challenge response set.
        :param i: Index of the block that is to be returned.
        :param total: Total number of blocks.
        :return: A challenge response set.
        """
        return self.subset(slice(
            int(i / total * self.N),
            int((i + 1) / total * self.N)
        ))

    def subset(self, subset_slice):
        """
        Gives the subset of this challenge response set defined by the slice given.
        :param subset_slice: A python array slice
        :return: A challenge response set defined accordingly
        """
        return ChallengeResponseSet(
            challenges=self.challenges[subset_slice],
            responses=self.responses[subset_slice]
        )

class pufModel:
    """
        A class which interfaces with Tensorflow/Keras and creates a DNN model to model an APUF.
    """

    @staticmethod
    def loss(y_true: tf.Tensor, y_pred: tf.Tensor) -> tf.Tensor:
        return tf.keras.losses.binary_crossentropy(.5 - .5 * y_true, .5 - .5 * y_pred)

    @staticmethod
    def accuracy(y_true: tf.Tensor, y_pred: tf.Tensor) -> tf.Tensor:
        return tf.keras.metrics.binary_accuracy(.5 - .5 * y_true, .5 - .5 * y_pred)

    def __init__(self, crpData=None):
        self.crpData = crpData
        self.clength = crpData.clength
        model = Sequential()
        model.add(Input(shape=(self.clength,)))
        model.add(Dense(2, activation='relu'))
        # model.add(Dropout(0.5))
        # model.add(BatchNormalization())
        # model.add(Dense(32, activation='relu'))
        # model.add(Dropout(0.5))
        # model.add(BatchNormalization())
        # model.add(Dense(self.clength // 6, activation='relu'))
        # model.add(Dropout(0.25))
        # model.add(BatchNormalization())
        model.add(Dense(1, activation='tanh'))
        # model.compile(loss=tf.keras.losses.binary_crossentropy, optimizer=tf.keras.optimizers.Adam(), metrics=['accuracy'])
        model.compile(loss=self.loss, optimizer=tf.keras.optimizers.Adam(), metrics=[self.accuracy])

        self.model = model
        self.initial_weights = self.model.get_weights()

    def reset_model(self):
        self.model.set_weights(self.initial_weights)

    def train(self, crps):
        trainX = crps.train.challenges
        trainY = crps.train.responses

        self.model.fit(
            trainX, trainY,
            # validation_data=(self._valid.challenges, self._valid.responses),
            batch_size=1000, epochs=100
        )

    def test(self, crps):
        testX = crps.test.challenges
        testY = crps.test.responses
        self.model.evaluate(testX, testY)
        pred_y = self.model.predict_on_batch(testX).reshape(-1)  # pred_y[pred_y >= 0.5] = 1
        # pred_y[pred_y < 0.5] = 0
        # pred_y[pred_y >= 0.5] = 1
        acc = self.accuracy(testY, pred_y)
        
        # acc = np.mean(pred_y == testY)
        print(f"Accuracy on {len(pred_y)} unseen challenges is: {acc}")

    def save_weights(self, filename):
        self.model.save_weights(filename)

    def load_weights(self, filename):
        self.model.load_weights(filename)


if __name__ == '__main__':
    main()