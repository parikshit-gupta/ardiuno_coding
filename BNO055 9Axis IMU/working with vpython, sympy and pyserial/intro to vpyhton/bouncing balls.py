from vpython import *
from sympy import *
# the box and reference frame
arr_len = 100
side = 100
thick = 1
posn = side/2
opa = .2


#xarrow = arrow(axis=vector(1, 0, 0), length=arr_len,shaftwidth=2, color=color.red)
#yarrow = arrow(axis=vector(0, 1, 0), length=arr_len,shaftwidth=2, color=color.green)
#zarrow = arrow(axis=vector(0, 0, 1), length=arr_len,shaftwidth=2, color=color.blue)

xp = box(pos=vector(posn, 0, 0), length=thick, width=side,
         height=side, color=color.white, opacity=opa)
xn = box(pos=vector(-posn, 0, 0), length=thick, width=side,
         height=side, color=color.white, opacity=opa)
yp = box(pos=vector(0, posn, 0), length=side, width=side,
         height=thick, color=color.white, opacity=opa)
yn = box(pos=vector(0, -posn, 0), length=side, width=side,
         height=thick, color=color.white, opacity=opa)
zp = box(pos=vector(0, 0, posn), length=side, width=thick,
         height=side, color=color.white, opacity=opa)
zn = box(pos=vector(0, 0, -posn), length=side, width=thick,
         height=side, color=color.white, opacity=opa)

# the ball
rad = 2
ball = sphere(radius=rad, pos=vector(5, 5, 0), color=color.yellow)

# balls motion


def f(t):
    return 2*t


def diff_f(expr, var, val):
    df = diff(expr, var)
    return df.subs(var, val).evalf()


def mag(arr):
    magnitude = sqrt(pow(arr[0], 2)+pow(arr[1], 2)+pow(arr[2], 2))
    return magnitude


# parameters to define line of motion
fix = [5, 5, 0]
slope = [1, 2, 3]
img_fix = [0, 0, 0]
t = symbols('t')
time = 0.0
mag_slope = mag(slope)

# velocity vector
vel = [0, 0, 0]
for i in range(0, 3):
    vel[i] = (diff_f(f(t), t, time))*slope[i]

x = float(fix[0])
y = float(fix[1])
z = float(fix[2])
while True:
    rate(50)

    #check for collision
    #1
    if (x > 49 and x < 51):
        img_fix = [(100-fix[0]), fix[1], fix[2]]
        fix = [x, y, z]
        time = 0.1
        print(img_fix)
        for i in range(0, 3):
            slope[i] = fix[i]-img_fix[i]
        temp_slope_mag = mag(slope)
        for i in range(0, 3):
            slope[i] = (slope[i]*mag_slope)/temp_slope_mag
    
    #2
    elif (y > 49 and y < 51):
        img_fix = [fix[0], (100 - fix[1]), fix[2]]
        fix = [x, y, z]
        time = 0.1
        print(img_fix)
        for i in range(0, 3):
            slope[i] = fix[i]-img_fix[i]
        temp_slope_mag = mag(slope)
        for i in range(0, 3):
            slope[i] = (slope[i]*mag_slope)/temp_slope_mag

    #3
    elif (z > 49 and z < 51):
        img_fix = [fix[0], fix[1],(100 - fix[2])]
        fix = [x, y, z]
        time = 0.1
        print(img_fix)
        for i in range(0, 3):
            slope[i] = fix[i]-img_fix[i]
        temp_slope_mag = mag(slope)
        for i in range(0, 3):
            slope[i] = (slope[i]*mag_slope)/temp_slope_mag

    #4
    elif (x < -49 and x > -51):
        img_fix = [-(100+fix[0]), fix[1], fix[2]]
        fix = [x, y, z]
        time = 0.1
        print(img_fix)
        for i in range(0, 3):
            slope[i] = fix[i]-img_fix[i]
        temp_slope_mag = mag(slope)
        for i in range(0, 3):
            slope[i] = (slope[i]*mag_slope)/temp_slope_mag

    #5
    elif (y < -49 and y > -51):
        img_fix = [fix[0], -(100+fix[1]), fix[2]]
        fix = [x, y, z]
        time = 0.1
        print(img_fix)
        for i in range(0, 3):
            slope[i] = fix[i]-img_fix[i]
        temp_slope_mag = mag(slope)
        for i in range(0, 3):
            slope[i] = (slope[i]*mag_slope)/temp_slope_mag

    #6
    elif (z < -49 and z > -51):
        img_fix = [fix[0], fix[1], -(100+fix[2])]
        fix = [x, y, z]
        time = 0.1
        print(img_fix)
        for i in range(0, 3):
            slope[i] = fix[i]-img_fix[i]
        temp_slope_mag = mag(slope)
        for i in range(0, 3):
            slope[i] = (slope[i]*mag_slope)/temp_slope_mag


    for i in range(0, 3):
        vel[i] = (diff_f(f(t), t, time))*slope[i]


    x = float(((f(t).subs(t, time).evalf())*slope[0])+fix[0])
    y = float(((f(t).subs(t, time).evalf())*slope[1])+fix[1])
    z = float(((f(t).subs(t, time).evalf())*slope[2])+fix[2])
    ball.pos = vector(x, y, z)
    print(ball.pos)
    time = time+.2