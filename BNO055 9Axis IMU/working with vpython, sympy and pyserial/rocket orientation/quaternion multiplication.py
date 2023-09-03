from vpython import *
import math
import numpy as np


def quat_multiply(q1, q2):
    [a, v1] = q1
    [e, v2] = q2

    v3 = a*v2+e*v1+cross(v1, v2)
    q3 = [a*e-dot(v1, v2), v3]

    return q3


raw_quat = [0, vector(0, 1, 1)]
raw_quat_conj = [0, vector(0, -1, -1)]


x_quat = [0, vector(1, 0, 0)]
y_quat = [0, vector(0, 1, 0)]
z_quat = [0, vector(0, 0, 1)]

x_rot_quat = quat_multiply((quat_multiply(raw_quat, x_quat)), raw_quat_conj)
z_rot_quat = quat_multiply((quat_multiply(raw_quat, z_quat)), raw_quat_conj)

fa = x_rot_quat[1]
sa = z_rot_quat[1]
ua = cross(sa, fa)
print(fa)
print(ua)
print(sa)
