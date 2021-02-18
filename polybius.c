#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(void) {
	char mess[100];
	char cm[200];
	printf("Message\t-> ");
	fgets(mess, 100, stdin);
	int len = strlen(mess)-1;
	
	int c = 0;
	for(int t = 0; t < len; t++) {
		if(mess[t]>64 && mess[t]<91)
			mess[t] += 32;
		if(mess[t] > 'i')
			mess[t] -= 1;
		if(mess[t]>96 && mess[t]<123) {
			cm[2*c] = (mess[t]-97)%5+49;
			cm[2*c+1] = (mess[t]-97)/5+49;
			c++;
		}
	}
	cm[2*c] = '\0';
	//44513444
	printf("Cipher\t-> %s\n", cm);
}
