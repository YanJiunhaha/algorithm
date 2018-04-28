#define recursive 1
#if recursive
	int gcd(int a,int b){
		if(a==0)return b;
		return gcd(b%a,a);
	}
#else
	int gcd(int a,int b){
		int c;
		while(a!=0){
			c=a;
			a=b%a;
			b=c;
		}
		return b;
	}
#endif




#define define debug 0
#if debug
	#include<stdio.h>

	int main(int argc,char **argv){
		int a=26,b=58;
		printf("%d",gcd(a,b));
		return 0;
	}
#endif