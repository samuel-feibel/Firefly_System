from google.protobuf.message import DecodeError

import autopilot_pb2
import base64

pack = autopilot_pb2.PlaneBuf()

with open('dataLog.txt') as f:
    line = f.readline()
    line = bytes(line, 'ascii')
    while line:
        line = f.readline()
        pack.ParseFromString(base64.decodebytes(line))

        # Write to csv
        
