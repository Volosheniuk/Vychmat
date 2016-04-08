#include <iostream>
#include "gnuplot.h"
#include <fstream>
#include <stdio.h>
#include<fstream>
#include<iomanip>
#include <cstdlib>
#include <math.h>
using namespace std;

//define zone
#define kapa 0.9
#define ul 0.0
#define ur 0.0
#define damp 20

int main(){
	Gnuplot gp;
	double *u;
	double *u1;
	int m,i,j;
	ofstream answer("data.txt");
for(int k=0; k<1000; k++){
	m=k;
	double h=1.0/(double)m;
	
	double myytime=h*h/2.0/kapa;
	
	u=(double*)malloc(m*sizeof(double));
	u1=(double*)malloc(m*sizeof(double));
  //at the beg
	for(i=0;i<m;i++){
		u[i]=sin(i*3.14/m);
		u1[i]=sin(i*3.14/m);
	}
 //main part
 
 	for(j=0;j<damp;j++){
		for(i=0;i<m;i++){
			if(i==0){
				u1[0]=u[0]+kapa*myytime/h/h*(u[1]+ul-2*u[0]);
			}
			else if(i==(m-1)){
				u1[m-1]=u[m-1]+kapa*myytime/h/h*(ur+u[m-2]-2*u[m-1]);
			}else{
				u1[i]=u[i]+kapa*myytime/h/h*(u[i+1]+u[i-1]-2*u[i]);
			}			
		}
	//swap
	     for(i=0;i<m;i++){
			u[i]=u1[i];	
		}
	//write after step
	
	}	
	for(j=0;j<m;j++){
		u1[j]=u[j]-exp(-kapa*damp)*sin(i*3.14/m);
		}
	double ans=0;
	for(j=0;j<m;j++){
		ans=ans+u1[j];
		}
	answer<<h<<"   "<<sqrt(ans)<<endl;
	
	
	}
	gp("plot 'data.txt' using 1:2 \n");
return 0;
}
