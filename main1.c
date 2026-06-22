/* * Project: Security Utility Library Suite (ALSDS)
 * File: main1.c
 * Description: Fully implemented navigation with every function active.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Handle cross-platform getch()
#ifdef _WIN32
    #include <conio.h> 
#else
    #include <termios.h>
    #include <unistd.h>
    int getch() {
        struct termios oldt, newt;
        int ch;
        tcgetattr(STDIN_FILENO, &oldt);
        newt = oldt;
        newt.c_lflag &= ~(ICANON | ECHO);
        tcsetattr(STDIN_FILENO, TCSANOW, &newt);
        ch = getchar();
        tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
        return ch;
    }
#endif

// --- 1. Include Custom Headers ---
#include "message.h"  
#include "math_tools.h"  
#include "user.h"        
#include "security.h"       
#include "log.h"         

// --- Global Data Structures ---
struct User users[100];
int userCount;
struct Log logs[100];
int logCount;
struct Message currentMsg; 
struct Message msg2;
struct Matrix mat;

// --- UI Helper Functions ---
void clearScreen() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");    
    #endif
}

void pressAnyKey() {
    printf("\n[Press any key to return to menu...]");
    getch();
}

void clearBuffer() {
    int c; while((c=getchar()) != '\n' && c!=EOF);
}

void printHeader(const char *title) {
    clearScreen();
    printf("====================================================\n");
    printf("   %s\n", title);
    printf("====================================================\n");
}
// --- SUB-MENUS ---

void menuEncryption() {
    int choice, key;
    char subKey[27], c;
    clearBuffer();
    while(1) {
        printHeader("LIBRARY 1: ENCRYPTION & DECRYPTION");
        printf("1. inputMsg           2. displayMsg         3. isUppercase\n");
        printf("4. isLowercase        5. isAlphabitical     6. toUppercase\n");
        printf("7. toLowercase        8. reverseMessage     9. removeSpaces\n");
        printf("10. encryptCesar      11. decryptCesar      12. XORencryption\n");
        printf("13. XORdecryption     14. encryptSubst      15. decryptSubst\n");
        printf("16. isValidKey        17. compareMessage    18. counterChar\n");
        printf("19. frequencyAnalysis 20. coincidenceIndex   0. Back\n");
        printf("----------------------------------------------------\n");
        printf(" Choice: ");
        if (scanf("%d", &choice) != 1) { while(getchar() != '\n'); continue; }
        if(choice == 0) break;
        switch(choice) {
            case 1: inputMessage(&currentMsg); break;
            case 2: displayMessage(&currentMsg); break;
            case 3: printf("Char: "); scanf(" %c", &c); isUppercase(c); break;
            case 4: printf("Char: "); scanf(" %c", &c); isLowercase(c); break;
            case 5: printf("Char: "); scanf(" %c", &c); isAlphabitical(c); break;
            case 6: inputMessage(&currentMsg); toUppercase(&currentMsg); printf("\nDone.\n"); break;
            case 7: inputMessage(&currentMsg); toLowercase(&currentMsg); printf("\nDone.\n"); break;
            case 8: inputMessage(&currentMsg); reverseMessage(&currentMsg); printf("\nDone.\n"); break;
            case 9: inputMessage(&currentMsg); removeSpaces(&currentMsg); printf("\nDone.\n"); break;
            case 10: inputMessage(&currentMsg); printf("Cesar Key: "); scanf("%d", &key); encryptCesar(&currentMsg, key); break;
            case 11: inputMessage(&currentMsg); printf("Cesar Key: "); scanf("%d", &key); decryptCesar(&currentMsg, key); break;
            case 12: inputMessage(&currentMsg); printf("XOR Key: "); scanf("%d", &key); XORencryption(&currentMsg, key); break;
            case 13: inputMessage(&currentMsg); printf("XOR Key: "); scanf("%d", &key); XORdecryption(&currentMsg, key); break;
            case 14: inputMessage(&currentMsg); printf("26-char Key: "); scanf("%s", subKey); encryptSubstitution(&currentMsg, subKey); break;
            case 15: inputMessage(&currentMsg); printf("26-char Key: "); scanf("%s", subKey); decryptionSubstitution(&currentMsg, subKey); break;
            case 16: printf("Key: "); scanf("%s", subKey); printf("Valid: %d\n", isValidKey(subKey)); break;
            case 17: inputMessage(&currentMsg); printf("The second message for comparison\n"); inputMessage(&msg2); printf("Result: %d\n", compareMessage(&currentMsg, &msg2)); break;
            case 18: printf("Char: "); scanf(" %c", &c); printf("Count: %d\n", counterCharacter(&currentMsg, c)); break;
            case 19: frequencyAnalysis(&currentMsg); break;
            case 20: inputMessage(&currentMsg); printf("Index: %d\n", coincidenceIndex(&currentMsg)); break;
        }
        pressAnyKey();
    }
}

void menuMath() {
    int choice, n, a, b, exp, m, size;
    int arr[50];
    struct Matrix matA, matB, matC;
    while(1) {
        printHeader("LIBRARY 2: MATH & SECURITY TOOLS");
        printf("1. isEven        2. isPrime       3. gcd           4. lcm\n");
        printf("5. modExp        6. fact          7. sumDigits     8. reverseNumber\n");
        printf("9. isPalindrome  10. sumDivisors  11. isPerfect    12. isArmstrong\n");
        printf("13. randNum      14. sumArray     15. averageArray 16. maxArray\n");
        printf("17. minArray     18. sortAsc      19. dispMatrix   20. addMatrices\n");
        printf("21. multMatrices 22. transpose    23. det2x2       24. isSymmetric\n");
        printf("25. isIdentity    0. Back\n");
        printf("----------------------------------------------------\n");
        printf(" Choice: ");
        if (scanf("%d", &choice) != 1) { while(getchar() != '\n'); continue; }
        if(choice == 0) break;

        switch(choice) {
            case 1: printf("N: "); scanf("%d", &n); printf("Even: %d\n", isEven(n)); break;
            case 2: printf("N: "); scanf("%d", &n); printf("Prime: %d\n", isPrime(n)); break;
            case 3: printf("a b: "); scanf("%d %d", &a, &b); printf("GCD: %d\n", gcd(a, b)); break;
            case 4: printf("a b: "); scanf("%d %d", &a, &b); printf("LCM: %d\n", lcm(a, b)); break;
            case 5: printf("Base Exp Mod: "); scanf("%d %d %d", &a, &exp, &m); printf("Res: %d\n", modExp(a, exp, m)); break;
            case 6: printf("N: "); scanf("%d", &n); printf("Fact: %d\n", fact(n)); break;
            case 7: printf("N: "); scanf("%d", &n); printf("Sum: %d\n", sumDigits(n)); break;
            case 8: printf("N: "); scanf("%d", &n); printf("Rev: %d\n", reverseNumber(n)); break;
            case 9: printf("N: "); scanf("%d", &n); printf("Pal: %d\n", isPalindromeNumber(n)); break;
            case 10: printf("N: "); scanf("%d", &n); printf("Sum: %d\n", sumDivisors(n)); break;
            case 11: printf("N: "); scanf("%d", &n); printf("Perfect: %d\n", isPerfectNumber(n)); break;
            case 12: printf("N: "); scanf("%d", &n); printf("Armstrong: %d\n", isArmstrong(n)); break;
            case 13: printf("Min Max: "); scanf("%d %d", &a, &b); printf("Rand: %d\n", randomNumber(a, b)); break;
            case 14: printf("Size: "); scanf("%d", &size); for(int i=0; i<size; i++) scanf("%d", &arr[i]); printf("Sum: %d\n", sumArray(arr, size)); break;
            case 15: printf("Size: "); scanf("%d", &size); for(int i=0; i<size; i++) scanf("%d", &arr[i]); printf("Avg: %.2f\n", averageArray(arr, size)); break;
            case 16: printf("Size: "); scanf("%d", &size); for(int i=0; i<size; i++) scanf("%d", &arr[i]); printf("Max: %d\n", maxArray(arr, size)); break;
            case 17: printf("Size: "); scanf("%d", &size); for(int i=0; i<size; i++) scanf("%d", &arr[i]); printf("Min: %d\n", minArray(arr, size)); break;
            case 18: printf("Size: "); scanf("%d", &size); for(int i=0; i<size; i++) scanf("%d", &arr[i]); sortAscending(arr, size); break;
            case 19: displayMatrix(matA); break;
            case 20: addMatrices(matA, matB, matC); break;
            case 21: multiplyMatrices(matA, matB, matC); break;
            case 22: transposeMatrix(matA, matC); break;
            case 23: { int m2[2][2]; printf("4 vals: "); for(int i=0;i<2;i++) for(int j=0;j<2;j++) scanf("%d", &m2[i][j]); printf("Det: %d\n", determinant2x2(m2)); break;}
            case 24: printf("Symm: %d\n", isSymmetric(matA)); break;
            case 25: printf("Identity: %d\n", isIdentity(matA)); break;
        }
        pressAnyKey();
    }
}

void menuUser() {
    int choice, role;
    char name[50], pass[50], str[100];
    clearBuffer();
    while(1) {
        printHeader("LIBRARY 3: USER MANAGEMENT");
        printf("1. strongPassword     2. unblockUser        3. listAdmins\n");
        printf("4. containsUpper      5. userStatistics     6. loadUsers\n");
        printf("7. initUsers          8. displayUsers       9. addUser\n");
        printf("10. deleteUser        11. searchUser        12. checkLogin\n");
        printf("13. blockUser         14. changeRole        15. stringLength\n");
        printf("16. containsLower     17. containsDigit     18. containsSymbol\n");
        printf("19. saveUsers         20. changePassword     0. Back\n");
        printf("----------------------------------------------------\n");
        printf(" Choice: ");
        if (scanf("%d", &choice) != 1) { while(getchar() != '\n'); continue; }
        if(choice == 0) break; 
        int n;clearBuffer();

        switch(choice) {
            case 1: printf("Pass: "); scanf("%s", pass); printf("Strong: %d\n", strongPassword(pass)); break;
            case 2: printf("Name: "); scanf("%s", name); unblockUser(users, userCount, name); break;
            case 3: listAdmins(users, userCount); break;
            case 4: printf("Str: "); scanf("%s", str); printf("HasUpper: %d\n", containsUppercase(str)); break;
            case 5: userStatistics(users, userCount); break;
            case 6: loadUsers(users, &userCount); break;
            case 7: printf("write how many users you have: "); scanf("%d", &n);userCount=n;initUsers(users, n); break;
            case 8: displayUsers(users, userCount); break;
            case 9: addUser(users, &userCount); break;
            case 10: printf("Name: "); scanf("%s", name); deleteUser(users, &userCount, name); break;
            case 11: printf("Name: "); scanf("%s", name); printf("Index: %d\n", searchUser(users, userCount, name)); break;
            case 12: printf("User Pass: "); scanf("%s %s", name, pass); printf("Login: %d\n", checkLogin(users, userCount, name, pass)); break;
            case 13: printf("Name: "); scanf("%s", name); blockUser(users, userCount, name); break;
            case 14: printf("Name Role: "); scanf("%s %d", name, &role); changeRole(users, userCount, name, role); break;
            case 15: printf("Str: "); scanf("%s", str); printf("Len: %d\n", stringLength(str)); break;
            case 16: printf("Str: "); scanf("%s", str); printf("HasLower: %d\n", containsLowercase(str)); break;
            case 17: printf("Str: "); scanf("%s", str); printf("HasDigit: %d\n", containsDigit(str)); break;
            case 18: printf("Str: "); scanf("%s", str); printf("HasSym: %d\n", containsSymbol(str)); break;
            case 19: saveUsers(users, userCount); break;
            case 20: printf("Name: "); scanf("%s", name); changePassword(users, userCount, name); break;
        }
        pressAnyKey();
    }
}

void menuAudit() {
    int choice, len;
    char text[200], key[100];

    while(1) {
        printHeader("LIBRARY 4: SECURITY AUDIT & ANALYSIS");
        printf("1. countUpper      2. countLower      3. countDigits\n");
        printf("4. percentUpper    5. textLength       6. displayStats\n");
        printf("7. veryStrongPass  8. generateKey     9. isHexKey\n");
        printf("10. genRandPass    11. passwordScore  12. averageScore\n");
        printf("13. securityReport 14. countStrong    15. showTips\n");
        printf("16. checkEmail     17. checkLoginFmt  18. genHexKey\n");
        printf("19. top3Pass       20. globalSecLvl    0. Back\n");
        printf("----------------------------------------------------\n");
        printf(" Choice: ");
        if (scanf("%d", &choice) != 1) { while(getchar() != '\n'); continue; }
        if(choice == 0) break;

        switch(choice) {
            case 1: printf("Text: "); scanf(" %s", text); printf("Cnt: %d\n", countUppercase(text)); break;
            case 2: printf("Text: "); scanf(" %s", text); printf("Cnt: %d\n", countLowercase(text)); break;
            case 3: printf("Text: "); scanf(" %s", text); printf("Cnt: %d\n", countDigits(text)); break;
            case 4: printf("Text: "); scanf(" %s", text); printf("Pct: %.2f%%\n", percentUppercase(text)); break;
            case 5: printf("Text: "); scanf(" %s", text); printf("Len: %d\n", textLength(text)); break;
            case 6: printf("Text: "); scanf(" %[^\n]", text); displayTextStats(text); break;
            case 7: printf("Pass: "); scanf(" %s", text); printf("VeryStrong: %d", veryStrongPassword(text)); break;
            case 8: printf("Len: "); scanf("%d", &len); generateKey(len, key); printf("Key: %s\n", key); break;
            case 9: printf("Key: "); scanf(" %s", key); printf("IsHex: %d\n", isHexKey(key)); break;
            case 10: printf("Len: "); scanf("%d", &len); generateRandomPassword(len, text); printf("Pass: %s\n", text); break;
            case 11: printf("Pass: "); scanf(" %s", text); printf("Score: %d\n", passwordScore(text)); break;
            case 12: printf("Avg Score: %.2f\n", averageScore(users, userCount)); break;
            case 13: displaySecurityReport(users, userCount); break;
            case 14: printf("Strong Users: %d\n", countStrongUsers(users, userCount)); break;
            case 15: showSecurityTips(); break;
            case 16: printf("Email: "); scanf(" %s", text); printf("Valid: %d\n", checkEmailFormat(text)); break;
            case 17: printf("Login: "); scanf(" %s", text); printf("Valid: %d\n", checkLoginFormat(text)); break;
            case 18: printf("Len: "); scanf("%d", &len); generateHexKey(len, key); printf("HexKey: %s\n", key); break;
            case 19: top3Passwords(users, userCount); break;
            case 20: printf("Global Lvl: %d\n", globalSecurityLevel(users, userCount)); break;
        }
        pressAnyKey();
    }
}

void menuLog() {
    int choice, code, nb;
    char user[50], action[100], date[20];
    while(1) {
        printHeader("LIBRARY 5: LOG MANAGEMENT");
        printf("1. initLogs        2. addLog          3. displayLogs\n");
        printf("4. searchByUser    5. searchByDate    6. countErrorLogs\n");
        printf("7. countLoginLogs  8. countBlocked    9. displayLogStats\n");
        printf("10. sortDate       11. sortUser       12. detectSuspicious\n");
        printf("13. dailyConn      14. errorRate      15. exportCSV\n");
        printf("16. importCSV      17. clearLogs      18. recentLogs\n");
        printf("19. archiveLogs    20. showTopErrors   0. Back\n");
        printf("----------------------------------------------------\n");
        printf(" Choice: ");
        if (scanf("%d", &choice) != 1) { while(getchar() != '\n'); continue; }
        if(choice == 0) break;
        clearBuffer();

        switch(choice) {
            case 1: printf("rnter the number of logs"); scanf("%d", &logCount); initLogs(logs, logCount); break;
            case 2: printf("enter the name: ");scanf(" %s", user);
                    printf("enter the action: ");scanf(" %s", action);
                    printf("enter the code: ");scanf("%d", code);
                    addLog(logs, logCount++, user, action, code); break;
            case 3: displayLogs(logs, logCount); break;
            case 4: printf("User: "); scanf("%s", user); searchLogsByUser(logs, logCount, user); break;
            case 5: printf("Date: "); scanf("%s", date); searchLogsByDate(logs, logCount, date); break;
            case 6: printf("Errors: %d\n", countErrorLogs(logs, logCount)); break;
            case 7: printf("Logins: %d\n", countLoginLogs(logs, logCount)); break;
            case 8: printf("Blocked: %d\n", countBlockedLogs(logs, logCount)); break;
            case 9: displayLogStats(logs, logCount); break;
            case 10: sortLogsByDate(logs, logCount); break;
            case 11: sortLogsByUser(logs, logCount); break;
            case 12: printf("User: "); scanf("%s", user); printf("Suspicious: %d\n", detectSuspiciousActivity(logs, logCount, user)); break;
            case 13: printf("Date: "); scanf("%s", date); printf("Conn: %d\n", dailyConnections(logs, logCount, date)); break;
            case 14: printf("Error Rate: %.2f\n", errorRate(logs, logCount)); break;
            case 15: exportLogsCSV(logs, logCount); break;
            case 16: importLogsCSV(logs, logCount); break;
            case 17: clearLogs(logs, logCount); logCount = 0; break;
            case 18: printf("Count: "); scanf("%d", &nb); recentLogs(logs, logCount, nb); break;
            case 19: archiveLogs(logs, logCount); break;
            case 20: showTopErrors(logs, logCount); break;
        }
        pressAnyKey();
    }
}

// --- MAIN ENTRY POINT ---
int main() {
    srand(time(NULL));
    loadUsers(users, &userCount);
    currentMsg.text=(char*)malloc(1024*sizeof(char));
    msg2.text=(char*)malloc(1024*sizeof(char));

    int choice;
    while(1) {
        clearScreen();
        
        // Cyber-Glow Title
        printf("  █████╗ ██╗     ███████╗██████╗ ███████╗\n");
        printf(" ██╔══██╗██║     ██╔════╝██╔══██╗██╔════╝\n");
        printf(" ███████║██║     ███████╗██║  ██║███████╗\n");
        printf(" ██╔══██║██║     ╚════██║██║  ██║╚════██║\n");
        printf(" ██║  ██║███████╗███████║██████╗ ███████║\n");
        printf(" ╚═╝  ╚═╝╚══════╝╚══════╝╚═════╝ ╚══════╝\n");
        
        printf(" ┌───────────────────────────────────────────────┐\n");
        printf(" │     ""SECURITY UTILITY LIBRARY SUITE""        |\n");
        printf(" └───────────────────────────────────────────────┘\n");

        printf("\nMAIN CONTROL INTERFACE:""\n");
        printf(" [1] Encryption & Decryption Module\n");
        printf(" [2] Mathematical Analysis Tools\n");
        printf(" [3] Identity & Access Management\n");
        printf(" [4] Global Security Audit\n");
        printf(" [5] System Log Monitor\n");
        printf(" ─────────────────────────────────────────────────\n");
        printf(" [0] SHUTDOWN SYSTEM\n");
        
        printf("\n ""SYS_PROMPT >> " );
        
        if (scanf("%d", &choice) != 1) {
            while(getchar() != '\n');
            continue;
        }

        switch(choice) {
            case 1: menuEncryption(); break;
            case 2: menuMath(); break;
            case 3: menuUser(); break;
            case 4: menuAudit(); break;
            case 5: menuLog(); break;
            case 0:
                saveUsers(users, userCount);
                printf("\n [!] System Terminated. Data Synchronized.\n");
                return 0;
            default:
                printf("\n [X] Access Denied: Invalid Module ID.\n");
                pressAnyKey();
        }
    }
    return 0;
}