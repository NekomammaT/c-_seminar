#include <sys/time.h>
#include <iostream>
#include "IntTrap.hpp"

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
  
#ifdef _OPENMP
  cout << "OpenMP : Enabled (Max # of threads = " << omp_get_max_threads() << ")" << endl;
#endif

  
  double xmin = 0;
  double xmax = 1;
  int istep = 1000;
  vector<double> v{0,0};
  
  function<double(vector<double>)> intfx = [xmin,xmax,istep](vector<double> y){ return IntTrap(ff,0,xmin,xmax,istep,y); };
  cout << ParaIntTrap(intfx,1,xmin,xmax,istep,v) << endl;


  // ---------------- return elapsed time --------------
  gettimeofday(&tv, &tz);
  after = (double)tv.tv_sec + (double)tv.tv_usec * 1.e-6;
  cout << after - before << " sec." << endl;
  // ---------------------------------------------------
}


double ff(vector<double> x) {
  return 4./(1+x[0]*x[0])*2*cos(2*M_PI*x[1])*cos(2*M_PI*x[1]);
}
