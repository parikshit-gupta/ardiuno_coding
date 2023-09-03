from vpython import *
from time import sleep
import math
import numpy as np
import serial


scene.range = 10
scene.width=1280
scene.height=600
scene.forward=vector(-1,-1,-1)

#conversion factors
to_deg=180/np.pi
to_rad=1/to_deg

#creating vpython objects
arr_len= 4
xarrow = arrow(axis=vector(1, 0, 0), length=arr_len,shaftwidth=.1, color=color.red)     #x axis
yarrow = arrow(axis=vector(0, 1, 0), length=arr_len,shaftwidth=.1, color=color.green)   #y axis
zarrow = arrow(axis=vector(0, 0, 1), length=arr_len,shaftwidth=.1, color=color.blue)    #z aixs

frontarrow = arrow(axis=vector(1, 0, 0), length=6,shaftwidth=.1, color=color.purple)    #x' axis
uparrow = arrow(axis=vector(0, 1, 0), length=3,shaftwidth=.1, color=color.yellow)       #y' axis
sidearrow = arrow(axis=vector(0, 0, 1), length=2,shaftwidth=.1, color=color.orange)     #z' axis

breadBoard = box(length=10, width=2, height=.2, color=color.white)
ardBoard = box(pos=vector(-3,.1,0),length=3, width=1.3, height=.2, color=color.green)
IMUsensor = box(pos=vector(-.5,.1,0),length=1.5, width=1.3, height=.2, color=color.blue)
my_obj= compound([breadBoard,ardBoard,IMUsensor])

#quaternion multiplication
def quat_multiply(q1, q2):
    [a, v1] = q1
    [e, v2] = q2

    v3=a*v2+e*v1+cross(v1,v2)
    q3 = [a*e-dot(v1,v2), v3]

    return q3


#creating data object
data_obj= serial.Serial('com4', 115200)
sleep(1)

while True:
    #waiting for data at the com port
    while(data_obj.in_waiting==0):
        pass

    rate(50)

    #passing data from ardiuno
    datapacket=data_obj.readline()
    datapacket=str(datapacket, 'utf-8')
    splitpacket=datapacket.split(',') #quaternion obtained from arduino

    #the rotation quaternion
    raw_quat=[splitpacket[0], vector(splitpacket[1], splitpacket[2], splitpacket[3])]
    raw_quat_conj=[raw_quat[0],vector(-raw_quat[1],-raw_quat[2],-raw_quat[3])]

    #initial sensor axes
    x_quat = [0.0, vector(1.0, 0.0, 0.0)]
    y_quat = [0.0, vector(0.0, 1.0, 0.0)]
    z_quat = [0.0, vector(0.0, 0.0, 1.0)]


    #rotated sensor axes
    x_rot_quat=quat_multiply((quat_multiply(raw_quat,x_quat)), raw_quat_conj)
    z_rot_quat=quat_multiply((quat_multiply(raw_quat,z_quat)), raw_quat_conj)

    fa=x_rot_quat[1]
    sa=z_rot_quat[1]
    ua=cross(sa,fa)
    print(sa)

    frontarrow.axis=fa
    frontarrow.length=6
    sidearrow.axis=sa
    sidearrow.length=2
    uparrow.axis=ua
    uparrow.length=3

    my_obj.axis=fa
    my_obj.up=ua