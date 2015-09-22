#include <iostream>
#include "gnuplot.h"
#include<cmath>
#include<fstream>
#include<iomanip>
using namespace std;
struct data{
 double h;
 double ans;
};
//global data
data mas[10000];
int lengthmas;
void norm(){
    double rez;
    double x;
    double h;
    x=20.0;
    h=1.0;
    int i=0;
    double truestory=exp(x);
    ofstream myfile("data.txt");
    while (h>0.00000001){
        rez=(-(1/12.0)*exp(x-2*h)+(4/3.0)*exp(x-h)+(-5/2.0)*exp(x)+(4/3.0)*exp(x+h)+(-1/12.0)*exp(x+2*h))/(h*h);
        myfile<<setprecision(10)<<log(h)<<"      "<<log(abs(rez-truestory))<<endl;
        mas[i].h=h;
        mas[i].ans=abs(rez-truestory);
        i++;
        h=h/2.0;
    }
    lengthmas=i;
    myfile.close();

}

int findmin(){
int i,q;
q=0;
double cop;
cop=mas[0].ans;
for (i=0;i<lengthmas;i++){
    if(mas[i].ans-cop<0){
        cop=mas[i].ans;
        q=i;
    }
}
return q;
}

void plottomin(int d,int q){
    ofstream myf("data2.txt");
    myf<<"#  x     y"<<endl;
    int i;
    if (0==q) {
        for( i=d;i<lengthmas;i++)
            myf<<setprecision(10)<<log(mas[i].h)<<"      "<<log(mas[i].ans)<<endl;
    }
    else {
        for(i=1;i<d+1;i++)
            myf<<setprecision(10)<<log(mas[i].h)<<"      "<<log(mas[i].ans)<<endl;
    }
    myf.close();
}

void worseres(){
ofstream f("data3.txt");
 double rez;
    double x;
    double h;
    x=20.0;
    h=1.0;
    double beststep=1;
    double privres=2*exp(x);
     while (h>0.00000001){
        rez=(exp(x-h)-2*exp(x)+exp(x+h))/(h*h);
        cout<<setprecision(10)<<"REAL="<<exp(x)<<"    MYREZ="<<rez<<endl;
        if (abs(exp(x)-rez)<(abs(exp(x)-privres))) {
            beststep=h;
            privres=rez;
        }
        f<<setprecision(10)<<log(h)<<"      "<<log(abs(rez-exp(x)))<<endl;
        h=h/2.0;
    }
    cout<<endl<<endl;
    cout<<"BEST STEP="<<beststep<<endl;

f.close();
}

int main()
{   int a;
    norm();
    Gnuplot gp;
    cout<<"List of commands"<<endl;
    cout<<"0--exit"<<endl<<"1--plot ln(delta)(ln(step))"<<endl<<"2--find tang1"<<endl<<"3--find tang2"<<endl<<"4--find best step "<<endl<<"5--worse results & plot graph"<<endl<<endl<<endl<<"Command:";
    while (true){
    cin>>a;
    switch (a){
    case 0:  return 0;
    case 1: {
                gp("plot 'data.txt' using 1:2\n");
                break;
            }
    case 2: {
                int d=findmin();
                plottomin(d,0);
                gp("plot 'data2.txt' using 1:2\n");
                gp("fit y=a*x+b'data.txt' via a,b");
                break;
            }
    case 3: {
                int d=findmin();
                plottomin(d,2);
                gp("plot 'data2.txt' using 1:2\n");
                gp("fit y=a*x+b'data.txt' via a,b");
                break;
            }
    case 4: {   int w=findmin();
                cout<<"BEST STEP="<<mas[w].h<<endl;
                break;
            }
    case 5: {
                worseres();
                gp("plot 'data3.txt' using 1:2\n");
                break;
            }

    }
    //return 0;
    cout<<endl<<"Command:";
    }
}
