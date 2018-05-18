#include<stdio.h>
#include<stdlib.h>
#include<math.h>

int comba(int* a,int* b,int n,int d){
	int ans=0;
	int *pp;
	pp=(int*)malloc(sizeof(int)*n*2-2);
	if(pp==NULL){return -1;}
	
	int i,j,sum;
	 for(i=0;i<=2*n-2;++i){
		 sum=0;
		if(i>n){
			for(j=0;j<=i-1;++j){
				int tempa=(j<n)?a[j]:0;
				int tempb=(i-j>0 && i-j<n)?b[i-j]:0;
				// if(tempb<0)printf("%d\t%d\n",i,j);
				sum+=tempa*tempb;
				// printf("%d*%d=%d\n",tempa,tempb,sum);
			}
			pp[i]=sum;
		}else{
			for(j=0;j<=n-1;++j){
				int tempa=(j<n)?a[j]:0;
				int tempb=(i-j>0 && i-j<n)?b[i-j]:0;
				sum+=tempa*tempb;
				// printf("%d*%d=%d\n",tempa,tempb,sum);
			}
			pp[i]=sum;
		}
	}
	
	for(int i=0;i<=2*n-2;++i){
		ans+=(pp[i]*pow(d,i));
	}
	
	free(pp);
	return ans;
}


#define debug 1

#if debug
	#include<stdio.h>
	#include<stdlib.h>
	#include<string.h>
	
	#include".\include\basis.h"
	int main(){
		int a=128,a_len,b=4,b_len;
		const int base=2;
		int *aArr,*bArr;
		aArr=basis(a,base,&a_len);
		bArr=basis(b,base,&b_len);
		int max_len=(a_len>b_len)?a_len:b_len;
		
		if(a_len<max_len){
			aArr=(int*)realloc(aArr,max_len*sizeof(int));
			memset(aArr+a_len,0,max_len*sizeof(int));
			a_len=max_len;
		}
		else if(b_len<max_len){
			bArr=(int*)realloc(bArr,max_len*sizeof(int));
			memset(bArr+b_len,0,max_len*sizeof(int));
			b_len=max_len;
		}
		
		// for(int i=0;i<a_len;++i)printf("%d\t",*(aArr+i));
		// printf("\n");
		// for(int i=0;i<b_len;++i)printf("%d\t",*(bArr+i));
		
		int ans;
		ans=comba(aArr,bArr,max_len,base);
		
		printf("%d",ans);
		
		free(aArr);
		free(bArr);
		return 0;
	}

#endif 