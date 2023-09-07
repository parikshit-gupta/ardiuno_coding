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
arr_len= 6
xarrow = arrow(axis=vector(1, 0, 0), length=7,shaftwidth=.1, color=color.red)     #x axis
yarrow = arrow(axis=vector(0, 1, 0), length=arr_len,shaftwidth=.1, color=color.green)   #y axis
zarrow = arrow(axis=vector(0, 0, -1), length=arr_len,shaftwidth=.1, color=color.blue)    #z aixs

frontarrow = arrow(axis=vector(1, 0, 0), length=6,shaftwidth=.1, color=color.purple)    #x' axis
uparrow = arrow(axis=vector(0, 1, 0), length=3,shaftwidth=.1, color=color.yellow)       #y' axis
sidearrow = arrow(axis=vector(0, 0, 1), length=2,shaftwidth=.1, color=color.orange)     #z' axis

breadBoard = box(length=10, width=2, height=.2, color=color.white)
ardBoard = box(pos=vector(-3,.1,0),length=3, width=1.3, height=.2, color=color.green)
IMUsensor = box(pos=vector(-.5,.1,0),length=1.5, width=1.3, height=.2, color=color.blue)
my_obj= compound([breadBoard,ardBoard,IMUsensor])

#creating data object
data_obj= serial.Serial('com4', 115200)
sleep(1)

#taking the first reading out
while(data_obj.in_waiting==0):
    print("waiting")
    pass
datapacket=data_obj.readline()
datapacket=str(datapacket, 'utf-8')
splitpacket=datapacket.split(',')
print(splitpacket)

try:

    while True:

        rate(50)
        #passing data from ardiuno
        datapacket=data_obj.readline()
        datapacket=str(datapacket, 'utf-8')
        splitpacket=datapacket.split(',')
        print(splitpacket)


        #in degrees
        roll=float(splitpacket[0])    #theta (rotation about y')
        pitch=float(splitpacket[1])     #phi (rotation about x')
        #yaw=float(splitpacket[2])      #psi (rotation about z')
        
        #in radians
        pitch=pitch*to_rad
        roll=roll*to_rad
        yaw=0*to_rad

        #orientation vectors
        fa=vector(cos(roll), sin(roll), 0)
        sa=vector(0, sin(pitch),-cos(pitch))
        ua=-cross(sa, fa)

        frontarrow.axis=fa
        frontarrow.length=6
        sidearrow.axis=sa
        sidearrow.length=2
        uparrow.axis=ua
        uparrow.length=3

        my_obj.axis=fa
        my_obj.up=ua
        sleep(.01)

except:
    pass
