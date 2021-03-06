import numpy as np
from numpy import linalg as LA
import math

f = open('lab3.test.csv', "r")

rows = 2315
columns = 30

A = np.genfromtxt("lab3.test.csv", skip_header = 1, usecols = range(1, columns + 1))

str_sup = f.readline().split('\t')
B_sup = []
i = 0

while(str_sup != ['']):
  B_sup.append(str_sup[32])
  B_sup[i] = B_sup[i].replace(',', '.')
  B_sup[i] = B_sup[i].replace('\n', '')
  if (i != 0):
    B_sup[i] = float(B_sup[i])
  i += 1
  str_sup = f.readline().split('\t')

B_sup.pop(0)
B = np.array(B_sup)
sol = LA.lstsq(A, B)[0]
print(A, '\n', B, '\n')
print(sol)

const = 0.22
mis_cntr = 0

R = np.dot(A, sol)

print ("len_B = ", len(B))

for i in range(len(B)):
  if R[i] <= const:
    if B[i] > const:
      mis_cntr += 1
  elif B[i] <= const:
    mis_cntr += 1

print ('mistake counter = ', mis_cntr)

#exponent
B_copy = np.array(B)

for i in range(len(B_copy)):
  B_copy[i] = math.e ** B_copy[i]

sol = LA.lstsq(A, B_copy)[0]
print(A, '\n', B_copy, '\n')
print(sol)

const_exp = math.e ** 0.22
mis_cntr_exp = 0

R = np.dot(A, sol)

print ("len_B_copy = ", len(B_copy))

for i in range(len(B_copy)):
  if R[i] <= const_exp:
    if B_copy[i] > const_exp:
      mis_cntr_exp += 1
  elif B[i] <= const_exp:
    mis_cntr_exp += 1

print ('mistake counter exp = ', mis_cntr_exp)

#logarithm
B_copy = np.array(B)

for i in range(len(B_copy)):
  B_copy[i] = math.log(1 - B_copy[i])

sol = LA.lstsq(A, B_copy)[0]
print(A, '\n', B_copy, '\n')
print(sol)

const_log = math.log(0.78)
mis_cntr_log = 0

R = np.dot(A, sol)

print ("len_B_copy = ", len(B_copy))

for i in range(len(B_copy)):
  if R[i] <= const_log:
    if B_copy[i] > const_log:
      mis_cntr_log += 1
  elif B[i] <= const_log:
    mis_cntr_log += 1

print ('mistake counter log = ', mis_cntr_log)
