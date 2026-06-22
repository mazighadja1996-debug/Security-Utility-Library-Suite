#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include <stdbool.h>
struct User{ 
  char name[20]; 
  char password[20]; 
  int role;   // 0: user, 1: admin 
  int state;  // 0: active, 1: blocked 
 }; 

int strongPassword(char pass[]){
	int i,s,l,up,low,d;
	up=0;
	low=0;
	d=0;
	l=strlen(pass);
	if(l<8){
		return 0;
	}
	for (i=0;i<l;i++){
		if (pass[i]>= 'A' && pass[i] <= 'Z'){
			up=1;
		}
		else{
			if(pass[i]>= 'a' && pass[i] <= 'z'){
				low=1;
			}
			else{
				d=1;
			}
		}
	}
	s=up+low+d;
	if(s!=3){
		return 0;
	}
	return 1;
}

void unblockUser(struct User users[], int n, char name[]){
	int i,f;
	f=0;
	for (i=0;i<n;i++){
		if(strcmp(users[i].name,name)==0){
			users[i].state=0;
			printf("User %s has been unblocked.\n", name);
			f=1;
			break;
		}		
	}
	if (f==0) {
        printf("User %s not found in the database.\n", name);
    }
	
}

void listAdmins(struct User users[], int n){
	int i,c;
	c=1;
	for (i=0;i<n;i++){
		if (users[i].role==1){
			printf("the admin %d : %s\n",c,users[i].name);
			c++;
		}
	}
	if(c==1){
		printf("no admin found");
	}
}

int containsUppercase(char str[]){
	int i;
	for (i=0;i<strlen(str);i++){
		if(str[i]>= 'A' && str[i] <= 'Z'){
			return 1;
		}
	}
	return 0;
}

int containsDigit(char str[]){
	int i;
	for (i=0;i<strlen(str);i++){
		if(str[i]>= '0' && str[i] <= '9'){
			return 1;
		}
	}
	return 0;
}

void userStatistics(struct User users[], int n){
	int i,u,ad,ac,b;
	float  l;
	l=n;
	u=0;
	ad=0;
	ac=0;
	b=0;
	if (n==0){
		printf("The system is currently empty.\n");
        return;
	}
	for(i=0;i<n;i++){
		if(users[i].role==1){
			ad++;
		}
		else{
			u++;
		}
		if(users[i].state==0){
			ac++;
		}
		else{
			b++;
		}
	}
	printf("the number of simple user(s) is :%d represent %.2f %%\n",u,(u*100)/l);
	printf("the number of admin  user(s) is :%d represent %.2f %%\n",ad,(ad*100)/l);
	printf("the number of active user(s) is :%d represent %.2f %%\n",ac,(ac*100)/l);
	printf("the number of blocked user(s) is :%d represent %.2f %%\n",b,(b*100)/l);
} 

