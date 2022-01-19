#define _USE_MATH_DEFINES
#include <cmath> // 基本的な数学関数や定数のライブラリ。この2つはセット

#include <sys/time.h> // ストップウォッチ用
#include <iostream>

using namespace std;

// 2つの被積分関数
double ff(double x) {
  return 4./(1+x*x);
}

double gg(double x) {
  return 2*sin(2*M_PI*x)*sin(2*M_PI*x);
}


int main()
{
  // ---------------- start stop watch -----------------
  struct timeval tv;
  struct timezone tz;
  double before, after;
  
  gettimeofday(&tv, &tz);
  before = (double)tv.tv_sec + (double)tv.tv_usec * 1.e-6;
  // ---------------------------------------------------

  
  double xmin = 0; // 積分下端
  double xmax = 1; // 上端
  int istep = 1000; // 分割数 n

  double dx = (xmax-xmin)/istep;
  double IntTrap = (ff(xmin)+ff(xmax))/2.*dx; // 最初と最後だけ足しておく
  double x; // 積分変数

  for (int i=1; i<istep; i++) {
    x = xmin + i*dx; 
    IntTrap += ff(x)*dx;
  }
  
  cout << IntTrap << endl;


  IntTrap = (gg(xmin)+gg(xmax))/2.*dx;

  for (int i=1; i<istep; i++) {
    x = xmin + i*dx;
    IntTrap += gg(x)*dx;
  }

  cout << IntTrap << endl;

  
  // ---------------- return elapsed time --------------
  gettimeofday(&tv, &tz);
  after = (double)tv.tv_sec + (double)tv.tv_usec * 1.e-6;
  cout << after - before << " sec." << endl;
  // ---------------------------------------------------
}



