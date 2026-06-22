#include<stdio.h>
#include <stdlib.h>
#include <time.h>
struct Matrix{ 
  int data[10][10]; 
  int n, p; 
 }; 

 int isEven(int n){
 if(n%2==0){
 		return 1;
	}
	else{
		return 0;
	}
 }
 int gcd(int a, int b){
 	int temp;
 	while(b>0){
 		temp=b;
 		b=a%b;
 		a=temp;
	 }
 	return a;
 	
 }
 int modExp(int base, int exp, int mod){
 	int i,s;//i can define s as longlong to prevent overflow when dealing with huge nums
 	s=1;
 	for (i=1;i<=exp;i++){
 		s=s*base;
	 }
 	return s%mod;
 }
 int sumDigits(int n){
 	int s;
 	s=0;
 	while(n>0){
 		s=s+n%10;
 		n=n/10;
	 }
	 return s;
 }
 int isPalindromeNumber(int n){
 	int temp,h;
 	temp=n; 
 	h=0;
 	while (temp>0){
 		h=h*10+temp%10;
 		temp=temp/10;
	 }
 	if(h==n){
 		return 1;
	 }
 	else{
 		return 0;
	 }
 } 
 int isPerfectNumber(int n){
 	int s,i;
 	s=0;
 	if(n<0){
 		return 0;
	 }
	 else{
	 	for(i=1;i<=n/2;i++){
	 		if(n%i==0){
	 			s=s+i;	
			 }
		 }
	 	if(n==s){
	 		return 1;
		 }
		 else{
		 	return 0;
		 }
	 }
 	
 }
 int randomNumber(int min, int max){
 	int r,s;
 	r=max-min+1;
 	s=rand()%r;
 	return s+min;
 }
 float averageArray(int T[], int n){
 	int s,i;
 	s=0;
 	for (i=0;i<n;i++){
 		s=s+T[i];
	 }
	 return s/n;
 } 
 int minArray(int T[], int n){
 	int min,i;
 	min=T[0];
 	for (i=1;i<n;i++){
 		if(T[i]<min){
 			min=T[i];
		 }	
	 }
	 return min;
 }
 void displayMatrix(struct Matrix M){
    printf("Enter rows and columns: ");
    scanf("%d", &M.n); scanf("%d", &M.p);
    
    printf("Enter elements:\n");
    for(int i = 0; i < M.n; i++) {
        for(int j = 0; j < M.p; j++) {
             scanf("%d", &M.data[i][j]);
        }
    }
 	for (int i=0; i<M.n; i++){
 		for (int j=0;j<M.p;j++){
 		    printf(" %d", M.data[i][j]);
		}
		printf("\n");
	 }	
 }
void multiplyMatrices(struct Matrix A, struct Matrix B, struct Matrix C){
    printf("Enter rows and columns: ");
    scanf("%d", &A.n); scanf("%d", &A.p);
    
    printf("Enter elements:\n");
    for(int i = 0; i < A.n; i++) {
        for(int j = 0; j < A.p; j++) {
             scanf("%d", &A.data[i][j]);
        }
    }
    printf("Enter rows and columns: ");
    scanf("%d", &B.n); scanf("%d", &B.p);
    
    printf("Enter elements:\n");
    for(int i = 0; i < B.n; i++) {
        for(int j = 0; j < B.p; j++) {
             scanf("%d", &B.data[i][j]);
        }
    }
    int i, j, k;
    if (A.p != B.n) {
        printf("Error: Matrices cannot be multiplied (the number of Columns of A not equal the number of Rows of B).\n");
        return;
    }
    C.n = A.n;
    C.p = B.p;
    for (i = 0; i < C.n; i++) {          
        for (j = 0; j < C.p; j++) {      
            
            C.data[i][j] = 0;             
            
            for (k = 0; k < A.p; k++) {  
                C.data[i][j] = C.data[i][j] + A.data[i][k] * B.data[k][j];
            }
        }
    }
    printf(" Multiplication Result :\n");
    for (i = 0; i < C.n; i++) {
        for (j = 0; j < C.p; j++) {
            printf("%d\t", C.data[i][j]);
        }
        printf("\n");
    }
}
 int determinant2x2(int A[2][2]){
    int i= (A[0][0]*A[1][1])-(A[0][1]*A[1][0]);
    return i;
 }
 int isIdentity(struct Matrix M){
 	printf("Enter rows and columns: ");
    scanf("%d", &M.n); scanf("%d", &M.p);
    
    printf("Enter elements:\n");
    for(int i = 0; i < M.n; i++) {
        for(int j = 0; j < M.p; j++) {
             scanf("%d", &M.data[i][j]);
        }
    }
    int i,j;
 	if(M.n==M.p){
 		for(i=0;i<M.p;i++){
 			for (j=0;j<M.p;j++){
 				if(i==j){
 					if(M.data[i][j]!=1 ){
 						return 0;
					 }
				 }
				else{
 					if (M.data[i][j] !=0){
 						return 0;
				 	}
				}
			 }
		 }
 		return 1;
	 }
 	else{
 		return 0;
 	 }
    }
