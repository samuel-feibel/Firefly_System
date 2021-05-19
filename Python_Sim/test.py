from sympy.core.symbol import Symbol, symbols
from sympy.utilities.autowrap import autowrap
x, y = symbols('x y')
print(x)
expr = ((x+y)**(2)).expand()
print(expr)
eq = autowrap(expr,language='C')
