import numpy as np
import time
import matplotlib.pyplot as plt
import serial
import sys

from google.protobuf.message import DecodeError

import autopilot_pb2
import base64

pack = autopilot_pb2.PlaneBuf()

#initialize serial port
ser = serial.Serial()
ser.port = 'COM3' #Arduino serial port
ser.baudrate = 115200
ser.timeout = 0 #specify timeout when using readline()
ser.open()
if ser.is_open==True:
	print("\nAll right, serial port now open. Configuration:\n")
	print(ser, "\n") #print serial parameters
    
x = []
y0 = []
y1 = []
y2 = []

plt.ion()

xTest = np.linspace(0, 10, 100)
yTest = np.cos(xTest)

figure, axs = plt.subplots(2, 2,figsize=(8,6))
axs[0,0].plot(xTest, yTest)

t = time.time()
# do stuff

while True:
    c = ser.readline()
    
    if c:
        # print(c)
        try:
            pack.ParseFromString(base64.decodebytes(c))
        except DecodeError:
            ...

        # x.append(pack.mcTime)
        # y0.append(pack.sensors.IMU.acc[0]) 
        axs[0,0].clear()
        axs[0,0].plot(xTest, yTest)
        axs[1,1].clear()
        axs[1,1].plot(xTest, yTest)
        axs[1,0].clear()
        axs[1,0].plot(xTest, yTest)
        axs[0,1].clear()
        axs[0,1].plot(xTest, yTest)


        
        figure.canvas.draw()
        
        figure.canvas.flush_events()

        print(time.time() - t)
        t = time.time()
        # time.sleep(0.1)