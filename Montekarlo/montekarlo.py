__author__ = 'Volosheniuk'
import random
import math


#n -- dimension
n = 20
npoints = 100000000
s = 0
ss = 0
#1
#method Montekarlo for  volume
for i in range(1, npoints + 1):
    ss = 0
    for i in range(0, n):
        ss = ss + random.uniform(-1,1) ** 2
        if ss > 1:
            break
    if ss > 1:
        continue
    else:
        s = s + 1
print("The volume of the 20-sphere=")
print((2 ** n) * (s / npoints))



#2 The integral of the n-dimensional Gaussian


def f(mas):
	myf=0
	for i in range(0,n):
		myf=mas[i] ** 2
	return math.exp(-myf)<mas[n]
	
	s = 0
	ss = 0
	mas=[]

		
	for i in range(1, npoints + 1):
		ss = 0
		for i in range(0, n):	
			mas.append(str(random.uniform(-100, 100)))
			
		mas.append(str(random.uniform(0, 1)))
		
		if f(mas):
			continue
		else:
			s = s + 1
print(" The integral of the n-dimensional Gaussian=")
print((2 ** n) * (s / npoints))


#3   1, but with the punctured area of small diameter.  diam=0.01 
eps=0.01
s = 0
ss = 0

#method Montekarlo for  volume
for i in range(1, npoints + 1):
    ss = 0
    for i in range(0, n):
        ss = ss + random.uniform(-1,1) ** 2
        if ss > 1 or ss<eps ** 2:
            break
    if ss > 1 or ss<eps ** 2:
        continue
    else:
        s = s + 1
print("The volume of the 20-sphere, but with the punctured area of small diameter.  diam=0.01=")
print((2 ** n) * (s / npoints))
