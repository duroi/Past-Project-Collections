import numpy as np
from numpy.core.fromnumeric import size
import serial


#Need double \\ to find file path for some reason 
loadResponse = np.load('C:\\Users\\duroi\\Documents\\Lab-02\\Python\\resp_100000.npz')
loadChallenge = np.load('C:\\Users\\duroi\\Documents\\Lab-02\\Python\\challenges_100000.npz')

#loadcr = np.load('C:\\Users\\duroi\\Documents\\Lab-02\\Python\\cr_10000.npz')

#print('Challenges array :',loadcr['challenge'['challenge']])
#print('Responses array:',loadcr['response'])


print('Challenges array :',loadChallenge['challenge'])
print('Responses array:',loadResponse['response'])

#print('Size of Challenges :',size(loadcr['challenge']))
#print('Size of Reponses :',size(loadcr['response']))

print('Size of Challenges :',size(loadChallenge['challenge']))
print('Size of Reponses :',size(loadResponse['response']))

np.savez_compressed('cr_100000.npz', challenge=loadChallenge['challenge'], response=loadResponse['response'])
