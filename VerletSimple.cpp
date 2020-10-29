
#include <cmath>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <armadillo>
#include <string>
using namespace  std;
using namespace  arma;
double pi=acos(-1);

int main(int argc, char* argv[])
{
    string filename;
    ofstream myfile;
    filename = "testEarth";
    filename.append(".txt");
    myfile.open(filename);

    double G = 6.67*pow(10,-11);
    double Ms = 2*pow(10,30);
    double mu_s = G*Ms;
    int epochs = 10000;
    double timeProp = 1;
    double v = 2*pi;
    double v2 = v*v;
    double *x,*y,*vx,*vy;
    x = new double[epochs];
    y = new double[epochs];
    vx = new double[epochs];
    vy = new double[epochs];
    double h = timeProp/(epochs-1);
    x[0]=1; y[0]=vx[0]=0; vy[0] = v;
    for (int i = 0; i < epochs; i++)
    {
        x[i+1] = x[i] + h*vx[i] - h*h*(4*pi*pi)*x[i];
        y[i+1] = y[i] + h*vy[i] - h*h*(4*pi*pi)*y[i];
        vx[i+1] = vx[i]-h/2*(4*pi*pi)*(x[i]+x[i+1]);
        vy[i+1] = vy[i]-h/2*(4*pi*pi)*(y[i]+y[i+1]);
    }
    for(int i=0;i<epochs;i++){
        myfile << setw(15) << setprecision(8) << x[i];
        myfile << setw(15) << setprecision(8) << y[i];
        myfile << setw(15) << setprecision(8) << vx[i];
        myfile << setw(15) << setprecision(8) << vy[i];
        myfile << endl;
    }
    myfile.close();
return 0;
}   //  End of main function 