/////////////////////////////////////////////////////////////////////////////
struct Matrix{
    int data[10][10];
    int n,p; //n for rows and p for columns
};
int isPrime(int n){
    int l=1;

    int d=2;
    while(d<n){
    if(n%d != 0){ 
        d++;
    }
    else{
        l=0;
        break;
    }
}

    if(n==d){
        l=1;
    }
    return l;
}
int lcm(int a, int b){
    if (b<a)
    {
        int temp=a; b=a; b=temp;
    }
    int p=a*b;
    int div=b%a;
    while(div != 0){
        div=b%a;
        b=a;
        a=div;
    }
    
    return p/b;
}
int fact(int n){
    int i;
    int f=1;
    for(i=1; i<=n; i++){
        f=f*i;
    }

    return f;
}
int reverseNumber(int n){
    int rev=0;
    while(n>0){
        int d=n%10;
        n=n/10;
        rev=rev*10+d;
    }

    return rev;
}
int sumDivisors(int n){
    int i; int s=0;
    for(i=2; i<n; i++){
        if(n%i == 0){
            s=s+i;
        }
    }

    return s;
}
int isArmstrong(int n){
    int j=0; int n1=n;
    while(n1>0){
        j++;
        n1=n1/10;
    }
    int s=0;
    while(n>0){
        int d=n%10; int J=j;
        int D=1;
        while(J>0){ 
            D *= d;
            J -= 1;
        } 
        s += D; n /= 10;
    }

    return s;
}
int sumArray(int T[], int n){
    int i; int s=0; 
    for(i=0; i<n; i++){
        s += T[i];
    }

    return s;
}
int maxArray(int T[], int n){
    int i; int max=T[0];
    for(i=1; i<n; i++){
        if(T[i]>max){
            max=T[i];
        }
    }

    return max;
}
void sortAscending(int T[], int n){
    int i=0;
    while(i<n){
        int j=0;
        while(j<n){
            if(T[i]<T[j]){
                int m=T[i]; T[i]=T[j]; T[j]=m;
            }
            j += 1;
        }
        i +=1;
    }
    for(int i=0; i<n; i++){
        printf("%d", T[i]);
    }
}
void addMatrices(struct Matrix A, struct Matrix B, struct Matrix C){
    printf("Enter rows and columns: ");
    scanf("%d", &A.n); scanf("%d", &A.p);
    
    printf("Enter elements:\n");
    for(int i = 0; i < A.n; i++) {
        for(int j = 0; j < A.p; j++) {
             scanf("%d", &A.data[i][j]);
        }
    }
    printf("Enter rows and columns: ");
    scanf("%d", &B.n); scanf("%d", &B.p);
    
    printf("Enter elements:\n");
    for(int i = 0; i < B.n; i++) {
        for(int j = 0; j < B.p; j++) {
             scanf("%d", &B.data[i][j]);
        }
    }    
    if(A.n != B.n || A.p != B.p){
            printf("Error: Matrices dimensions do not match for addition \n");
            return;
        }

    for(int i=0; i<A.n; i++){
        for(int j=0; j<A.p;j++){
            C.data[i][j]=A.data[i][j]+B.data[i][j];
        }
    }
    for(int i=0; i<A.n; i++){
        for(int j=0; j<A.p;j++){
            printf("%d ", C.data[i][j]);
        }
        printf("\n");
    }
}
void transposeMatrix(struct Matrix A, struct Matrix T){
    printf("Enter rows and columns: ");
    scanf("%d", &A.n); scanf("%d", &A.p);
    
    printf("Enter elements:\n");
    for(int i = 0; i < A.n; i++) {
        for(int j = 0; j < A.p; j++) {
             scanf("%d", &A.data[i][j]);
        }
    }
    T.n=A.p;
    T.p=A.n;
    for(int i=0; i<T.n; i++){
        for(int j=0; j<T.p; j++){
            T.data[i][j]=A.data[j][i];
        }
    }
    for(int i=0; i<T.n; i++){
        for(int j=0; j<T.p; j++){
            printf("%d ", T.data[i][j]);
        }
        printf("\n");
    }
}   
int isSymmetric(struct Matrix M){ 
    
    do{
        printf("Enter rows and columns: ");
    scanf("%d", &M.n); scanf("%d", &M.p);
    
    printf("Enter elements:\n");
    for(int i = 0; i < M.n; i++) {
        for(int j = 0; j < M.p; j++) {
             scanf("%d", &M.data[i][j]);
        }
    }
    if(M.n != M.p){
        printf("it does not have symmetric property\n");
        return 0;
    }
    }while(M.n != M.p);
    for(int i=0; i<M.n; i++){
        for(int j=0; j<M.p; j++){
            if(M.data[i][j] != M.data[j][i]){
                return 0;
            }
        }
    }
    return 1;
}
