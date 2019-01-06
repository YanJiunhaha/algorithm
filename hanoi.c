#include<stdio.h>

void hanoi(int n, char* a, char* b, char* c){
	if (n == 1){
		// 只有一個盤子
		printf("將盤子從 %s 搬移到 %s。\n", a, c);
	} else {
		hanoi(n - 1, a, c, b);
		hanoi(1, a, b, c);
		hanoi(n - 1, b, a, c);
	}
}

int main(){
	//河內塔
	char *a = "塔A";
	char *b = "塔B";
	char *c = "塔C";
	hanoi(3, a, b, c);
	return 0;
}
