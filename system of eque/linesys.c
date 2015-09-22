#include <stdio.h>
#include <time.h>
#define size 4  /*dimension of matrix*/

//here is global data
	//time
		clock_t starttime;
		clock_t endtime;
	//matrix
		float A[size][size];
		float f[size];
		int c1,c2,pivot[size],ok;
		float AT [size*size];
//functions and procedures
void zerotime(){
		starttime=0;
		endtime=0;
}		
void starttimer(){
	starttime=clock();
}
void endtimer(){
	endtime=clock();
}
unsigned long returntime(){
	return endtime-starttime;	
}

void makematrixA(){
	int i,j;
	//A=)=0
	for (i=0;i<size;i++){
		for (j=0;j<size;j++){
			A[i][j]=0;
		}
	}
	for (i=0;i<size;i++){
		A[i][i]=1;
	}
	for(i=0;i<size-1;i++){
		A[i][i+1]=2;
	}
	for (i=0; i<size; i++){
		for(j=0; j<size; j++) AT[j+size*i]=A[j][i];		
	}	
}
void printmatrixA(){
 int i,j;
 printf("Here is your matrix A!\n");
 for (i=0;i<size;i++){
	for(j=0;j<size;j++){
			printf("%lf   ",A[i][j]);
	}
	printf("\n");
 }
 printf("\n");
 printf("********************************");
 printf("\n");
}

void mymakef(){
		int i;
		for(i=0;i<size;i++){
				f[i]=1;
		}
}

void myprintf(int q){
	int i;
	switch (q){
	case 1: {printf("Here is your vector f\n");
			break;
		}
	case 2: {printf("Here is your answer x\n");
			break;
		}}
	for(i=0;i<size;i++){
		printf("%lf\n",f[i]);
	}
 printf("\n");
 printf("********************************");
 printf("\n");
}
int main(){
	makematrixA();
	printmatrixA();
	mymakef();
	myprintf(1);

	//lapack is working here
		c1=size;
		c2=1;
	
	sgesv_(&c1, &c2, AT, &c1, pivot, f, &c1, &ok);
	   
	//lapack have done it
	myprintf(2);
	
return 0;
}

