__author__ = 'Volosheniuk'
import math

def f(x, y):
    return y

def t(x):
    return a + (b - a) / np * x

a = 0
b = 1
y0 = 1
y = 0
np = 1000
tt = (b - a) / np

f1 = open("euler.txt","w")
f2 = open("runge.txt","w")
f3 = open("adams.txt","w")

for j in range(1,18):
    print(j)
    a = 0
    b = 1
    y0 = 1
    y = 0
    np = 5*(2**j)
    tt = (b - a) / np
#Euler
    yy = y0
    ey = 0
    for i in range(1,np + 1):
        ey = yy + tt * f(t(i - 1), yy)
        yy = ey

#Runge-Kutta
    yy = y0
    rky = 0
    k1 = k2 = k3 = k4 = 0
    stack = []
    stack.append(yy)
    for i in range(1,np + 1):
        k1 = tt * f(t(i - 1), yy)
        k2 = tt * f(t(i - 1) + tt / 2, yy + k1 / 2)
        k3 = tt * f(t(i - 1) + tt / 2, yy + k2 / 2)
        k4 = tt * f(t(i - 1) + tt, yy + k3)
        rky = yy + (k1 + 2 * k2 + 2 * k3 + k4) / 6
        yy = rky
        if i < 4:
            stack.append(rky)


    stack.reverse()

#Adams
    y1 = y2 = y3 = 0
    ay = 0
    for i in range(4, np + 1):
        # print(stack)
        ay = stack[0] + tt * (55 * f(t(i - 1), stack[0]) - 59 * f(t(i - 2), stack[1]) + 37 * f(t(i - 3), stack[2]) - 9 * f(t(i - 4), stack[3])) / 24
        stack.pop()
        stack.insert(0, ay)
    f1.write(str((b - a) / np) + " " + str(abs(math.exp(b) - ey)) + "\n")
    f2.write(str((b - a) / np) + " " + str(abs(math.exp(b) - rky)) + "\n")
    f3.write(str((b - a) / np) + " " + str(abs(math.exp(b) - ay)) + "\n")


f1.close()
f2.close()
f3.close()

print("Euler: " + str(ey))
print("Runge: " + str(rky))
print("Adams: " + str(ay))
print("True:  "+str(math.exp(b)))
