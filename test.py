import numpy as np     
class MultiplicationNTT:
	def __init__(self,mod,alpha,show=False):
		self._M=mod
		self._alpha=alpha
		self._F=self._finiteField(alpha,mod,show)
		self._N=len(self._F)
		self._Ninv=self._modularInverse(self._N,mod)
		self._addTable,self._mulTable=self._createCalsTable(mod)
		self._nttTable,self._inttTable=self._createTransTable(self._F,self._Ninv,self._N,mod,alpha)
	def show(self):
		print("M: "+str(self._M))
		print("N: "+str(self._N))
		print("alpha: "+str(self._alpha))
		print("N_inverse: "+str(self._Ninv))
		print("\nCount Number M: "+str(self._cntNumber(self._M))+"\n")
		print("len:"+str(len(self._F))+"\n")
		print(self._F)
		print("\nnttTable:")
		print(self._nttTable)
		print("\ninttTable:")
		print(self._inttTable)
	def showCal(self):
		print("\ninput:")
		print(self._a)
		print(self._b)
		print("\nNTT:")
		print(self._A)
		print(self._B)
		print("\nproduct:")
		print(self._C)
		print("\nINTT:")
		print(self._c)
	def test(self):
		self.inputa(2)
		self.inputb(3)
		self.nttAB()
		self.outC()
		self.inttc()
	def inputa(self,a):
		self._a=np.zeros(self._N,dtype="int32")
		self._a[1]=1
		self._a=self._a.reshape(self._N,1)
		
	def inputb(self,b):
		self._b=np.zeros(self._N,dtype="int32")
		self._b[0]=1
		self._b[1]=1
		self._b=self._b.reshape(self._N,1)
		
	def nttAB(self):
		self._A=np.mod(self._nttTable.dot(self._a),self._M)
		self._B=np.mod(self._nttTable.dot(self._b),self._M)
		
	def outC(self):
		self._C=np.mod(self._A*self._B,self._M)
		
	def inttc(self):
		self._c=np.mod(self._inttTable.dot(self._C),self._M)
		
	def cntM(self):
		return self._cntNumber(self.M)
		
	def lenF(self):
		return len(self._F)
	
	def _finiteField(self,alpha,M,show=False):
		flag=True
		finite=[]
		i=0
		while(flag):
			out=np.mod(alpha**i,M)
			if(i>0 and out==1):
				flag=False
			if(flag):
				finite.append(out)
			i+=1
			if(i>16):
				break
		if(show):
			for i in range(len(finite)):
				print(str(alpha)+"^"+str(i)+"(mod"+str(M)+")="+str(finite[i]))
		return finite

	def _createCalsTable(self,mod):
		add=np.zeros(mod**2,dtype="int32").reshape(mod,mod)
		mul=np.zeros(mod**2,dtype="int32").reshape(mod,mod)
		for i in range(mod):
			for j in range(mod):
				add[i][j]=(i+j)%mod
				mul[i][j]=(i*j)%mod
		return add,mul

	def _createTransTable(self,finite,inverse,N,M,alpha):
		ntt=[]
		intt=[]
		for i in range(N):
			for j in range(N):
				ntt.append(finite[np.mod(i*j,len(finite))])
				intt.append(np.mod(inverse*finite[np.mod((-i*j),len(finite))],M))
		return np.array(ntt).reshape(N,N),np.array(intt).reshape(N,N)

	def _cntNumber(self,i):
		if(not i):
			return 0;
		else:
			return self._cntNumber(i&i-1)+1
		
	def _gcd(self,a,b):
		if(a==0):
			return b,0,1
		else:
			q,x,y=self._gcd(b%a,a)
			return q,y-(b//a)*x,x

	def _modularInverse(self,i,mod):
		q,x,y=self._gcd(i,mod)
		if(q!=1):
			print("modular inverse dose not exist.")
		else:
			return x%mod
M=13
alpha=4
#alpha^N=1(mod M)
test=MultiplicationNTT(13,5,True)
test.test()
test.show()
test.showCal()
