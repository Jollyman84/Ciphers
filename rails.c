#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(void) {
	char mess[100];
	int rails;
	
	printf("Rails\t-> ");
	scanf("%i",&rails);
	
	// 4 rails
	// hello my name is bill
	// hmeie ym bllo ai llns
	
	printf("Message\t-> ");
	fgets(mess, 100, stdin);
	fgets(mess, 100, stdin);
	int len = strlen(mess)-1;
	
	if(rails < 2 || rails > len/2) {
		printf("Error\t-> Inappropriate about of rails\n");
		return 0;
	}
	
	char m[rails][(100/rails)+2];
	for(int i = 0; i < rails; i++)
		for(int j = 0; j < (100/rails)+2; j++)
			m[i][j] = '\0';
	
	short cross = 2*rails-2;
	short n[cross];
	for(int d = 0; d < rails; d++)
		n[d] = d;
	for(int d = rails-2; d > 0; d--)
		n[cross-d] = d;
	
	short p[rails];
	for(int d = 0; d < rails; d++)
		p[d] = 0;
	for(int t = 0; t < len; t++) {
		m[n[t%cross]][p[n[t%cross]]] = mess[t];
		p[n[t%cross]]++;
	}
	
	printf("Cipher\t-> ");
	for(int d = 0; d < rails; d++) {
		m[d][p[d]] = '\0';
		printf("%s",m[d]);
	}
	printf("\n");
}
