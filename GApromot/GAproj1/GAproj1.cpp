// GAproj1.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"

#define M_PI 3.14159265358979323846

double funcx1(double x1,double x2);
double funcx2(double x1,double x2);
double funcx3(double x1,double x2);
double funcx4(double x1,double x2);
double funcx5(double x1,double x2);

int _tmain(int argc, _TCHAR* argv[])
{
	GA x(18,256,2,0.95,0.05,2000,2.0000,-0.0000);
	x.fitness_function = funcx3 ;
	x.population_initialize();
	x.iteration_procedure();
	system("Pause");
	return 0;
}


double funcx1(double x1,double x2)  //-10.0000<=x1,x2<=10.0000
{
	if(x1==0)
		x1 += 1e-6;
	if(x2==0)
		x2 += 1e-6;
	return sin(x1)/x1*sin(x2)/x2;
}

double funcx2(double x1,double x2)  //-10.0000<=x1,x2<=10.0000
{
	return 0.9*exp(-1*(pow(x1+5,2)+pow(x2+5,2))/10.0)+0.99996*exp(-1*(pow(x1-5,2)+pow(x2-5,2))/20.0);
}
double funcx3(double x1,double x2)  //-5.0000<=x1,x2<=5.0000
{
	return -1*(100*pow((x2-pow(x1,2)),2)+pow(1-x1,2));
}
double funcx4(double x1,double x2)  //-5.0000<=x1,x2<=5.0000
{
	return -1*(20+pow(x1,2)+pow(x2,2)-10*(cos(2*M_PI*x1)+cos(2*M_PI*x2)));
}

double funcx5(double x1,double x2)   //-1.0000<=x1,x2<=2.0000
{
	return x1*sin(10*M_PI*x1)+x2*sin(10*M_PI*x2);
}