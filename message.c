#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"message.h"

Message create_message(const char *text){
	Message m;
	m.size=strlen(text);
	m.text=malloc(m.size+1);
	strcpy(m.text, text);
	return m;
}

void inputMessage(struct Message m[]){
	char message[200];
    printf("enter your message: ");
    scanf(" %[^\n]s", message);
    // [0] is the number or the order of the struct 0 means the first and 1 means the second and so on
    strcpy(m[0].text, message);
    m[0].size=strlen(message);
}
void displayMessage(struct Message m[]){
    inputMessage(m);
    printf("%s\n", m[0].text);
}
int isUppercase(char c){
	int a;
	a=(int)c;
	if(a>='A'&& a<='Z'){
		printf("it is an upper case");
	}else{
		printf("it is not an upper case");
	}
	return a;
}
int isLowercase(char C){
	int b;
	b=(int)C;
	if(b<='z'&& b>='a'){
		printf("it is a lower case");
	}else{
		printf("it is not a lower case");
	}
	return b;
}
int isAlphabitical(char a){
	int b;
	b=(int)a;
	if((b>='a' && b<='z') || (b<='Z' && b>='A')){
		printf("it is a letter");
	}else{
		printf("it is not a letter");
	}
	return b;
}
void toUppercase(struct Message m[]){
	for(int i=0; i<=strlen(m[0].text)-1; i++){
		if(((int)m[0].text[i]<'a') || ((int)m[0].text[i]>'z')){
			i=i+1;
		}
		else {
		int a=(int)m[0].text[i];
		a=a-32;
		m[0].text[i]=(char)a;
		}
	}
	m[0].text[m[0].size]='\0';
	printf("%s", m[0].text);
}
void toLowercase(struct Message m[]){
	for(int i=0; i<=m[0].size-1; i++){
		if(((int)m[0].text[i]<'A') || ((int)m[0].text[i]>'Z')){
			i=i+1;
		}
		else{
		int a=(int)m[0].text[i];
		a=a+32;
		m[0].text[i]=(char)a;
		}
	}
	m[0].text[m[0].size]='\0';
	printf("%s", m[0].text);
}
void reverseMessage(struct Message m[]){
	char message[100];
	fgets(message, 100, stdin);
    m[0].size=strlen(message);
    int j=strlen(message)-2;
	for(int i=0; i<strlen(message); i++){
        m[0].text[i]=message[j];
        j--;
    }
	printf("%s\n", m[0].text);
}   
void removeSpaces(struct Message m[]) {
    int i = 0; 
    int j = 0; 
    while (m[0].text[i] != '\0') {
        if (m[0].text[i] != ' ') {
            m[0].text[j] = m[0].text[i];
            j++;
        }
        i++;
    }
    m[0].text[j] = '\0';
	printf("%s", m[0].text);
}
void encryptCesar(struct Message m[], int key){
	for(int i=0; i<m[0].size; i++){
		int a=((int)m[0].text[i]+key-'A')%26+'A';
		m[0].text[i]=(char)a;
	}
	printf("%s", m[0].text);
}
//////////////////////////////////////////////////////////////////////
void decryptCesar(struct Message m[], int key){
	for(int i=0; i<m[0].size; i++){
		int a=((int)m[0].text[i]-key+'A')%26-'A';
		m[0].text[i]=(char)a;
	}
	printf("%s", m[0].text);
}
void XORencryption(struct Message m[], int key){
	for(int i=0; i<m[0].size-1; i++){
		int a=(int)m[0].text[i];
		int b=(a & ~key) | (~a & key);
		m[0].text[i] = (char)b;
	}
	printf("%s", m[0].text);
}
void XORdecryption(struct Message m[], int key){
	for(int i=0; i<m[0].size-1; i++){
		int a=(int)m[0].text[i];
		int b=(a & ~key) | (~a & key);
		m[0].text[i] = (char)b;
	}
	printf("%s", m[0].text);
}
void encryptSubstitution(struct Message m[], char key[26]){
    //the key is qwertyuiopasdfghjklzxcvbnm
	char letters[26]={"abcdefghijklmnopqrstuvwxyz"};
	long indexes[m[0].size];
    for(long i=0; i<26; i++){
        for(long j=0; j<m[0].size; j++){
            if(m[0].text[i]==letters[j]){
                indexes[i]=i;
            }
        }
    }
	for(long i=0; i<m[0].size; i++){
		m[0].text[i]=key[indexes[i]];
	}
	printf("%s", m[0].text);
}
void decryptionSubstitution(struct Message m[], char key[26]){
	//the key is qwertyuiopasdfghjklzxcvbnm
	char letters[26]={"abcdefghijklmnopqrstuvwxyz"};
	long indexes[m[0].size];
	for(long i=0; i<26; i++){
		for(long j=0; j<m[0].size; j++){
			if(m[0].text[i]==key[j]){
				indexes[i]=i;
			}
		}
	}
   
	for(long i=0; i<m[0].size; i++){
		m[0].text[i]=letters[indexes[i]];
	}
	printf("%s", m[0].text);
}
int isValidKey(char key[26]){
	int validation;
	if(strlen(key)>16){
		validation=1;
	}else{
		validation=0;
	}
	
	return validation;
} 
int compareMessage(struct Message m1[], struct Message m2[]){
	int comp = 0; 
	if(m1[0].size==m2[0].size){
		int i;
		for(i=0; i<m1[0].size; i++){
			if(m1[0].text[i]!=m2[0].text[i]){
				break;
			}
		}

		if(i==m1[0].size){
			comp=1;
		}
	}
	
	return comp; 
}
int counterCharacter(struct Message m[], char c){
	int oc;
	fgets(m[0].text, 200, stdin);
    m[0].size=strlen(m[0].text);
	oc=0;
	for(int i=0; i<m[0].size; i++){
		if(m[0].text[i]==c){
			oc++;
		}
	}
	return oc;
}
void frequencyAnalysis(struct Message m[]){
	int l, freq;
	char c, A;
	fgets(m[0].text, 30, stdin);
    m[0].size=strlen(m[0].text);
	A='a';
	while(A<'z'){
		freq=0;
		for(int i=0; i<m[0].size; i++){
			if(m[0].text[i]==A){
				freq=freq+1;			
			}
		}
		printf("the frequency of %c is %d\n", A, freq);
		A=(char)(((int)'a')+1);
	}
}
int coincidenceIndex(struct Message m[]){
    char M[30]; fgets(M, 30, stdin);
    strcpy(m[0].text, M);
    m[0].size=strlen(M);
    char A='a';
    int sum=0;
	while((int)A<(int)'z'){
		int freq=0;
		for(int i=0; i<m[0].size; i++){
			if(m[0].text[i]==A){
				freq=freq+1;			
			}
		}
		sum=sum+(freq*(freq-1));
		A=(char)(((int)A)+1);
	}
	int IC=(int) sum/(m[0].size*(m[0].size-1));

    return IC;
}

void free_message(Message *m){
	free(m->text);
}
