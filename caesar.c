#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(void) {
	char mess[100];
	int shift;
	
	printf("Shift\t-> ");
	scanf("%i", &shift);
	
	printf("Cipher\t-> ");
	fgets(mess, 100, stdin);
	fgets(mess, 100, stdin);
	
	int len = strlen(mess) - 1;
	mess[len] = '\0';
	
	for(int i = 0; i < len; i++) {
		if(mess[i]>64 && mess[i]<91)
			mess[i] = (mess[i]-65+shift)%26+65;
		else if(mess[i]>96 && mess[i]<123)
			mess[i] = (mess[i]-97+shift)%26+97;
	}
		
	printf("Message\t-> %s\n",mess);
}
