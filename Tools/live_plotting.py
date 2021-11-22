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
    
t = []
roll = []
pitch = []
yaw = []
pos_N = []
pos_E = []
pos_D = []
vel_N = []
vel_E = []
vel_D = []
mag_bias_X = []
mag_bias_Y = []
mag_bias_Z = []

r2d = 180/np.pi

plt.ion()

figure, axs = plt.subplots(2,3,figsize=(12,8))

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

        t.append(pack.mcTime)
        q1 = pack.stateEstimator.xhat[0]
        q2 = pack.stateEstimator.xhat[1]
        q3 = pack.stateEstimator.xhat[2]
        q4 = pack.stateEstimator.xhat[3]
        pos_N.append(pack.stateEstimator.xhat[4])
        pos_E.append(pack.stateEstimator.xhat[5])
        pos_D.append(pack.stateEstimator.xhat[6])
        vel_N.append(pack.stateEstimator.xhat[7])
        vel_E.append(pack.stateEstimator.xhat[8])
        vel_D.append(pack.stateEstimator.xhat[9])
        mag_bias_X.append(pack.stateEstimator.xhat[10])
        mag_bias_Y.append(pack.stateEstimator.xhat[11])
        mag_bias_Z.append(pack.stateEstimator.xhat[12])



        # Append Angles
        roll.append(np.arctan2(2*(q2*q3+q1*q4),1-2*(q1**2+q2**2))*r2d)
        temp = 2*(q1*q3+q4*q2)
        yaw.append(np.arctan2(2*(q1*q2+q3*q4),1-2*(q2**2+q3**2))*r2d)

        if temp > 1:
            temp = 1
        if temp < -1:
            temp = -1
        pitch.append(np.arcsin(temp)*r2d)
         
        if len(t) > recentWindow:
            t.pop(0)
            pos_D.pop(0)
            roll.pop(0)
            pitch.pop(0)
            yaw.pop(0)
            vel_N.pop(0)
            vel_E.pop(0)
            vel_D.pop(0)
            mag_bias_X.pop(0)
            mag_bias_Y.pop(0)
            mag_bias_Z.pop(0)

        ## Plot ##

        # Angles
        axs[0,0].clear()
        axs[0,0].plot(t, roll, 'r', label = "Roll")
        axs[0,0].plot(t, pitch, 'g', label = "Pitch")
        axs[0,0].plot(t, yaw, 'b', label = "Yaw")
        axs[0,0].legend()
        axs[0,0].set_title('Attitude')

        # Position
        axs[0,1].clear()
        axs[0,1].plot(pos_E, pos_N)
        axs[0,1].axis('equal')
        axs[0,1].set_title('Position')

        # Height
        axs[0,2].clear()
        axs[0,2].plot(t,pos_D)
        axs[0,2].set_title('Altitude')

        # Velocity
        axs[1,0].clear()
        axs[1,0].plot(t, vel_N, 'r', label = "N")
        axs[1,0].plot(t, vel_E, 'g', label = "E")
        axs[1,0].plot(t, vel_D, 'b', label = "D")
        axs[1,0].legend()
        axs[1,0].set_title('Velocity')

        # Bias
        axs[1,1].clear()
        axs[1,1].plot(t, mag_bias_X, 'r', label = "X")
        axs[1,1].plot(t, mag_bias_Y, 'g', label = "Y")
        axs[1,1].plot(t, mag_bias_Z, 'b', label = "Z")
        axs[1,1].legend()
        axs[1,1].set_title('Mag Bias')
        
        figure.canvas.draw()
        
        figure.canvas.flush_events()

