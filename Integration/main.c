#include <stdio.h>
#include <stdlib.h>
//#include <gnuplot.h>
#include <math.h>
#include <time.h>
//#include <gsl/gsl_integration.h>
#define mypi     3.14159265358979323846

/*list of functions
	0-- sin(x)  from 0 to pi/2   
	1-- x(10x+1)(10x+2) from 0 to 1  step 0.1   0.02
	2--ln(x)  from 0.01 to 1 
	3--exp(4x)sin(40px)  from 0 to 1
	* 
*/
//global data 
int counter;



void my_handler (const char * reason,const char * file,int line,int gsl_errno){
   printf("Error: %s at %s:%d\n",reason,file,line);
};

void zerocounter(){
	counter=0;
	}
	
	
double f(double x, void * params) {
  counter++;
  return sin(x);
};

double f1(double x, void * params) {
  counter++;
  return x*(10*x+1)*(10*x+2);
};

double f2(double x, void * params) {
  counter++;
  return ln(x);
};
double f3(double x, void * params) {
  counter++;
  return exp(4*x)*sin(40*mypi*x);
};




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


double rectangleform(int N,double a,double b,int func){
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


double trapezeform(int N,double a,double b,double func){
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

double Simpson(int N,double a,double b,int func){
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

double findoptimalh(int method,double e,float a,float b,int func){
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


double timeofwork(int method,int N,double a,double b,double func){
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
	return -1;
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
	printf("Results:\n");
	printf("For integral sin(x) from 0 to pi/2  we have next:\n");
	double hrectangleform=findoptimalh(0,0.00001,0,mypi/2.0,0);
	int step =(int)(mypi/(2*hrectangleform));
	printf("OPtimal h for rectangelmethod (e=0.00001) is %le \n",hrectangleform);
	printf("Using it we have: I=%le",rectangleform(step,0,mypi/2,0));
	int number=0;
	printf("Number of callings f(x) is= %d",number);
	builddata_J_h(0,0.00001,0,mypi/2.0);
	printf("Dependence between |I-In|(h) is plotted in the pictire: Pic1\n");
	gsl_function FS;
    gsl_integration_workspace * WS;
	int i,j;
    double res,err;
    size_t neval;
    gsl_set_error_handler (my_handler);
    FS.function=f;
    counter=0;
    for(j=1;j<512;j*=2) {
      i=gsl_integration_qng(&FS, 0.0,(j+1)*M_PI,1.0e-8,1.0e-8, &res,&err,&neval);
      printf("%d: %le %le %ld %d\n",j,res,err,neval,counter);
   counter=0;

   };
	
	double ans=timeofwork(0,100000,0,1.57,0);
	printf("%f",ans);
return 0;
}
