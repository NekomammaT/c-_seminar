#define _USE_MATH_DEFINES

#include <sys/time.h>
#include <iostream>
#include <cmath>
#include "IntTrap.hpp" // ヘッダを読み込めば IntTrap 関数が使える

using namespace std;

double ff(vector<double> x);
double gg(vector<double> x);

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

  
  // ベタうち
  
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



  // ---------------- reset stop watch -----------------
  gettimeofday(&tv, &tz);
  before = (double)tv.tv_sec + (double)tv.tv_usec * 1.e-6;
  // ---------------------------------------------------
  
  // MultiIntTrap を使う

  vector<double> vmin{0,0};
  vector<double> vmax{1,1};
  vector<int> vstep{1000,1000};
  cout << ParaMultiIntTrap(ff,vmin,vmax,vstep) << endl;


  // ---------------- return elapsed time --------------
  gettimeofday(&tv, &tz);
  after = (double)tv.tv_sec + (double)tv.tv_usec * 1.e-6;
  cout << after - before << " sec." << endl;
  // ---------------------------------------------------


  
  // ---------------- reset stop watch -----------------
  gettimeofday(&tv, &tz);
  before = (double)tv.tv_sec + (double)tv.tv_usec * 1.e-6;
  // ---------------------------------------------------
  
  // 3変数積分。積分範囲もそれぞれ違う

  vector<double> v2min{0,M_PI,1};
  vector<double> v2max{1,3*M_PI,11};
  vector<int> v2step{100,100,1000};
  cout << ParaMultiIntTrap(gg,v2min,v2max,v2step) << endl;


  // ---------------- return elapsed time --------------
  gettimeofday(&tv, &tz);
  after = (double)tv.tv_sec + (double)tv.tv_usec * 1.e-6;
  cout << after - before << " sec." << endl;
  // ---------------------------------------------------
}


double ff(vector<double> x) {
  return 4./(1+x[0]*x[0])*2*cos(2*M_PI*x[1])*cos(2*M_PI*x[1]);
}

double gg(vector<double> x) {
  return 4./(1+x[0]*x[0])*cos(x[1])*cos(x[1])/M_PI
    *sin(2*M_PI*x[2])*sin(2*M_PI*x[2])/5;
}
