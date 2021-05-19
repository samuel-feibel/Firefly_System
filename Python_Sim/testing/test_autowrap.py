from sympy import *
from sympy.utilities.autowrap import autowrap, ufuncify

x,y,z = symbols('x y z')

expr = (sin(x)/x)
# bFunc = autowrap(expr,language='C',backend='cython',tempdir='/tmp')
# print(bFunc(1,4,2))

from numpy import linspace
fn = ufuncify([x],expr,backend='cython')

xx = linspace(1,6,3)

print(fn(xx))

