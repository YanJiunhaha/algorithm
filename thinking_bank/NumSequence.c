#include<stdio.h>
#include<limits.h>

int p(int i, int N){
	return (i < N && printf("%d\n", i) && !p(i + 1, N)) || printf("%d\n", i);
}

int main(){
	p(0,INT_MAX);
	return 0;
}
