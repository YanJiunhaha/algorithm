#include "bit_reverse.h"

inline unsigned int bit_reverse(unsigned int a,int len){
	a=((a&0x55555555U)<<1)|((a&0xAAAAAAAAU)>>1);
	a=((a&0x33333333U)<<2)|((a&0xCCCCCCCCU)>>2);
	a=((a&0x0F0F0F0FU)<<4)|((a&0xF0F0F0F0U)>>4);
	a=((a&0x00FF00FFU)<<8)|((a&0xFF00FF00U)>>8);
	a=((a&0x0000FFFFU)<<16)|((a&0xFFFF0000U)>>16);
	return a>>(32-len);
}  


#define debug 0
#if debug
	#include<stdio.h>

	int main(){
		for(int i=0;i<8;++i){
			printf("%d\n",bit_reverse(i,3));
		}
		return 0;
	}
#endif