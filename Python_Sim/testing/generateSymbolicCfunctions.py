from sympy import *
from sympy.utilities.codegen import codegen

# --- Instantiate Symbolic Vars --- #

# State
N, E, D, u, v, w, q1, q2, q3, q4 = symbols('N E D u v w q1 q2 q3 q4')
xs = Matrix([N, E, D, u, v, w, q1, q2, q3, q4 ])
ns = 10

# Control
X, Y, Z, p, q, r = symbols('X Y Z p q r')
cntrl = Matrix([X, Y, Z, p, q, r ])

# --- Dynamics --- #
I_C_B = Matrix([[q1**2-q2**2-q3**2+q4**2, 2*(q1*q2 + q3*q4), 2*(q1*q3 - q2*q4)],[2*(q2*q1-q3*q4), -q1**2 + q2**2 - q3**2 + q4**2,2*(q1*q4 + q2*q3)],[2*(q3*q1+q2*q4),2*(q2*q3 -q1*q4),-q1**2 - q2**2 + q3**2 + q4**2]])
I_C_B = Transpose(I_C_B)

skewx = Matrix([[0, -q3, q2],[ q3, 0, -q1],[ -q2, q1, 0]])


