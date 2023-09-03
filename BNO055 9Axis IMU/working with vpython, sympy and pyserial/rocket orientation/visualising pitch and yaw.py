from vpython import *
from time import sleep
import numpy as np
import math

to_deg = 180/np.pi
to_rad = 1/to_deg

#the scene function of vptyhon helps in adjusting the vpython display when first opened
scene.range=10
scene.forward=vector(-1,-1,-1)
scene.width=1280
scene.height=600

arr_len= 4
xarrow = arrow(axis=vector(1, 0, 0), length=arr_len,shaftwidth=.1, color=color.red)
yarrow = arrow(axis=vector(0, 1, 0), length=arr_len,shaftwidth=.1, color=color.green)
zarrow = arrow(axis=vector(0, 0, 1), length=arr_len,shaftwidth=.1, color=color.blue)

frontarrow = arrow(axis=vector(1, 0, 0), length=6,shaftwidth=.1, color=color.purple)
uparrow = arrow(axis=vector(0, 1, 0), length=3,shaftwidth=.1, color=color.yellow)
sidearrow = arrow(axis=vector(0, 0, 1), length=2,shaftwidth=.1, color=color.orange)

breadBoard = box(length=10, width=2, height=.2, color=color.white)
ardBoard = box(pos=vector(-3,.2,0),length=3, width=1.3, height=.2, color=color.green)
IMUsensor = box(pos=vector(-.5,.2,0),length=1.5, width=1.3, height=.2, color=color.blue)
my_obj= compound([breadBoard,ardBoard,IMUsensor])


#visualising pitch and yaw

while True:
    pitch = 15*to_rad
    #np.arange creates a densely packed array which makes excecutuon faster
    for yaw in np.arange(0, 2*np.pi, .01):
        rate(50)
        fa = vector(cos(yaw)*cos(pitch),sin(pitch), sin(yaw)*cos(pitch))  #frontarrow position
        y=vector(0,1,0)
        sa= cross(fa, y)                   #sidearrow position
        ua=cross(sa, fa)                   #uparrow posiiton
        print(sa) #note that y coordinate of the tip of sa is 0, which means it rotates in the x-z plane only

        #defining coordinate axes attached to our sensor
        frontarrow.axis=fa
        frontarrow.length=6
        uparrow.axis=ua
        uparrow.length=3
        sidearrow.axis=sa
        sidearrow.length=2

        my_obj.axis=fa
        my_obj.up=ua

