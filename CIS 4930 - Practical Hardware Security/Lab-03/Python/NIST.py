import random
import numpy as np
import time
import copy
import argparse
from tests import *

def random_matrix():
    return [random.getrandbits(32) for row in range(32)]

def random_matrices(count):
    return [random_matrix() for _ in range(count)]

class TRNGtester:
    """
        Class container for the NIST SP 800-22r1a specification for random number generator (RNG) testing.

        The test suite contains 15 total tests, which are ran in their order of reference in the NIST documentation.

    """


    def __init__(self, binaryFile=None, bits=-1, binformat='bytes'):
        """ Initializer for TRNGTester class. Calls parse function accordingly.

        Args:
            binaryFile (str): Filename where the random data to test is.
            bits (int, optional): . Defaults to -1.
            binformat (str, optional): [description]. Defaults to 'bytes'.
        """

        if binaryFile != None:
            self.binary = self.BinaryData(binaryFile, bits=bits, binformat=binformat)
        else:
            self.binary = None

    class BinaryData:
        """ Class that holds arrays of packed/unpacked binary data.
            Constructor parses bin
        """
        def __init__(self, filename, bits=-1, binformat='bytes'):
            if filename == None:
                self.unpacked = None
                self.packed = None
                self.n = 0
                return

            # if filename.endswith(".txt") or binformat != 'bytes': 
            #     lines = open(filename).readlines()
            #     rawData = ''.join(lines).replace('\n','').replace(' ','').replace('\t','')
            #     n = bits // 8 if bits != -1 else len(rawData) // 8
            #     self.packed = np.array([int(rawData[i*8:(i+1)*8], 2) for i in range(n)],dtype=np.uint8)
            # else:
            self.packed = np.fromfile(filename, dtype=np.uint8, count=bits//8)

            self.unpacked = np.unpackbits(self.packed)
            self.n = len(self.packed) * 8

    def read_binary(self, filename, bits=-1):
        """ Parse a file containing raw bytes. Calls the subclass for parsing binary.

        Args:
            filename : path to the file containing binary to test.
            bits (int, optional): Number of bits to parse. Defaults to -1 (parse all bits).

        Returns:
            BinaryData: class that holds arrays of packed/unpacked binary data
        """

        return self.BinaryData(filename, bits=bits)

    def load_int_array(self, data):
        """ Takes data in the form of an integer array, and sets the class variables accordingly.
            Use this function to manually change the binary sequence under test, and supply your data as an np.uint8 array.

        Args:
            data (np.array(dtype=np.uint8)): Binary sequence to test, passed as an integer arrayl.
        """
        bd = self.BinaryData(None)
        bd.packed = data
        bd.unpacked = np.unpackedbits(bd.packed)
        bd.n = len(bd.packed) * 8

        self.binary = bd

    def run_nist_tests(self, verbose=2):
        nistFuncs = [
                    monobit_test, frequency_within_block_test, runs_test, longest_run_within_block_test,
                    binary_matrix_rank_test, discrete_fourier_transform_test, 
                    non_overlapping_template_matching_test,
                    overlapping_template_matching_test, maurers_universal_test, 
                    linear_complexity_test,
                    serial_test, approximate_entropy_test, cumulative_sums_test, random_excursion_test, random_excursion_variant_test
        ]

        allstart = time.time()

        pvalues = []

        # iterate through the nist tests, run each one and gather the results
        for func in nistFuncs:
            start = time.time()
            if verbose == 2:
                print("Starting: {}".format(func.__name__))

            try:
                ret = func(copy.deepcopy(self.binary))
                end = time.time() - start
                
                if verbose == 2:
                    print("\t\tResults (p-value(s), Pass/Fail) = \n\t\t\t{}".format(ret))
                    print("Test completed in {}s".format(end))
                    print("\n")
                if len(ret) == 2 and type(ret[0]) != tuple:
                    ps = ret[0]
                else:
                    ps = [p for p,s in ret]

                pvalues.append(ps)
                    
            except Exception as e:
                print(f"Ran into exception: {repr(e)}")
                print("Error running: {}\nVerify that you have at least 10000 bits of data.".format(func.__name__))

        if verbose == 2:
            print("Completed all tests in: {}s".format(time.time() - allstart))

        return pvalues
