import matplotlib.pyplot as plt
import matplotlib.animation as animation
from matplotlib import style
import numpy as np
import random
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

# Create figure for plotting
fig = plt.figure()
ax = fig.add_subplot(1, 1, 1)
xs = [] #store trials here (n)
ys = [] #store relative frequency here
rs = [] #for theoretical probability

# This function is called periodically from FuncAnimation
def animate(i, xs, ys):

    #Aquire and parse data from serial port
    c = ser.readline()
    if c:
        # print(c)
        try:
            pack.ParseFromString(base64.decodebytes(c))
        except DecodeError:
            ...

	# Add x and y to lists
    xs.append(pack.mcTime)
    ys.append(pack.sensors.IMU.acc[0])

    # Limit x and y lists to 20 items
    #xs = xs[-20:]
    #ys = ys[-20:]

    # Draw x and y lists
    ax.clear()
    ax.plot(xs, ys, label="X acceleration")

    # Format plot
    plt.xticks(rotation=45, ha='right')
    plt.subplots_adjust(bottom=0.30)
    plt.title('Still Testing!')
    plt.ylabel('Acc [m/s]')
    plt.legend()
    plt.autoscale(enable=True, axis='both', tight=None)
    #plt.axis([1, 100, 0, 1.1]) #Use for 100 trial demo

# Set up plot to call animate() function periodically
ani = animation.FuncAnimation(fig, animate, fargs=(xs, ys), interval=100)
plt.show()