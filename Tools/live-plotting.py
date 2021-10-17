import dash
from dash.dependencies import Output, Input
import dash_core_components as dcc
import dash_html_components as html
import plotly
import random
import plotly.graph_objs as go
from collections import deque
import numpy as np
import serial

# import sys

from google.protobuf.message import DecodeError

import autopilot_pb2
import base64

pack = autopilot_pb2.PlaneBuf()


X = deque(maxlen = 200)
X.append(1)
  
Y = deque(maxlen = 200)
Y.append(1)
  
app = dash.Dash(__name__)
  
app.layout = html.Div(
    [
        dcc.Graph(id = 'live-graph', animate = True),
        dcc.Interval(
            id = 'graph-update',
            interval = 1000,
            n_intervals = 0
        ),
    ]
)

@app.callback(Output('live-graph', 'figure'), [Input('graph-update', 'n_intervals')])  
def update_graph_scatter(n):
    X.append(X[-1]+1)
    # Y.append(Y[-1]+Y[-1] * random.uniform(-0.1,0.1))
    c = ser.readline()
    if c:
        try:
            pack.ParseFromString(base64.decodebytes(c))
            Y.append(pack.sensors.IMU.acc[0])
        except DecodeError:
            ...
        

    data = plotly.graph_objs.Scatter(
            x=list(X),
            y=list(Y),
            name='Scatter',
            mode= 'lines+markers'
    )
  
    return {'data': [data],
            'layout' : go.Layout(xaxis=dict(range=[min(X),max(X)]),yaxis = dict(range = [min(Y),max(Y)]),)}
  
if __name__ == '__main__':
    ser = serial.Serial('COM3', 115200, timeout=0)
    app.run_server()
    ser.close()