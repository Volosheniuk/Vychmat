__author__ = 'Volosheniuk'
import math

def fx(x,y):
    return 98*x + 198*y

def fy(x,y):
    return -99*x - 199*y

tau = 0.00001

uk = [1, 1]
uk1 = [0, 0]

xk = [0,0]
xk1 = [100,100]
a = [0,0]
p = 0.00001
z = 100
k = 0

f1 = open("2part.txt","w")

for i in range (0,1000000):
   # print(i)
    a[0] = xk[0] = uk[0]
    a[1] = xk[1] = uk[1]


    while z>p:
       # print(k)
       # k = k + 1
        xk1[0] = a[0] + tau * fx(xk[0], xk[1])
        xk1[1] = a[1] + tau * fy(xk[0], xk[1])
        z = math.sqrt((xk1[0] - xk[0])**2 + (xk1[1] - xk[1])**2)
        xk[0] = xk1[0]
        xk[1] = xk1[1]
    z = 1000
    f1.write(str(uk[0])+" "+str(uk[1])+"\n")

    uk[0] = xk[0]
    uk[1] = xk[1]

f1.close()
print("Answer x, y:")
print(uk)

