#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(void) {
	char mess[100];
	char shift[26];
	
	printf("Text\t-> abcdefghijklmnopqrstuvwxyz\nKey\t-> ");
	fgets(shift, 27, stdin);
	for(int k = 0; k < 26; k++)
		if(shift[k] < 96)
			shift[k] += 32;
	
	for(int y = 97; y < 123; y++) {
		if(index(shift,y) == NULL) {
			printf("Error\t-> Invalid Key\n");
			return 0;
		}
	}
		
	printf("Message\t-> ");
	fgets(mess, 100, stdin);
	fgets(mess, 100, stdin);
	
	int len = strlen(mess) - 1;
	mess[len] = '\0';
	
	for(int i = 0; i < len; i++) {
		if(mess[i]>64 && mess[i]<91)
			mess[i] = shift[mess[i]-65]-32;
		else if(mess[i]>96 && mess[i]<123)
			mess[i] = shift[mess[i]-97];
	}
	
	printf("Cipher\t-> %s\n", mess);
}
