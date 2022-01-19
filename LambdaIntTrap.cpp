#define _USE_MATH_DEFINES

#include <cmath>
#include <sys/time.h>
#include <iostream>
#include <functional>
#include <vector>

using namespace std;

double IntTrap(function<double(vector<double>)> func, int Ix, double xmin, double xmax, int istep, vector<double> y);
double ff(vector<double> x);

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
  vector<double> v{0,0};
  
  function<double(vector<double>)> intfx = [xmin,xmax,istep](vector<double> y){ return IntTrap(ff,0,xmin,xmax,istep,y); };
  cout << IntTrap(intfx,1,xmin,xmax,istep,v) << endl;


  // ---------------- return elapsed time --------------
  gettimeofday(&tv, &tz);
  after = (double)tv.tv_sec + (double)tv.tv_usec * 1.e-6;
  cout << after - before << " sec." << endl;
  // ---------------------------------------------------
}


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

double ff(vector<double> x) {
  return 4./(1+x[0]*x[0])*2*cos(2*M_PI*x[1])*cos(2*M_PI*x[1]);
}
