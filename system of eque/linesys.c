#include <stdio.h>
#include <time.h>
#include <math.h>
#define size 4  /*dimension of matrix*/
#define econs  0.0001
//here is global data
	//time
		clock_t starttime;
		clock_t endtime;
	//matrix
		float A[size][size];
		float E_At[size][size];
		float f[size];
		int c1,c2,pivot[size],ok;
		float AT [size*size];
		float E_ATt [size*size];
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
//ittt method
void getmyanswerviamethoditerations(int p){//f is an answer like in lapack
	int i,j;
	float xp[size];
	float xp1[size];
	float sum;
	float t=0.5;
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
	//printf("here is an E-At")
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
//end of itt method
float findnormavector(float a[]){
	int i;
	float sum=0.0;
	for(i=0;i<size;i++){
		sum=sum+a[i];
		}
	return sum;
}
float findnormamatrixA(float matrix[]){
	int i,j;
	float sum=0;
	float ans=-65000.0;
	for (i=0;i<size;i++){
		ans=ans+matrix[i];
		}
	for(i=1;i<size;i++){
		sum=0;
		for(j=0;j<size;j++){
			sum=sum+matrix[i*size+j];
			
			}
		if(sum>ans) ans=sum;  
		}
	return ans;
	}
void lapackwork(){
	//lapack is working here
		c1=size;
		c2=1;
	starttime=clock();
	sgesv_(&c1, &c2, AT, &c1, pivot, f, &c1, &ok);
	endtime=clock();
		
}
void itmethodwork(int p){
	starttime=clock();
	getmyanswerviamethoditerations(p);
	endtime=clock();		
}
int findm(){
	int res=0;
	float x0[size];
	float x1[size];
	int i,j;
	for (i=0;i<size;i++){
		x0[i]=1;
		}
	//get E-tA
	for (i=0;i<size;i++){
		for(j=0;j<size;j++){
			if(i==j){
					E_At[i][j]=1-0.5*A[i][j];
					}
			else E_At[i][j]=-0.5*A[i][j];
			}
		}
	for (i=0; i<size; i++){
		for(j=0; j<size; j++) E_ATt[i*size+j]=E_At[j][i];		
	}
	float q;
	for(i=0;i<size;i++){
		for(j=0;j<size;j++){
			printf("%f   ",E_ATt[i*size+j]);
			}
			printf("\n");
		}
	 if(findnormamatrixA(E_ATt)>=0) q=findnormamatrixA(E_ATt);
	 else q=(-1.0)*findnormamatrixA(E_ATt);
	if (q==0) printf("Erorrr\n");
	printf("q%f\n",q);
	//lets find ||x1-x0||
	float sum=0;
	for (i=0;i<size;i++){
			for(j=0;j<size;j++){
				sum=sum+E_At[i][j]*x0[j];
				}
			x1[i]=sum+f[i];
			sum=0;
			}
	for(i=0;i<size;i++){
		x1[i]=x1[i]-x0[i];
		}
	float qq;
	if(findnormavector(x1)>=0) qq=findnormavector(x1);
	else qq=(-1.0)*findnormavector(x1);
	printf("qq%f\n",qq);
	res=log(econs*(1-q)/qq)/log(q);
	return res;
	}
int main(){
	makematrixA();
	mymakef();
	int command=1000;
	while (command!=0){
		printf("Your command:");
		scanf("%d",&command);
		switch (command){
			case 1: {
						printmatrixA();
						break;
					}
			case 2: {
						mymakef();
						myprintf(1);
						break;
					}
			case 3: {
						lapackwork();
						//lapack have done it
						printf("Answer of working lapack\n");
						myprintf(2);
						printf("Lapack time:=%d\n",endtime-starttime);
						printf("********************************\n");
						printf("\n");
						break;
					}
			case 4: {
						itmethodwork(100);
						printf("Answer of working it method (3)\n");
						myprintf(2);
						printf("It method m=100 time:=%d\n",endtime-starttime);
						printf("********************************\n");
						break;
					}
			case 5: {
						printf("OPtimal m=%d\n",findm());
						break;
					}
			case 6: {

					}
			}
		}
		
	
	
	
return 0;
}

