#define _USE_MATH_DEFINES

#include <cmath>
#include <functional>
#include <vector>
#ifdef _OPENMP
#include <omp.h>
#endif

using namespace std;

double IntTrap(function<double(vector<double>)> func, int Ix, double xmin, double xmax, int istep, vector<double> y);
double ParaIntTrap(function<double(vector<double>)> func, int Ix, double xmin, double xmax, int istep, vector<double> y);


double IntTrap(function<double(vector<double>)> func, int Ix, double xmin, double xmax, int istep, vector<double> y) {
  double dx = (xmax-xmin)/istep;
  double IntTrap = 0, x;

  for (int i=0; i<=istep; i++) {
    x = xmin + i*dx;
    y[Ix] = x;

    if (i==0 || i==istep) {
      IntTrap += func(y)*dx/2.;
    } else {
      IntTrap += func(y)*dx;
    }
  }

  return IntTrap;
}

double ParaIntTrap(function<double(vector<double>)> func, int Ix, double xmin, double xmax, int istep, vector<double> y) {
  double dx = (xmax-xmin)/istep;
  double IntTrap = 0;

#ifdef _OPENMP
#pragma omp parallel for
#endif
  for (int i=0; i<=istep; i++) {
    double x = xmin + i*dx;
    vector<double> yy = y;
    yy[Ix] = x;

    if (i==0 || i==istep) {
#ifdef _OPENMP
#pragma omp atomic
#endif
      IntTrap += func(yy)*dx/2.;
    } else {
#ifdef _OPENMP
#pragma omp atomic
#endif
      IntTrap += func(yy)*dx;
    }
  }

  return IntTrap;
}