void loadUsers(struct User users[], int *n){
	int i;
	char filename[50];
	printf ("enter you file name please :");
	scanf ("%s",filename);
	FILE *f = fopen(filename, "r");
	if (f == NULL) {
        printf("Error: Could not find a valid file named %s\n", filename);
        return;
    }
	if (n<=0){
		printf("erorr : no user has been loaded");
		fclose(f);
		return;
	}
	int count = 0;
    while (fscanf(f, "%19s %19s %d %d", users[count].name, users[count].password, &users[count].role, &users[count].state) == 4) {
        count++;
    }
	*n = count;
	fclose(f);
}
////////////////////////////////////////////////////////////////////////////
void initUsers(struct User *users, int n){
    for(int i=0; i<n; i++){
        printf("enter your user name: ");
        scanf("%s", users[i].name);
        printf("enter your password: ");
        scanf("%s", users[i].password);               
        printf("enter 0 if it is a normal user and 1 if it is an admin: ");
        scanf("%d", users[i].role);
        printf("enter 0 if youe state account is active and 1 if it is blocked: ");
        scanf("%d", users[i].state);
    }
}
void displayUsers(struct User *users, int n){ 
    for(int i=0; i<n; i++){
        printf("the user name is : %s", users[i].name);
        printf("the password is : %s\n", users[i].password);
        printf("the role is : %d\n", users[i].role);
        printf("the state is : %d\n", users[i].state);
        printf("\n===============================\n");
    }
}
void addUser(struct User *users, int *n) {
    int m;
    printf("How many users to add? ");
    scanf("%d", &m);
    
    for (int i = 0; i < m; i++) {
        printf("\n--- Adding User %d ---\n", *n + 1);
        printf("Username: ");
        scanf(" %s", &users[*n].name);
        printf("Password: ");
        scanf(" %s", &users[*n].password);
        printf("Role (0:User, 1:Admin): ");
        scanf("%d", &users[*n].role);
        printf("State (0:Active, 1:Blocked): ");
        scanf("%d", &users[*n].state);
        (*n)++;
    }
}
void deleteUser(struct User *users, int *n, char name[]) {
    int found = -1;
    for (int i = 0; i < *n; i++) {
        if (strcmp(users[i].name, name) == 0) {
            found = i;
            break;
        }
    }

    if (found != -1) {
        for (int i = found; i < (*n) - 1; i++) {
            users[i] = users[i + 1];
        }
        (*n)--;
        printf("User %s deleted successfully.\n", name);
    } else {
        printf("User not found.\n");
    }
}
int searchUser(struct User *users, int n, char name[]){
    char nameToSearch[20];
    fgets(nameToSearch, 20, stdin);
    for(int i=0; i<n; i++){
        if(strcmp(users[i].name, nameToSearch)==0){
            printf("the user name is : %s", users[i].name);
            printf("the password is : %s\n", users[i].password);
            printf("the role is : %d\n", users[i].role);
            printf("the state is : %d\n", users[i].state);
        }
    } 
}
int checkLogin(struct User *users, int n, char name[], char pass[]){
    bool v=false;
    for(int i=0; i<n; i++){
        if(strcmp(users[i].name, name)==0 && strcmp(users[i].password, pass)==0){
            v=true;
        }
    }
    if(v){
        return 1;
    }else{
        return 0;
    }
}
void blockUser(struct User *users, int n, char name[]){
    for(int i=0; i<n; i++){
        if(strcmp(users[i].name, name)==0){
            users[i].state= 1;
        }
    }
} 
void changeRole(struct User *users, int n, char name[], int role){
    int c; while((c=getchar()) != '\n' && c != EOF);
    for(int i=0; i<n; i++){
        if(strcmp(users[i].name, name)==0){
            users[i].role=role;
        }
    }
}
int stringLength(char str[]){
    int c=-1;
    for(int i=0; str[i]!='\0'; i++){
        c++;
    }
    return c;
}
int containsLowercase(char str[]){
    for(int i=0; i<strlen(str); i++){
        if(str[i]>96 && str[i]<123){
            return 1;
        }
    }
    return 0;
}
int containsSymbol(char str[]){
    for(int i=0; i<strlen(str); i++){
        if(~(str[i]>47 && str[i]<58)&&(str[i]>64 && str[i]<91)&&(str[i]>96 && str[123])){
            return 1;
        }
    }
    return 0;
}
void saveUsers(struct User *users, int n){
    FILE *file;
    file=fopen("users.txt", "w");

    if(file==NULL){
        printf("Error in this process\n");
        return;
    }
    for(int i=0; i<n; i++){
        fprintf(file, "user name: %s\n user password: %s\n user role: %d\n user state: %d\n", users[i].name, users[i].password, users[i].role, users[i].state);
    }

    fclose(file);
    printf("Data saved in users.txt\n");
}
void changePassword(struct User *users, int n, char name[]){
    int i;
    char passwd[20];
    printf("enter your password :");
    scanf("%s",passwd);
    for (i=0;i<n;i++){
        if(strcmp(users[i].name,name)==0){
            strcpy(users[i].password,passwd);
            saveUsers(users, n); 
            return;
        }
    }
    printf ("user not found");
}