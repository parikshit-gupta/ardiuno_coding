from vpython import *
print("hello")

'''y = cylinder(length=1, radius=.5, color=color.yellow)
n = 1
count = 1
y.pos = vector(-5, 0, 0)
while True:
    rate(20)
    n = n+count
    y.length = n
    if (n == 10):
        count = -1
    if (n == 1):
        count = 1'''

breadBoard = box(length=10, width=2, height=.2, color=color.white)
ardBoard=box(pos=vector(-3,.2,0),length=3, width=1.3, height=.2, color=color.green)
IMUsensor=box(pos=vector(-.5,.2,0),length=1.5, width=1.3, height=.2, color=color.blue)
xarrow=arrow(axis=vector(1,0,0), length=3, shaftwidth=.3, color=color.red)
yarrow=arrow(axis=vector(0,1,0), length=3, shaftwidth=.3, color=color.green)
zarrow=arrow(axis=vector(0,0,1), length=3, shaftwidth=.3, color=color.blue)

