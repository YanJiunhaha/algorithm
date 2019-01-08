#include<stdlib.h>
#include<stdio.h>
static inline void swap(char* a, char* b){
	*a ^= *b; *b^=*a; *a^=*b;
}

char* reserse(char* s){
	if((*s == '\0') || (*(s+1) == '\0'))
		return NULL;
	reserse(s+1);
	swap(s,(s+1));
	if(reserse(s+2) != '\0')
		reserse(s+2);
	reserse(s+1);
}

int rev_core(char* head, int idx){
	if(head[idx] != '\0'){
		int end = rev_core(head, idx+1);
		if(idx > end/2)
			swap(head+idx, head+end-idx);
		return end;
	}
	return idx-1;
}

int main(){
	char str[]="yanjiun";
	reserse(str);
	printf("%s\n",str);
	int lenght = rev_core(str,0);
	printf("lenght:%d,str=%s\n",lenght,str);

	return 0;
}
