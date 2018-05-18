//#include"basis.h"
#include<stdlib.h>
#include<math.h>

int logb(int n,int b){
	double ans=log(n)/log(b);
	return (ans>=(int)ans)?(int)ans+1:(int)ans;
}

int* basis(int in,int len,int *elen){
	int i,e;
	*elen=e=logb(in,len);
	int *arr;
	arr=(int*)malloc(sizeof(int)*e);
	if(arr==NULL)return NULL;
	for(i=0;i<e;++i){
		*(arr+i)=in%len;
		in/=len;
	}
	return arr;
}


#define debug 0
#if debug

	#include<stdio.h>
	int main(){
		int a=128;
		int *len=(int*)malloc(sizeof(int));
		int *num=basis(a,128,len);
		printf("%d\n",*len);
		for(int i=0;i<*len;++i){
			printf("%d\t",*(num+i));
		}
		free(num);
		return 0;
	}

#endif