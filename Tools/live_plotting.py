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
h0 = []
h1 = []
h2 = []
bias = [0,0,0]
magVec0 = [0,0,0]

r2d = 180/np.pi

plt.ion()

figure, axs = plt.subplots(figsize=(8,6))

t = time.time()
# do stuff
recentWindow = 20

while True:
    c = ser.readline()
    
    if c:
        # print(c)
        try:
            pack.ParseFromString(base64.decodebytes(c))
        except DecodeError:
            ...

        # Euler = [phi;theta;psi];
        vec = np.array(pack.sensors.IMU.mag)
        print(np.linalg.norm(vec))
        x.append(pack.mcTime)
        y0.append(pack.sensors.GPS.position_NED[0])
        y1.append(pack.sensors.GPS.position_NED[1])
        y2.append(pack.sensors.GPS.position_NED[2])
        # h0.append(pack.stateEstimator.xhat[4])
        # h1.append(pack.stateEstimator.xhat[5])
        # h2.append(pack.stateEstimator.xhat[6])
         
        axs.clear()
        axs.plot(x, y0, 'r', label = "x")
        axs.plot(x, y1, 'g', label = "y")
        axs.plot(x, y2, 'b', label = "z")
        # axs.plot(x, h0, 'r--')
        # axs.plot(x, h1, 'g--')
        # axs.plot(x, h2, 'b--')
        # axs.legend()

        # ## Save Stuff
        # bias[0] = (max(y0)+min(y0))/2
        # bias[1] = (max(y1)+min(y1))/2
        # bias[2] = (max(y2)+min(y2))/2

        # # print(bias)

        # magVec0[0] = np.mean(y0[len(y0)-recentWindow:len(y0)])
        # magVec0[1] = np.mean(y1[len(y1)-recentWindow:len(y1)])
        # magVec0[2] = np.mean(y2[len(y2)-recentWindow:len(y2)])
        # print(magVec0)
        
        figure.canvas.draw()
        
        figure.canvas.flush_events()

        # print(time.time() - t)
        t = time.time()
        # time.sleep(0.1)