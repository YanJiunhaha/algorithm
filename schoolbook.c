#include<math.h>
#include"schoolbook.h"
int Log2(int n){
	double ans=log(n)/log(2);
	return (ans>(int)ans)?(int)ans+1:(int)ans;
}

int schoolbook(int a,int b){
	int sum=0;
	int n=Log2(b);
	for(int i=0;i<n;++i){
		if(b&1)sum+=(a<<i);
		b>>=1;
	}
	return sum;
}

#define debug 0
#if debug
	#include<stdio.h>
	int main (){
		int a,b;
		a=2;b=9;
		int ans=schoolbook(a,b);
		printf("%d",ans);
		return 0;
	}
#endif