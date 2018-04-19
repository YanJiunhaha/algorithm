#include <iostream>  
#include <string.h>  
#include <stdio.h>  

#define debug_prepare 0
#define debug_mod 0
#define debug_rader 0
#define debug_NTT 1

  
using namespace std;  
typedef long long LL;  

const int N = 1 << 18;  
const int P = (479 << 21) + 1;  
const int G = 3;  
const int NUM = 20;  


/*
Ft=2^(2^t)+1
let M=Ft
for 0<t<=4
	G=3,N=Tt-1
const LL t=2;
const LL P=(1<<(1<<t))+1;
const LL G=3;
const LL N=P-1;
const int NUM = 20; 
*/
LL  wn[NUM];  
LL  a[N], b[N];  
char A[N], B[N];  
  
inline unsigned int bit_reverse(unsigned int a,int len){
	a=((a&0x55555555U)<<1)|((a&0xAAAAAAAAU)>>1);
	a=((a&0x33333333U)<<2)|((a&0xCCCCCCCCU)>>2);
	a=((a&0x0F0F0F0FU)<<4)|((a&0xF0F0F0F0U)>>4);
	a=((a&0x00FF00FFU)<<8)|((a&0xFF00FF00U)>>8);
	a=((a&0x0000FFFFU)<<16)|((a&0xFFFF0000U)>>16);
	return a>>(32-len);
}  
  
LL quick_mod(LL a, LL b, LL m)  
{  
    LL ans = 1;  
    a %= m;  
    while(b)  
    {  
#if debug_mod
		cout<<"a:"<<a<<" b:"<<b<<" m:"<<m<<" ans:"<<ans<<endl;
#endif
        if(b & 1)  
        {  
            ans = ans * a % m;  
            b--;  
        }  
        b >>= 1;  
        a = a * a % m;  
    }  
    return ans;  
}  
  
void GetWn()  
{  
    for(int i = 0; i < NUM; i++)  
    {  
        int t = 1 << i;  
        wn[i] = quick_mod(G, (P - 1) / t, P);  
    }  
}  
  
void Prepare(char A[], char B[], LL a[], LL b[], int &len)  
{  
    len = 1;  
    int L1 = strlen(A);  
    int L2 = strlen(B);  
    while(len <= 2 * L1 || len <= 2 * L2) len <<= 1;  
#if debug_prepare
	cout<<"prepare len:"<<len<<endl;
#endif
    for(int i = 0; i < len; i++)  
    {  
        if(i < L1) a[i] = A[L1 - i - 1] - '0';  
        else a[i] = 0;  
        if(i < L2) b[i] = B[L2 - i - 1] - '0';  
        else b[i] = 0;  
    }  
}  
  
void Rader(LL a[], int len)  
{  
    int j = len >> 1;  
#if debug_rader 
	for(int i=0;i<len;i++)
		cout<<a[i]<<" ";
	cout<<endl;
#endif
    for(int i = 1; i < len - 1; i++)  
    {  
        if(i < j) swap(a[i], a[j]);  
        int k = len >> 1;  
        while(j >= k)  
        {  
            j -= k;  
            k >>= 1;  
        }  
        if(j < k) j += k;  
    } 
#if debug_rader 
	for(int i=0;i<len;i++)
		cout<<a[i]<<" ";
	cout<<endl;
#endif	
}  
  
void NTT(LL a[], int len, int on)  
{  
    //Rader(a, len);  
	int bitlen=std::__lg(len);
	int in[N];
#if debug_rader 
	for(int i=0;i<len;i++)
		cout<<a[i]<<" ";
	cout<<endl;
#endif
	for(int i=0;i<len;++i)in[i]=a[i];
	for(int i=0;i<len;++i)a[bit_reverse(i,bitlen)]=in[i];
#if debug_rader 
	for(int i=0;i<len;i++)
		cout<<a[i]<<" ";
	cout<<endl;
#endif
    int id = 0;  
#if debug_NTT
		cout<<"=============hb============="<<endl;
#endif 
    for(int h = 2; h <= len; h <<= 1)  
    { 
		id++; 
		int wn_n=quick_mod(G,(P-1)>>id,P);
#if debug_NTT
		cout<<"h(h*2): "<<h<<endl;
		cout<<"id(id+=1): "<<id<<endl;
		cout<<"wn_n(pow_mod(G,(P-1)/(2^id),P)):"<<wn_n<<endl;
		cout<<"=============jb============="<<endl;
#endif
        for(int j = 0; j < len; j += h)  
        {
            LL w = 1;  
#if debug_NTT
			cout<<"j(j+=h):"<<j<<endl;
			cout<<"w:"<<w<<endl;
			cout<<"a[]:";
			for(int i=0;i<len;++i){
				cout<<a[i]<<" ";
			}cout<<endl;
		cout<<"=============kb============="<<endl;
#endif
            for(int k = j; k < j + h / 2; k++)  
            {
                LL u = a[k] % P;  
                LL t = w * a[k + h / 2] % P;  
                a[k] = (u + t) % P;  
                a[k + h / 2] = (u - t + P) % P;  
                //w = w * wn[id] % P;  
				w=w*wn_n%P;
#if debug_NTT
				cout<<"k:"<<k<<endl;
				cout<<"u(a[k]%P):"<<u<<endl;
				cout<<"t(w*a[k+h/2]%P):"<<t<<endl;
				cout<<"a[k]((u+t)%P):"<<a[k]<<endl;
				cout<<"a[k+h/2]((u-t+P)%P):"<<a[k+h/2]<<endl;
				cout<<"wn[id]:"<<wn[id]<<endl;
				cout<<"w(w*wn%P):"<<w<<endl;
#endif 
            }  
#if debug_NTT
		cout<<"=============ke============="<<endl;
#endif
        }  
#if debug_NTT
		cout<<"=============je============="<<endl;
#endif
    }   
#if debug_NTT
		cout<<"=============he============="<<endl;
#endif 
    if(on == -1)  
    {  
        for(int i = 1; i < len / 2; i++)  
            swap(a[i], a[len - i]);  
        LL inv = quick_mod(len, P - 2, P);  
        for(int i = 0; i < len; i++)  
            a[i] = a[i] * inv % P;  
    }  
}  
  
void Conv(LL a[], LL b[], int n)  
{  
    NTT(a, n, 1);  
    NTT(b, n, 1);  
    for(int i = 0; i < n; i++)  
        a[i] = a[i] * b[i] % P;  
    NTT(a, n, -1);  
}  
  
void Transfer(LL a[], int n)  
{  
    int t = 0;  
    for(int i = 0; i < n; i++)  
    {  
        a[i] += t;  
        if(a[i] > 9)  
        {  
            t = a[i] / 10;  
            a[i] %= 10;  
        }  
        else t = 0;  
    }  
}  
  
void Print(LL a[], int n)  
{  
    bool flag = 1;  
    for(int i = n - 1; i >= 0; i--)  
    {  
        if(a[i] != 0 && flag)  
        {  
            //使用putchar()速度快很多  
            putchar(a[i] + '0');  
            flag = 0;  
        }  
        else if(!flag)  
            putchar(a[i] + '0');  
    }  
    puts("");  
}  
  
int main()  
{  
    GetWn();  
    while(scanf("%s %s", A, B) != EOF)  
    {  
        int len;  
        Prepare(A, B, a, b, len);  
        Conv(a, b, len);  
        Transfer(a, len);  
        Print(a, len);  
    }  
    return 0;  
}  