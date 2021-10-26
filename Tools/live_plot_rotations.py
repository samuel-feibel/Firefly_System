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
Euler = []

r2d = 180/np.pi

plt.ion()

figure = plt.figure() 
ax = plt.axes(projection='3d')

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

        q1 = pack.stateEstimator.xhat[0]
        q2 = pack.stateEstimator.xhat[1]
        q3 = pack.stateEstimator.xhat[2]
        q4 = pack.stateEstimator.xhat[3]

        phi = np.arctan2(2*(q2*q3+q1*q4),1-2*(q1**2+q2**2))*r2d
        temp = 2*(q1*q3+q4*q2)
        psi = np.arctan2(2*(q1*q2+q3*q4),1-2*(q2**2+q3**2))*r2d

        if temp > 1:
            temp = 1
        if temp < -1:
            temp = -1
        theta = np.arcsin(temp)*r2d

        Euler = [phi,theta,psi]
        print(Euler)
        x.append(pack.mcTime)

        ex = [q1**2-q2**2-q3**2+q4**2, 2*(q2*q1+q3*q4), 2*(q3*q1-q2*q4)]
        ey = [2*(q1*q2 - q3*q4), -q1**2 + q2**2 - q3**2 + q4**2,2*(q2*q3 + q1*q4)]
        ez = [2*(q1*q3 + q2*q4), 2*(q2*q3 - q1*q4), -q1**2 - q2**2 + q3**2 + q4**2]

        ax.clear()
        ax.plot3D([0, ex[0]], [0, ex[1]], [0, ex[2]], 'r', label = "x")
        ax.plot3D([0, ey[0]], [0, ey[1]], [0, ey[2]], 'g', label = "y")
        ax.plot3D([0, ez[0]], [0, ez[1]], [0, ez[2]], 'b', label = "z")
        ax.plot3D([0, 1], [0, 0], [0, 0], 'r--')
        ax.plot3D([0, 0], [0, 1], [0, 0], 'g--')
        ax.plot3D([0, 0], [0, 0], [0, 1], 'b--')
        ax.legend()
        ax.set_aspect('auto')

        figure.canvas.draw()
        
        figure.canvas.flush_events()

        # print(time.time() - t)
        # t = time.time()
        # time.sleep(0.1)