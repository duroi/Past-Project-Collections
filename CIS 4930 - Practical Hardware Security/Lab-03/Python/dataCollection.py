import numpy as np
from numpy.core.fromnumeric import size
import serial
from serial.serialutil import Timeout
 
# Opern serial connection to FPGA
ser  = serial.Serial("COM4", 115200)
#ser.open()
 


input = bytearray(125)
#f = open("RO_1M.bin", "wb")
f = open("GARO_1M.bin", "wb")

i = 0
while i < 1000:
    ser.write(input)
    i = i + 1
    print(i)

f.write(ser.read(125000))

print("1 million done...")
f.close()

#f = open("RO_10M.bin", "wb")
f = open("GARO_10M.bin", "wb")


i = 0
while i < 10000:
    ser.write(input)
    i = i + 1
    print(i)

f.write(ser.read(1250000))

f.close()

print("10 million done...")