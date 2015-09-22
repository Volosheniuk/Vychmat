#include <stdio.h>
#include <time.h>
#define size 4  /*dimension of matrix*/

//here is global data
	//time
		clock_t starttime;
		clock_t endtime;
	//matrix
		double A[size][size];
		double E_At[size][size];
		double f[size];
		int c1,c2,pivot[size],ok;
		double AT [size*size];
		double E_ATt [size*size];
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
/*
void getmyanswerviamethoditerations(int p){//f is an answer like in lapack
	int i,j;
	double xp[size];
	double xp1[size];
	double sum;
	double t=14.0;
	//f=tttttt  xp=11111111
	for(i=0;i<size;i++){
		f[i]=t;
		xp[i]=1;
		} 
	
	//get E-tA
	for (i=0;i<size;i++){
		for(j=0;j<size;j++){
			if(i==j){
					E_At[i][j]=1-t*A[i][j];
					}
			else E_At[i][j]=-t*A[i][j];
			}
		}
	for (i=0; i<size; i++){
		for(j=0; j<size; j++) E_ATt[i*size+j]=E_At[j][i];		
	}
	//count xp1=(E-At)xp+ft
	sum=0;
	int pp;
	for(pp=0;pp<p;pp++){
		for (i=0;i<size;i++){
			for(j=0;j<size;j++){
				sum=sum+E_At[i][j]*xp[j];
				}
			xp1[i]=sum+f[i];
			sum=0;
			}
		for(i=0;i<size;i++){
			xp[i]=xp1[i];
			}
	}
	//now lets make an answer
	for(i=0;i<size;i++){
		f[i]=xp1[i];
		}
}
	
	/*
	//using BLAS to count xp1=(E-At)xp+tf
	//[1]creat blas matrix
	gsl_matrix_view blasE_ATt= gsl_matrix_view_array(E_ATt, size, size);
	gsl_matrix_view blasxp = gsl_matrix_view_array(xp, size, 1);
	gsl_matrix_view blassum = gsl_matrix_view_array(sum, size, 1);
	//[2]find sum=(E-At)xp
	gsl_blas_dgemm_(CblasNoTrans, CblasNoTrans,1.0, &blasE_ATt.matrix, &blasxp.matrix,0.0, &blassum.matrix);
	*/

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
	//getmyanswerviamethoditerations(200);
	//myprintf(2);
	
	
return 0;
}

