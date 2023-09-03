#symoy is a pyhton library which helps us to work on mathematical symbols and expressions

import numpy as np
from sympy import *
def f(t):
    return 2*t**2

def diff_f(expr, var, val):
    df = diff(expr, var)
    return df.subs(var, val).evalf()

t= symbols('t')
print(diff_f(f(t), t, 2))


arr= np.arange(1,10)
print(arr)
