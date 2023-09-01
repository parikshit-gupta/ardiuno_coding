# we are going to use the bmp280 temp data, to make a vpyhton 3d simulation of a thermometer

from vpython import *
import serial
x = box(length=10, width=2, height=.2, color=color.white)
y = sphere(pos=vector(-5, 0, 0), radius=.75, color=color.red)
z = cylinder(pos=vector(-5, 0, 0), radius=.4, length=5, color=color.red)
xarrow = arrow(length=3, axis=vector(1, 0, 0), color=color.red)
yarrow = arrow(length=3, axis=vector(0, 1, 0), color=color.green)
zarrow = arrow(length=3, axis=vector(0, 0, 1), color=color.blue)

data_obj = serial.Serial('com5', 9600)

while True:
    while (data_obj.in_waiting == 0):
        pass
    rate(20)
    dataPacket = data_obj.readline()
    dataPacket = str(dataPacket, 'utf-8')
    splitPacket = dataPacket.split(',')
    temp = splitPacket[0]
    print(temp)
    leneq = (((17*float(temp))/200.0)+1.5)  # max temp is 100c
    print("leneq= ", leneq)
    z.length = leneq
   
