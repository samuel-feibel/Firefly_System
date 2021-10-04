import sys

from google.protobuf.message import DecodeError

import autopilot_pb2 as spb
import serial
import base64

pack = spb.Example()

with serial.Serial('COM3', 115200, timeout=0) as ser:
    while True:
        c = ser.readline()
        
        if c:
            try:
                err = pack.ParseFromString(base64.decodebytes(c))
                print(pack)
                print(pack.value)
            except DecodeError:
                ...