#ifndef MESSAGE_H
#define MESSAGE_H
typedef struct Message {
    char* text;
    int size;
}Message;

void inputMessage(struct Message m[]);
void displayMessage(struct Message m[]);
int isUppercase(char c);
int isLowercase(char C);
int isAlphabitical(char a);
void toUppercase(struct Message m[]);
void toLowercase(struct Message m[]);
void reverseMessage(struct Message m[]);
void removeSpaces(struct Message m[]);
void encryptCesar(struct Message m[], int Key);
void decryptCesar(struct Message m[], int Key);
void XORencryption(struct Message m[], int Key);
void XORdecryption(struct Message m[], int Key);
void encryptSubstitution(struct Message m[], char key[26]);
void decryptionSubstitution(struct Message m[], char key[26]);
int isValidKey(char key[26]); 
int compareMessage(struct Message m1[], struct Message m2[]);
int counterCharacter(struct Message m[], char c);
void frequencyAnalysis(struct Message m[]);
int coincidenceIndex(struct Message m[]);
#endif