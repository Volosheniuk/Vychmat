#include <stdio.h>
#include <stdlib.h>
//#include <gnuplot.h>
#include <math.h>
#include <time.h>

/*list of functions
	0-- sin(x)  from 0 to pi/2   
	1-- x(10x+1)(10x+2) from 0 to 1  step 0.1   0.02
	2--ln(x)  from 0.01 to 1 
	3--exp(4x)sin(40px)  from 0 to 1
	4--xabs(x)  from -1 to 2  step 0.1  0.05 0.02 1/4 1/8 1/16 1/32 
	5--(1+x^(3/2))ln(x)  from 0 to 1 step  0.1  0.05 0.02 1/4 1/8 1/16 1/32
	* 
*/
//method 0 -rect, 1-trapeze, 2-Simson 

//func= f(x)

int getN_by_e(int method,double e,double a,double b,double M){
	int N;
	switch (method){
		case 0: {
					N=(int) 1.0/sqrtf((24.0*e)/((b-a)*(b-a)*(b-a)*M));
					if(0==N) return 1;
					return N;
		}
		case 1: {
					N=(int)  1.0/sqrtf((12.0*e)/((b-a)*(b-a)*(b-a)*M));			
					if(0==N) return 1;
					return N;
		}			
		case 2:{
					N=(int) sqrtf(sqrtf((powf((b-a),5)*M)/(2880*e)));
					if(0==N) return 1;
					return N;
		}
		default:{		printf("error\n");
					return 0;	
		}
		}
	
	}


float rectangleform(int N,double a,double b,int func){
double h;
double rez=0;
h=(b-a)/N;
int i;
switch (func){
	case 0:{
		for(i=0;i<N;i++){
			rez=rez+sin(a+h*i+h/2);
		}
		break;
	}
	case 1: {
		for(i=0;i<N;i++){
			//rez=func(a+h*i+h/2);
		}
		break;
	}
	case 2:{
		for(i=0;i<N;i++){
			//rez=func(a+h*i+h/2);
		}
		break;
	}
	case 3: {
		for(i=0;i<N;i++){
			//rez=func(a+h*i+h/2);
		}
		break;
	}
}
return rez*h;
}


float trapezeform(int N,double a,double b,double func){
float h;
float rez=0;
h=(b-a)/N;
int i;
switch (func){
	case 0:{
		for(i=0;i<N;i++){
			rez=rez+sin(a+h*i)+sin(a+h*(i+1));
		}
		break;
	}
	case 1: {
		for(i=0;i<N;i++){
			//rez=rez+func(a+h*i)+func(a+h*(i+1));
		}
		break;
	}
	case 2:{
		for(i=0;i<N;i++){
			//rez=rez+func(a+h*i)+func(a+h*(i+1));
		}
		break;
	}
	case 3: {
		for(i=0;i<N;i++){
			//rez=rez+func(a+h*i)+func(a+h*(i+1));
		}
		break;
	}
}
return rez*h/2.0;	
	}

float Simpson(int N,double a,double b,int func){
double h;
double rez=0;
h=(b-a)/N;
int i;
switch (func){
	case 0:{
		for(i=0;i<N;i++){
			rez=rez+sin(a+h*i)+4*sin(a+h*(i+1/2.0))+sin(a+h*(i+1));
		}
		break;
	}
	case 1: {
		for(i=0;i<N;i++){
			//rez=rez+func(a+h*i)+func(a+h*(i+1));
		}
		break;
	}
	case 2:{
		for(i=0;i<N;i++){
			//rez=rez+func(a+h*i)+func(a+h*(i+1));
		}
		break;
	}
	case 3: {
		for(i=0;i<N;i++){
			//rez=rez+func(a+h*i)+func(a+h*(i+1));
		}
		break;
	}
}
return rez*h/6.0;		

}

float findoptimalh(int method,double e,float a,float b,int func){
 double preJ,J;int n=2;
 double flag=3*e;
	switch (method){
			case 0: {
						preJ=rectangleform(1,a,b,func);
						do{
							J=rectangleform(n,a,b,func);
							n++;
							flag=fabs(J-preJ);
							preJ=J;
						}while(flag>e);
						return (b-a)/(n-1);
				}
			case 1:{
						preJ=trapezeform(1,a,b,func);
						do{
							J=trapezeform(n,a,b,func);
							n++;
							flag=fabs(J-preJ);
							preJ=J;
						}while(flag>e);
						return (b-a)/(n-1);
				
				}
			case 2:{
						preJ=Simpson(1,a,b,func);
						do{
							J=Simpson(n,a,b,func);
							n++;
							flag=fabs(J-preJ);
							preJ=J;
						}while(flag>e);
						return (b-a)/(n-1);
				}
	}
	
	
 	
	
}


float timeofwork(int method,int N,double a,double b,double func){
	clock_t t1,t2;
	switch (method){
		case 0: {
					t1=clock();
					rectangleform(N,a,b,func);
					t2=clock();
					return t2-t1;
		}
		case 1: {
					t1=clock();
					trapezeform(N,a,b,func);
					t2=clock();
					return t2-t1;
		}
		case 2:	{
					t1=clock();
					rectangleform(N,a,b,func);
					t2=clock();
					return t2-t1;
		}
		default:{
					return -1;
		}	
	}
	return ;
	}

void builddata_J_h(int method,double e,double a,double b,double M,int func){
int Nopt=2*getN_by_e(method,e,a,b,M);
		switch (method){
			case 0:{
						
			}
			default: {
					printf("error\n");
					break;
			}
		}
}

int main(){
	double ans=timeofwork(0,100000,0,1.57,0);
	printf("%f",ans);
return 0;
}