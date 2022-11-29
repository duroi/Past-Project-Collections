
from modelPUF import ChallengeResponseSet
from modelPUF import pufModel

import numpy as np
from numpy.core.fromnumeric import size
import matplotlib.pyplot as plt


crpData = ChallengeResponseSet('cr_100000.npz', 'challenge', 'response')

p = .50

puf = pufModel(crpData)

crpData.train_test_split(p)
puf.train(crpData)
puf.test(crpData)


# Run through training 
#p = 0.10
#i = 0
#while p < 1.0:
#    while i < 3: 
#        crpData.train_test_split(p)
#        puf.train(crpData)
#        puf.test(crpData)
#        i= i+1
#    p = p +.2

