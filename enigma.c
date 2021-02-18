/////////////////////// ENIGMA MODEL 1 (ARMY) ///////////////////////

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

static int* ring; // Grundstellung
static int* grun; // Ringstellung

//                 abcdefghijklmnopqrstuvwxyz
static char* r1 = "ekmflgdqvzntowyhxuspaibrcj"; // Rotor I
static char* r2 = "ajdksiruxblhwtmcqgznpyfvoe"; // Rotor II
static char* r3 = "bdfhjlcprtxvznyeiwgakmusqo"; // Rotor III
static char* rf = "yruhqsldpxngokmiebfzcwvjat"; // Reflector UKW B
static char* bd = "aqrijfhgdewltnsxbcomzvkpyu"; // Plug Board

// Allows for rotor to substitute letters in opposite direction.
char pos(char* rotor, char l) {
	for(int i = 0; rotor[i] != '\0'; i++)
		if(rotor[i] == l)
			return i+97;
	return '#';
}

// Allows for x mod 26 to work if x >= -26.
int m26(int x) {return (x+26)%26;}

char plug(char l) {
	// bq cr di ej gh kw mt os px uz
	return bd[l-97];
}

// Shifts the wire connections, relative to the letter positions,
// down depending on  Grundstellung.
void ringset() {
	char* a1 = malloc(26*sizeof(char));
	char* a2 = malloc(26*sizeof(char));
	char* a3 = malloc(26*sizeof(char));
	
	for(int i = 0; i < 26; i++) {
		a1[i] = m26(r1[m26(i-ring[0])]-97+ring[0])+97;
		a2[i] = m26(r2[m26(i-ring[1])]-97+ring[1])+97;
		a3[i] = m26(r3[m26(i-ring[2])]-97+ring[2])+97;
	}
	
	r1 = a1; r2 = a2; r3 = a3;
}


// Rotates rotors accourding to current position.
void step() {
	grun[0] = (grun[0]+1)%26;
	if(grun[0] == 17)
		grun[1] = (grun[1]+1)%26;
	else if(grun[1] == 4) {
		grun[2] = (grun[2]+1)%26;
		grun[1] = (grun[1]+1)%26;
	}
	if(grun[2] == 22)
		grun[1] = (grun[1]+1)%26;
}

// Sends signal through multiple components; substituting the letter
// at each part.
//
// input -> plug board -> 1st rotor -> 2nd rotor -> 3rd rotor ->
// reflector -> 3rd rotor -> 2nd rotor -> 1st rotor plug board ->
// output
char crypt(char l) {
	step();
	l = plug(l);
	
	l = r1[m26(l-97+grun[0])];
	l = r2[m26(l-97+grun[1]-grun[0])];
	l = r3[m26(l-97+grun[2]-grun[1])];
	
	l = rf[m26(l-97-grun[2])];
	
	l = pos(r3,m26(l-97+grun[2])+97);
	l = pos(r2,m26(l-97+grun[1]-grun[2])+97);
	l = pos(r1,m26(l-97+grun[0]-grun[1])+97);
	
	return plug(m26(l-97-grun[0])+97);
}

int main(void) {
	char mess[256];
	char* set = malloc(6*sizeof(char));
	ring = malloc(3*sizeof(int));
	grun = malloc(3*sizeof(int));
	char board[27] = "abcdefghijklmnopqrstuvwxyz";
	char* words = malloc(39*sizeof(char));
	
	printf("Plug Board\t-> ");
	fgets(words,39,stdin);
	
	printf("Grundstellung\t-> ");
	scanf("%c%c%c",&set[0],&set[1],&set[2]);
	
	printf("Ringstellung\t-> ");
	fgets(mess, 256, stdin);
	scanf("%c%c%c",&set[3],&set[4],&set[5]);
	
	printf("Message\t\t-> ");
	fgets(mess, 256, stdin);
	fgets(mess, 256, stdin);
	int size = strlen(mess);
	
	for(int i = 0; i < 26; i++) {
		int n = -1;
		for(int j=0; j<39 && words[j]!='\n'; j++) {
			if(words[j]==board[i]) {
				n = j;
				break;
			}
		}
		if(n < 0) continue;
		if(isalpha(words[n+1])) board[i] = words[n+1];
		else board[i] = words[n-1];
	}
	
	bd = board;
	free(words);
	
	for(int i = 0; i < 3; i++) {
		grun[i] = set[i]-97;
		ring[i] = set[i+3]-97;
	}
	
	ringset();
	
	printf("\n");
	for(int i = 0, h = 0; i < size; i++) {
		if(isalpha(mess[i])) {
			printf("%c", crypt(tolower(mess[i])));
			if(h%30 == 29 && h != 0) printf("\n");
			else if(h%5 == 4 && h != 0) printf(" ");
			h++;
		}
	}
	if(! (size-1)%30 == 0) printf("\n");
}
