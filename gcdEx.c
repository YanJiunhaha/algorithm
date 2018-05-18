int gcdEx(int a, int b, int *x, int *y) 
{
    if(b==0)
    {
        *x = 1,*y = 0;
        return a;
    }
    else
    {
        int r = gcdEx(b, a%b, x, y); /* r = GCD(a, b) = GCD(b, a%b) */
        int t = *x;
        *x = *y;
        *y = t - a/b * *y;
        return r;
    }
}
#define debug 0
#if debug
	#include<stdio.h>
	int main(){
		int a=3,b=9;
		int x,y;
		printf("%d",gcdEx(a,b,&x,&y));
		return 0;
	}
#endif