import numpy as np

def showLoop(alpha,M):
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
	    
    for i in range(len(finite)):
        print(str(alpha)+"^"+str(i)+"(mod"+str(M)+")="+str(finite[i]))
    return finite

L=showLoop(4,13)
print(L)
