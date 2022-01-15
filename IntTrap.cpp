#define _USE_MATH_DEFINES

#include <sys/time.h>
#include <cmath>
#include <iostream>
#include <functional>

using namespace std;

double IntTrap(function<double(double)> func, double xmin, double xmax, int istep);
double ff(double x);
double gg(double x);

int main()
{
  // ---------------- start stop watch -----------------
  struct timeval tv;
  struct timezone tz;
  double before, after;
  
  gettimeofday(&tv, &tz);
  before = (double)tv.tv_sec + (double)tv.tv_usec * 1.e-6;
  // ---------------------------------------------------

  
  double xmin = 0;
  double xmax = 1;
  int istep = 1000;

  cout << IntTrap(ff,xmin,xmax,istep) << ' '
       << IntTrap(gg,xmin,xmax,istep) << endl;


  // ---------------- return elapsed time --------------
  gettimeofday(&tv, &tz);
  after = (double)tv.tv_sec + (double)tv.tv_usec * 1.e-6;
  cout << after - before << " sec." << endl;
  // ---------------------------------------------------
}


double IntTrap(function<double(double)> func, double xmin, double xmax, int istep) {
  double dx = (xmax-xmin)/istep;
  double IntTrap = (func(xmin)+func(xmax))/2.*dx;
  double x;

  for (int i=1; i<istep; i++) {
    x = xmin + i*dx;
    IntTrap += func(x)*dx;
  }

  return IntTrap;
}

double ff(double x) {
  return 4./(1+x*x);
}

double gg(double x) {
  return 2*sin(2*M_PI*x)*sin(2*M_PI*x);
}
