#include <iostream>
#include "gnuplot.h"
#include<cmath>
#include<fstream>
#include<iomanip>
#include "gnuplot.h"
#include <stdio.h>
using namespace std;
double mysinx(double x,int n){
        double cop=x;
	double sum=0.0;
	if (n<=1) return x;
	else{
		for (int i=1;i<n;i++){
			sum+=cop;
			cop*=-1.0*x*x/((2 * i) * (2 * i + 1));
		}
		return sum;
	    }
}

int main(){
	Gnuplot gp;
	ofstream myfile("data.txt");
	ofstream myfile2("data2.txt");
	int i;
	double ans=25.5;
	for(i=1;i<18;i++){
		myfile<<setprecision(10)<<i<<"      "<<log(abs(mysinx(ans,i)-sin(ans)))<<endl;
	}
	ans=600.452253;
	while(ans>0.0000000000000001){
		myfile2<<setprecision(10)<<ans<<"      "<<log(abs(mysinx(ans,i)-sin(ans)))<<endl;
		ans=ans/2.0;
	}
	int mycommand=0;
	
	while (mycommand!=3){
		cin>>mycommand;
		switch (mycommand) {
			case 1:	{gp("plot 'data.txt' using 1:2\n");
					break;
			}
			case 2: {gp("plot 'data2.txt' using 1:2\n");
					break;
			}
		}
	}
	
	
	myfile.close();
	myfile2.close();
return 0;
}
