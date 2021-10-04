import dash
from dash.dependencies import Output, Input
import dash_core_components as dcc
import dash_html_components as html
import plotly
import random
import plotly.graph_objs as go
from collections import deque
import numpy as np
import

import serial

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

# def pull_all():
    # s = ser.pull_all()
    # arr = s.split('\n')
    # for line in arr:
    #   l = line.decode('ascii').replace('[', '').replace(']', '').strip()
    #   a = np.fromstring(s, sep=',')
    #   Y.append(a[0])

@app.callback(Output('live-graph', 'figure'), [Input('graph-update', 'n_intervals')])  
def update_graph_scatter(n):
    X.append(X[-1]+1)

    s = ser.readline().decode("ascii").replace('[', '').replace(']', '').strip()
    arr = np.fromstring(s, sep=',')
    Y.append(arr[0])

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