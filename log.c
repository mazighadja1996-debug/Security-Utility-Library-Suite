#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
struct Log{ 
  char user[20]; 
  char action[50]; 
  char date[20]; 
  char time[10]; 
  int code;  // 0 info, 1 warning, 2 error 
 }; 
void addLog(struct Log logs[], int *n, const char *user, const char *action, int code) {
    if (*n < 100) {
        strncpy(logs[*n].user, user, 19);
        strncpy(logs[*n].action, action, 49);
        logs[*n].code = code;
        time_t t = time(NULL);
        struct tm *tm = localtime(&t);
        printf("enter the date: ");strftime(logs[*n].date, 20, "%Y-%m-%d", tm);
        printf("enter the time:");strftime(logs[*n].time, 10, "%H:%M:%S", tm);
        (*n)++;
    }
}
void searchLogsByUser(struct Log logs[], int n, char user[]){
	int i,f;
	f=0;
	printf(" Search Results for User: %s .\n", user);
	for (i=0;i<n;i++){
		if (strcmp(user,logs[i].user)==0){
			printf ("{\n");
			printf("user   :%s\n",logs[i].user);
			printf("action :%s\n",logs[i].action);
			printf("date   :%s\n",logs[i].date);
			printf("time   :%s\n",logs[i].time);
			printf("code   :%d\n",logs[i].code);
			printf("}\n");
			f=1;
		}	
	}
	if (f == 0) {
        printf("No logs found for user: %s\n", user);
    }
}
int countErrorLogs(struct Log logs[], int n){
	int c,i;
	c=0;
	for (i=0;i<n;i++){
		if (logs[i].code==2){
			c++;
		}
	}
	return c;
}
int countBlockedLogs(struct Log logs[], int n){
	int c,i;
	c=0;
	for (i=0;i<n;i++){
		if (logs[i].code==2){
			c++;
		}
	}
	return c;
}
void sortLogsByDate(struct Log logs[], int n){
	int i, j, min,Diff;
    struct Log temp;

    for (i = 0; i < n - 1; i++) {
        min = i;
        for (j = i + 1; j < n; j++) {
            Diff = strcmp(logs[j].date, logs[min].date);
            if (Diff < 0) {
                min = j;
            } else if (Diff == 0) {
                if (strcmp(logs[j].time, logs[min].time) < 0) {
                    min = j;
                }
            }
        }
        temp = logs[min];
        logs[min] = logs[i];
        logs[i] = temp;
    }
    printf("Logs sorted chronologically.");
	
}
int detectSuspiciousActivity(struct Log logs[], int n, char user[]){
	int i,f=0;
	for (i=0;i<n;i++){
		if (strcmp(logs[i].user,user)==0 && logs[i].code==1){
			printf ("the user %s is doing suspicious activity .",user);
			f=1;
		}
	}
	if(f==0){
		printf ("it is all good ");
	}
}
float errorRate(struct Log logs[], int n){
	int errorCount = 0;
	if (n == 0) {
		return 0.0; 
	}
    for (int i = 0; i < n; i++) {
        if (logs[i].code == 2) {
            errorCount++;
        }
    }
    return errorCount / n * 100;
}
////////
int importLogsCSV(struct Log logs[], int n) {
    FILE *file = fopen("logs.csv", "r");
    if (file == NULL) {
        printf("Could not open logs.csv\n");
        return n;
    }

    // Read until end of file or until array is full
    while (n < 100 && fscanf(file, "%[^,],%[^,],%[^,],%[^,],%d\n", 
           logs[n].user, logs[n].action, logs[n].date, logs[n].time, &logs[n].code) == 5) {
        n++;
    }

    fclose(file);
    printf("Imported %d logs successfully.\n", n);
    return n;
}

