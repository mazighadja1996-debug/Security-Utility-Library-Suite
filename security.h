#ifndef SEC_H
#define SEC_H
struct User{ 
  char name[20]; 
  char password[20]; 
  int role;   // 0: user, 1: admin 
  int state;  // 0: active, 1: blocked 
 }; 
int countUppercase(char text[]); 
int countLowercase(char text[]); 
int countDigits(char text[]); 
float percentUppercase(char text[]);
int textLength(char text[]); 
void displayTextStats(char text[]); 
int veryStrongPassword(char pass[]); 
void generateKey(int length, char key[]); 
int isHexKey(char key[]); 
void generateRandomPassword(int length, char pass[]); 
int passwordScore(char pass[]); 
float averageScore(struct User users[], int n); 
void displaySecurityReport(struct User users[], int n); 
int countStrongUsers(struct User users[], int n); 
void showSecurityTips(); 
int checkEmailFormat(char email[]); 
int checkLoginFormat(char name[]); 
void generateHexKey(int length, char key[]); 
void top3Passwords(struct User users[], int n); 
int globalSecurityLevel(struct User users[], int n); 
#endif