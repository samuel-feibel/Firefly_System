from sympy import *
from sympy.utilities.codegen import codegen

x= symbols('x')
expr = (sin(x)/x)
[(c_name, c_code), (h_name, c_header)] = codegen(('func', expr), "C99", "test",header=False, empty=False,to_files=False)
print(c_name)
print(c_code)
print(h_name)
print(c_header)