void recentLogs(struct Log logs[], int n, int nb) {
    printf("--- Showing Last %d Events ---\n", nb);
    
    // Determine where to start so we don't go below index 0
    int start = n - nb;
    if (start < 0) start = 0;

    for (int i = n - 1; i >= start; i--) {
        printf("[%s %s] %s: %s (Code: %d)\n", 
                logs[i].date, logs[i].time, logs[i].user, logs[i].action, logs[i].code);
    }
}
void showTopErrors(struct Log logs[], int n) {
    int found = 0;
    printf("\n--- CRITICAL ERROR ACTIONS REPORT ---\n");
    for (int i = 0; i < n; i++) {
        if (logs[i].code == 2) {
            printf("PRIORITY: %s | User: %s | Date: %s\n", 
                    logs[i].action, logs[i].user, logs[i].date);
            found = 1;
        }
    }
    if (!found) printf("No critical errors found.\n");
}
/////////////////////////////////////////////////////////////////////////////////
void initLogs(struct Log logs[], int n){
    for(int i=0; i<n; i++){
        int c; while((c=getchar())!='\n' && c!=EOF);
        printf("enter your name: ");
        strcpy(logs[i].user, "NONE");
        printf("enter your action: ");
        strcpy(logs[i].action, "EMPTY");
        printf("enter your date: ");
        strcpy(logs[i].date, "00-00-0000");
        printf("enter your time: ");
        strcpy(logs[i].date, "00:00");
        printf("enter your code 0 for info, 1 for warning, 2 for error: ");
        scanf("%d", &logs[i].code);
    }
}
void displayLogs(struct Log logs[], int n){
    for(int i=0; i<n; i++){
        printf("the user name is: %s", logs[i].user);
        printf("the action is: %s", logs[i].action);
        printf("the logging date is: %s", logs[i].date);
        printf("the logging time is: %s", logs[i].time);
        printf("the logging code is: %d", logs[i].code);
        printf("\n======================================\n");
    }
}
void searchLogsByDate(struct Log logs[], int n, char date[]){
    int I;
    for(int i=0; i<n; i++){
        if(strcmp(logs[i].date, date)==0){
            I=i;
        }        
    }
    printf("the user name is: %s", logs[I].user);
    printf("the action is: %s", logs[I].action);
    printf("the logging date is: %s", logs[I].date);
    printf("the logging time is: %s", logs[I].time);
    printf("the logging code is: %d", logs[I].code);
    
}
int countLoginLogs(struct Log logs[], int n){
    int c=0;
    for(int i=0; i<n; i++){
        if(strcmp(logs[i].action, "login\n")==0){
            c++;
        }
    }
    return c;
}
void displayLogStats(struct Log logs[], int n){
    printf("the total logs is: %d\n", n);
    int m=countLoginLogs(logs, n);
    printf("the login events is: %d\n", m);
    int w=0, e=0, in=0;
    for(int i=0; i<n; i++){
        if(logs[i].code==1){
            w++;
        }else if (logs[i].code==2){
            e++;
        }else{
            in++;
        }
    }
    printf("the number of warnings is: %d\n", w);
    printf("the number of errors is: %d\n", e);
    printf("the number of informations is: %d\n", in);
}
void sortLogsByUser(struct Log logs[], int n){
    int j=0;
    for(int c=97; c<123; c++){
        for(int i=0; i<n; i++){
            if(logs[i].user[0]==(char)c){
                struct Log temp = logs[i];
                logs[i]=logs[j];
                logs[j]=temp;
                j++;
            }
        }
    }
}
int dailyConnections(struct Log logs[], int n, char date[]){
    int d=0;
    for(int i=0; i<n; i++){
        if(strcmp(date, logs[i].date)==0){
            d++;
        }
    }
    return d;
}
void exportLogsCSV(struct Log logs[], int n){
    FILE *file=fopen("logs.csv", "w");
    if(file == NULL){
        printf("Error opening file\n");
        return;
    }
    for(int i=0; i<n; i++){
        fprintf(file, "the user is %s, the action is %s, at %s, at time %s, its code is %d", logs[i].user, logs[i].action, logs[i].date, logs[i].time, logs[i].code);
    }

    fclose(file);
    printf("logs exported successfully\n");
}
void clearLogs(struct Log logs[], int *n){
    //to make the content empty
    for(int i =0; i<*n; i++){
        logs[i].user[0]='\0';
        logs[i].action[0]='\0';
        logs[i].date[0]='\0';
        logs[i].time[0]='\0';
        logs[i].code=0;
        }
    (*n)--;
    memset(logs, 0, sizeof(struct Log)*(*n));
}
void archiveLogs(struct Log logs[], int n){
    //for archives we generate a time stamp
    time_t t = time(NULL);
    struct tm *tm = localtime(&t);
    char log_file[256];
    snprintf(log_file, sizeof(log_file), "archive_%04d%02d%02d_%02d%02d%02d.csv",
    tm->tm_year + 1900, tm->tm_mon + 1, tm->tm_mday, 
    tm->tm_hour, tm->tm_min, tm->tm_sec);
    FILE *file = fopen(log_file, "w");
    if(file == NULL){
        printf("Error opening archive file\n");
        return;
    }
    for(int i=0; i<n; i++){
        fprintf(file, "the user is %s, the action is %s, at %s, at time %s, its code is %d",
        logs[i].user, logs[i].action, logs[i].date,
        logs[i].time, logs[i].code);
    }

    fclose(file);
    printf("archive created successfully\n");
}