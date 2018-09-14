_P=(1<<64)-(1<<32)+1

def pow_mod(n,m,p):
    temp=n
    ans=1
    while(m):
        if(m&1):
            ans=(ans*temp)%p
        m>>=1
        temp=(temp*temp)%p
    return ans
