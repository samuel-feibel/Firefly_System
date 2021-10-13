import sys

from google.protobuf.message import DecodeError

import autopilot_pb2
# import example_pb2
import serial
import base64

pack = autopilot_pb2.PlaneBuf()
# pack = example_pb2.Example()

with serial.Serial('COM3', 115200, timeout=0) as ser:
    while True:
        c = ser.readline()
        
        if c:
            # print(c)
            try:
                pack.ParseFromString(base64.decodebytes(c))
                # print(pack.sensors.baro.pressure)
                print(pack.sensors.test)
            except DecodeError:
                ...