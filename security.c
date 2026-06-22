#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>
#include<time.h>

struct User{
    char name[20];
    char password[20];
    int role; // 0: user, 1: admin
    int state; // 0: active, 1: blocked
};
int countUppercase(char text[]){ 
    int s=0;
    for(int i=0; i<strlen(text); i ++){
        if( 65<=(int)text[i] && (int)text[i]<=90){
            s++;
        }
    }    
    return s;
}
int countLowercase(char text[]){
    int c=0;
    for(int i=0; i<strlen(text); i++){
        if(text[i]>96 && text[i]<123){
            c++;
        }
    }
    return c;
}
int countDigits(char text[]){
    int s=0;
    for (int i=0; i<strlen(text); i++){
        if(text[i]<=57 && 48<=text[i]){
            s++;
        }   
    }
    return s;
}
float percentUppercase(char text[]){
    int c=0;
    for(int i=0; i<strlen(text); i++){
       if(text[i]>64 && text[i]<91){
            c++;
       }
    }
    return c/(strlen(text)-1) ;
}
int textLength(char text[]){
    int c=0;
    for(int i=0; text[i] != '\0'; i++){
        c++;
    }
    return c;
}
int veryStrongPassword(char pass[]){
    int s=strlen(pass);
    if(s>7){
        bool Uc=false, Lc=false, D=false, sp=false, space=true;
        for(int i=0; i<s; i++){
            int c=(int)pass[i];
            if(65<=c && c<=90){
                Uc=true;
            }
            if( 97<=c && c<=122){
                Lc=true;
            }
            if( c<=57 && c>=48){
                D=true;
            }
            if((c<65 || (c<97 && 90<c) || c>122) && c!= 32 && c!= 13){
                sp=true;
            }
            if(c==32){
                space=false;
            }
            printf("%d, %d, %d, %d, %d\n", Uc, Lc, D, sp, space);
        }
        if(Uc && Lc && D && sp && space){
            return 1;
        }else{
            return 0;
        }
    }else{
        return 2;
    }
}
int isHexKey(char key[]){
    for( int i=0; i<strlen(key)-1; i++){
        char a=key[i];
        if(a!='1' && a!='2' && a!='3' && a!='4' && a!='5' && a!='6' && a!='7' && a!='8' && a!='9' && a!='0' && a!='A' && a!='B' && a!='C' && a!='D' && a!='E' && a!='F'){
            return 0;
        }
    }
    return 1;
}
int passwordScore(char pass[]){
    int score=4*(strlen(pass)-1);
    if(strlen(pass)-1 <8){
        score -=15;
    }
    bool b=false, c=false, d=false, e=false;
    for(int i =0; i<strlen(pass)-1; i++){
        if(pass[i]<91 && pass[i]>64){
            b=true;
        }else if(pass[i]<123 && pass[i]>96){
            c=true;
        }else if(pass[i]<58 && pass[i]>47){
            d=true;
        }else{
            e=true;
        }
    }
    if(b){score +=10;}else if(~c){score -=15;}
    if(c){score +=10;}
    if(d){score +=10;}else{score -=15;}
    if(e){score +=10;}
    if(strcmp(pass, "password")==0 || strcmp(pass, "admin")==0 || strcmp(pass, "1234567890")==0){
        score -=10;
    }
    int a=0;
    for(int i=0; i<strlen(pass)-2; i++){
        if(pass[i]==pass[i+1]){
            a++;
        }
    }
    if(a==strlen(pass)-1){
        score -=10;
    }

    return score;
} 
void displaySecurityReport(struct User users[], int n){
    
    for(int i=0; i<n; i++){
        printf("the user name is: %s", users[i].name);
        printf("the password score is: %d\n", passwordScore(users[i].password));
        printf("the status of the password is: ");
        if(passwordScore(users[i].password)<=30){
            printf("Very weak\n");
        }else if(passwordScore(users[i].password)<=50){
            printf("Weak\n");
        }else if(passwordScore(users[i].password)<=70){
            printf("Medium\n");
        }else if(passwordScore(users[i].password)<=90){
            printf("Strong\n");
        }else{
            printf("Very Strong\n");
        }
        printf("the account status is: "); if(users[i].state==1){printf("blocked\n");}else{printf("active\n");}
        printf("the account role is: "); if(users[i].role==1){printf("admin\n");}else{printf("user\n");}
        printf("\n================================================\n");
    }
}
void showSecurityTips(){
    printf("1-Account Creation:\nUse strong, complex passwords\nApply least privilege—give only needed access\nOne account per user; avoid shared accounts\nConfirm passwords during setup\nCreate accounts over secure channels (HTTPS/SSH)\n2-Account Management:\n\nLock accounts after failed login attempts\nAudit and remove inactive accounts regularly\nMonitor login activity for unusual behavior\nUse multi-factor authentication (MFA)\nSecure admin accounts; separate from normal users\n3-Password Handling:\n\nNever store passwords in plain text\nUse hashed and salted passwords\nEnforce periodic password updates if necessary");
}
int checkLoginFormat(char name[]){
    struct User users[20]; int n; scanf("%d", &n);
    for(int i=0; i<n; i++){
        scanf("%s %s %d %d", users[i].name, users[i].password, &users[i].role, &users[i].state);
    }
    char password[20];
    int c; while((c=getchar() != '\n') && c!= EOF);
    fgets(password, 20 ,stdin);
    for(int i=0; i<n; i++){
        if(strcmp(users[i].name, name)==0 && strcmp(users[i].password, password)==0){
            printf("loggin successfuly\n");
            return 1;
        }
    }
    return 0;
}
void top3Passwords(struct User users[], int n){
    int I=-1;
    for(int j=0; j<3; j++){
        int top=0;
        for(int i=0; i<n; i++){
            int a=passwordScore(users[i].password);
            if(a>top && i!= I){
                top=a;
                I=i;
            }
        }
        printf("the password number %d is: %s\n",j+1,users[I].password);
    }
}
void displayTextStats(char text[]){
    int n=0;
    for(int i=0; i<strlen(text); i++){
        if(text[i]== '\n' || text[i]== ' ' || text[i]== '\t'){
            n++;
        }
    }
    printf("the number of words in the text is: %d\n", n+1);
    printf("the number of letters in the text is: %d\n", textLength(text)-n);
    printf("the number of uppercase letters in the text is: %d\n", countUppercase(text));
    printf("the number of lowercase letters in the text is: %d\n", countLowercase(text));
    printf("the number of digits in the text is: %d\n", countDigits(text));
}
void generateKey(int length, char key[]){
    const char hexChars[] = "0123456789ABCDEF";
    for(int i=0; i<length; i++){
        int index = rand() % 16;
        key[i] = hexChars[index];
    }
    key[length] = '\0';
}
void generateRandomPassword(int length, char pass[]){
    const char chars[]="ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789!@#$^&*()";
    for(int i=0; i<length; i++){
        int index= rand()%70;
        pass[i]=chars[index];
    }
    pass[length]='\0';
}
float averageScore(struct User Users[], int n){
    int total=0; 
    for(int i=0; i<n; i++){
        if(Users[i].state==0){
            total += 1;
        }
    }
    return total/n;
}
int globalSecurityLevel(struct User users[], int n) {
    int i;
    int tot;
    tot=0;
    if (n == 0){
   return 0;
  } 
    for (i = 0; i < n; i++) {
        tot = tot + passwordScore(users[i].password);
    }
    
    return tot / n;
}
void generateHexKey(int length, char key[]) {
    int i, r;

    char hex[] = "0123456789ABCDEF";

    for (i = 0; i < length; i++) {
        r = rand() % 16;   
        key[i] = hex[r];   
    }
    key[length] = '\0';  
}
int countStrongUsers(struct User users[], int n) {
    int i;
    int count = 0;

    for (i = 0; i < n; i++) {
        if (veryStrongPassword(users[i].password) == 1) {
            count++;
        }
    }

    return count;
}

int checkEmailFormat(char email[]) {
    int i, atPos = -1, dotPos = -1;
    int len = strlen(email);

    for (i = 0; i < len; i++) {
        if (email[i] == '@') {
            atPos = i; 
        }
        if (email[i] == '.') {
            dotPos = i; 
        }
    }

    if (atPos > 0 && dotPos > atPos + 1 && dotPos < len - 1) {
        return 1;
    }

    return 0;
}
