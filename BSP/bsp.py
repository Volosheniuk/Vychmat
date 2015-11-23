 import numpy
 import matplotlib.pyplot as np
 import math
 import copy
 from functools import reduce
 SHOWN = {

     'sine': False,
     'table': True,
     'poly': False,
     'scmp': False,

}
def drange(start, stop=None, step=None):
   if stop is None:
      stop = start
      step = 1
      start = 0
   elif step is None:
	step = stop
	stop = start
	start = 0

    r = start
    while r < stop:
    	yield r
    	r += step

class TextProcessor:
	def __init__(self, filename):
	self._name = filename
	def process(self):
	   mtrx = numpy.transpose(numpy.genfromtxt(self._name)).tolist()
	   tlist = [(mtrx[0][i], mtrx[1][i]) for i in range(len(mtrx[0]))]
           tlist.sort()
 	   return [e[0] for e in tlist], [e[1] for e in tlist]

class PolySet:
	def __init__(self, net, order, previous=None):
		self._net = net
		self._order = order
 		self._vnet = copy.copy(net)
		self._vnet[-1:-1] = map(lambda x: net[-1] + 1 + x, range(self._order + 3))

 		if previous:
			self._previous = previous
		else:
			if self._order > 0:
				self._previous = self.__class__(self._net, self._order - 1)
		self._cache = {}

	def _fix_index(self, index):
		return index - int((self._order + 1) / 2)
	
	 def _wrap_polynome(self, i):
		return lambda x: self.evaluate(i, x)
	def _wrap_row(self, row):
		return lambda x: sum(row[i]*self.evaluate(self._fix_index(i), x) for i in range(len(row)))
 	def wrap(self, what):
		if isinstance(what, int):
			return self._wrap_polynome(what)
		else:
			return self._wrap_row(what)
	 def _evaluate(self, i, x):
		if i not in self._cache:
			 self._cache[i] = {}
		 if self._order > 0:
		 	self._cache[i][x] = 0
			c1 = (x-self._vnet[i])/(self._vnet[i+self._order]-self._vnet[i])
			c2 = (self._vnet[i+self._order+1]-x)/(self._vnet[i+self._order+1]-self._vnet[i+1])
			 self._cache[i][x] += self._previous.evaluate(i, x) * c1
			  self._cache[i][x] += self._previous.evaluate(i+1, x) * c2
		else:
			try:
				 if self._vnet[i] <= x < self._vnet[i+1]:
				 	self._cache[i][x] = 1
				 else:
				 	self._cache[i][x] = 0
			except IndexError:
				print("Index {0} out of range !".format(i))
				print(self._vnet)
				exit()
	 return self._cache[i][x]


	 def get_basis(self):
		return [self.wrap(self._fix_index(pt)) for pt in range(len(self._net))]


	 def get_net(self):
	 	 return self._net

	def evaluate(self, i, x, p=None):
		 if p is None:
		 	 return self._evaluate(i, x)

		 if p > self._order:
		 	 return -1e10
		 if self._order == p:
		 	 return self._evaluate(i, x)

		 if p < self._order:
			 if self._order > 0:
				 return self._previous.evaluate(i, x, p)
			 else:
			 	 print("o: {0}, p: {1}".format(self._order, p))

				  return 1e10
			 print("Неподдерживаемые параметры <{0},{1}> ({2})".format(i, p, x))

			 return 1e10
	
class SplineMachine:
	 def __init__(self, polyset):
		 self._polyset = polyset
		  self._net = polyset.get_net()

	def _interpolate_func(self, func):
		return self._interpolate_table([func(pt) for pt in self._net])

	 def _interpolate_table(self, y):
	 	 basis = self._polyset.get_basis()
		 a = []
		 b=y
		 for pt in self._net:
		 	q=[]
			 for f in basis:
			 	q.append(f(pt))
			a.append(q)
		a = numpy.matrix
		 b = (numpy.transposenumpy.transpose*(numpy.matrix(b))).tolist()
		 a = numpy.transpose*a

		try:
			row = numpy.linalg.solve(a, b)
			return self._polyset.wrap(row)
		except  numpy.linalg.linalg.LinAlgError:
			 print("error")
			 exit()

		return None
	

	 def interpolate(self, subj):
	 	if callable(subj):
		 	return self._interpolate_func(subj)
		else:
			return self._interpolate_table(subj)


class PolyMachine:
	def __init__(self, net):
		self._net = net
		self._mtr = list(map(lambda x: list(map(lambda n: x**n, range(len(net)))), net))
	

	 def _interpolate_table(self, table):
	 	 return numpy.linalg.solve(self._mtr, table)

	 def _interpolate_function(self, func):
		return self._interpolate_table(list(map(func, self._net)))

	 def interpolate(self, what):
	 	 if callable(what):
			 return self._interpolate_function(what)
		 else:
           		 return self._interpolate_table(what)

    	def wrap(self, row):
        	return self._wrap_row(row)

   	 def _wrap_row(self, row):
       		 return lambda x: reduce(lambda s, n: s+row[n]*(x**n), range(len(row)), 0)


	if SHOWN['poly']:
  		  eNet = list(range(100))
    		pNet = list(drange(14, 0.1))
		ps = PolySet(eNet, 10)

        for k in range(11):
     	   np.plot(pNet,list(map(lambda x: ps.evaluate(3, x, k), pNet)))

      np.show()


	if SHOWN['table']:
    		eNet, eVal = TextProcessor('func.dat').process()
   		 pNet = list(drange(1, 10.1, 0.1))
		sm = SplineMachine(PolySet(eNet, 3))
		pm = PolyMachine(eNet)
	        p = pm.wrap(pm.interpolate(eVal))
	       f = sm.interpolate(eVal)
	      np.scatter(eNet, eVal, c='r')
	      np.plot(pNet,list(map(f, pNet)),c='g')

    np.plot( pNet,list(map(p, pNet)),c='b')
    np.show()

    print(f(10))

if SHOWN['sine']:
    eNet = list(range(100))
    eFun = lambda x: math.sin(x/10)

    pNet = list(drange(100, 0.1))

    sm = SplineMachine(PolySet(eNet, 3))

    f = sm.interpolate(eFun)
    np.scatter(eNet,list(map(eFun, eNet)),c='r')
    np.plot(pNet,list(map(f, pNet)),c='g')

    np.show()

if SHOWN['scmp']:
    err = []
    err2 = []
    err3 = []

    for step in range(3, 51):

        eNet = list(range(0, 200, step))
        eFun = lambda x: math.sin(x/10)

        print(eNet)

        pNet = list(drange(200, 0.4))

        sm = SplineMachine(PolySet(eNet, 3))

        f = sm.interpolate(eFun)
        err.append(max(map(lambda x: abs(f(x) - eFun(x)), pNet)))
        err2.append(max(err))

        pm = PolyMachine(eNet)
        f = pm.wrap(pm.interpolate(eFun))

        err3.append(max(map(lambda x: abs(f(x) - eFun(x)), pNet)))

    np.plot(list(range(3, 51)), err)
    np.plot(list(range(3, 51)), err2, c='r')

    np.plot(list(range(3, 51)), err3, c='g')


    np.show()





			






















