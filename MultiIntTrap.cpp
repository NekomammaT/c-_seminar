#define _USE_MATH_DEFINES

#include <sys/time.h>
#include <cmath>
#include <iostream>
#include <functional>
#include <vector>

using namespace std;

#define XMIN 0
#define XMAX 1
#define ISTEP 1000

double IntTrap(function<double(vector<double>)> func, int Ix, double xmin, double xmax, int istep, vector<double> y);
double intfx(vector<double> y);
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
  
  
  vector<double> v{0,0};
  
  cout << IntTrap(intfx,1,XMIN,XMAX,ISTEP,v) << endl;


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

double intfx(vector<double> y) {
  return IntTrap(ff,0,XMIN,XMAX,ISTEP,y);
}

double ff(vector<double> x) {
  return 4./(1+x[0]*x[0])*2*cos(2*M_PI*x[1])*cos(2*M_PI*x[1]);
}
