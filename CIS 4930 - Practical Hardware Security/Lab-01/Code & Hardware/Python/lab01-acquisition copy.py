# Derek Caprio
# Igli Duro

import numpy as np
from numpy.core.fromnumeric import size
import serial
 
# Opern serial connection to FPGA
ser  = serial.Serial("COM4", 115200)
#ser.open()
 
 

# Open challenges
challenges_hex = np.load('C:\\Users\\duroi\\Documents\\Lab-01\\Python\\challenges_5000.npz')
 

## Debugging - examine challenges file
#print(challenges_hex.files)
#print(challenges_hex['challenge'])
#print(" ")
#print(challenges_hex['challenge'][1])
#print(type(challenges_hex['challenge'][1]))
##print(type(str(challenges_hex['challenge'][1])))
#s = str(challenges_hex['challenge'][1])
#print(s, type(s))
 

# convert hex challenges to binary challenges
challenges_bits = []
for i in np.nditer(challenges_hex['challenge']):
    #challenges_bits.append(bytes.fromhex(str(i)))
    #challenges_bits.append(i)
    challenges_bits.append(bytearray.fromhex(str(i)))
 
#challenges_bits = bytearray(challenges_bits)
 
# DEBUGGING
#print(challenges_bits[1])
#tmp = str(challenges_bits[1])
#print(tmp)
#ser.write(tmp)
response_bits_a = []
response_bits_b = []
response_bits_c = []

#count = 0
print(size(response_bits_a))
for i in challenges_bits:
 
    ser.write(i)
    
    response = ser.read(2)
    #print(count)
    response_bits_a.append(response)
    #count = count + 1

print(size(response_bits_a))

#count = 0
for i in challenges_bits:

    ser.write(i)

    response = ser.read(2)

    response_bits_b.append(response)
    #print(count)
    #count = count + 1

#count = 0
for i in challenges_bits:

    ser.write(i)

    response = ser.read(2)

    response_bits_c.append(response)
    #print(count)
    #count = count + 1


# print("response bits: ", response_bits)


response_np_a = np.array(response_bits_a)
response_np_b = np.array(response_bits_a)
response_np_c = np.array(response_bits_a)

np.savez_compressed('resp_a', response_np_a, 'RESPONSE')
np.savez_compressed('resp_b', response_np_b, 'RESPONSE')
np.savez_compressed('resp_c', response_np_c, 'RESPONSE')


## Debugging
#print("-----")
#print(challenges_bits)
 

## send challenges to PUF and get responses
#response_bits = []
#for i in challenges_bits:
#    ser.write(challenges_bits[i])
#    response_bits.append(ser.read(1))
 
 
## DEBUGGING
#print(response_bits)
 
## close serial connection
#ser.close()