from sympy import *
from sympy.utilities.codegen import codegen

# --- Instantiate Symbolic Vars --- #

# Constants
u0,g0,Theta = symbols('u0,g0,Theta')

# State
N, E, D, u, v, w, q1, q2, q3, q4 = symbols('N E D u v w q1 q2 q3 q4')
xs = Matrix([N, E, D, u, v, w, q1, q2, q3, q4 ])
ns = xs.rows

# Parameters
xp = Matrix([])
np = xp.rows

# Control
X, Y, Z, p, q, r = symbols('X Y Z p q r')
cntrl = Matrix([X, Y, Z, p, q, r ])

# --- Dynamics --- #
I_C_B = Matrix([[q1**2-q2**2-q3**2+q4**2, 2*(q1*q2 + q3*q4), 2*(q1*q3 - q2*q4)],[2*(q2*q1-q3*q4), -q1**2 + q2**2 - q3**2 + q4**2,2*(q1*q4 + q2*q3)],[2*(q3*q1+q2*q4),2*(q2*q3 -q1*q4),-q1**2 - q2**2 + q3**2 + q4**2]])
I_C_B = Transpose(I_C_B)

skewx = Matrix([[0, -q3, q2],[ q3, 0, -q1],[ -q2, q1, 0]])

qXi = Matrix([[q4*eye(3) + skewx],[ -q1,  -q2,  -q3]])

fs = Matrix([I_C_B*Matrix([u+u0,v,w]),0,0,0,0,0,0,0])

fs = fs + Matrix([0,0,0,(Matrix([X,Y,Z]) - I_C_B.T*Matrix([0,0,g0])),1/2* qXi*Matrix([p,q,r])])

# Combine
fp = zeros(np,1)
f = fs.col_join(fp)


