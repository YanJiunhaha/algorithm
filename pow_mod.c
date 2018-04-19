#include".\include\pow_mod.h"

inline int pow_mod(int a,int b,int m){
	int ans=1;
	a%=m;
	while(b){
		if(b&1){
			ans=ans*a%m;
			b-=1;
		}
		b>>=1;
		a=a*a%m;
	}
	return ans;
}


#define debug 0
#if debug
	#include<stdio.h>
	
	int main(){
		printf("%d",pow_mod(2,3,5));
		return 0;
	}
#endif