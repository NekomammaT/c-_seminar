#define _USE_MATH_DEFINES

#include <cmath>
#include <sys/time.h>
#include <iostream>
#include <functional>
#include <vector>

using namespace std;

// コード全体を通じて積分パラメータを使いたいのでマクロを使う
#define XMIN 0
#define XMAX 1
#define ISTEP 1000

// 多変数関数 func を Ix 番目の変数に関して xmin から xmax まで istep 分割で積分
// 積分変数以外の変数は値 y に固定
double IntTrap(function<double(vector<double>)> func, int Ix, double xmin, double xmax, int istep, vector<double> y);

double intfx(vector<double> y); // ff を x についてのみ定積分した関数

double ff(vector<double> x); // 2変数関数


int main()
{
  // ---------------- start stop watch -----------------
  struct timeval tv;
  struct timezone tz;
  double before, after;
  
  gettimeofday(&tv, &tz);
  before = (double)tv.tv_sec + (double)tv.tv_usec * 1.e-6;
  // ---------------------------------------------------
  
  
  vector<double> v{0,0}; // IntTrap の性質上テキトーな vector が必要
  
  cout << IntTrap(intfx,1,XMIN,XMAX,ISTEP,v) << endl; // 1番目の変数を積分


  // ---------------- return elapsed time --------------
  gettimeofday(&tv, &tz);
  after = (double)tv.tv_sec + (double)tv.tv_usec * 1.e-6;
  cout << after - before << " sec." << endl;
  // ---------------------------------------------------
}


double IntTrap(function<double(vector<double>)> func, int Ix, double xmin, double xmax, int istep, vector<double> y) {
  double dx = (xmax-xmin)/istep;
  double IntTrap = 0; // 積分結果用変数。まず 0 にセット
  double x; // 積分変数

  for (int i=0; i<=istep; i++) {
    x = xmin + i*dx;
    y[Ix] = x; // 変数ベクトル y の Ix 番目だけ積分変数 x に変更

    if (i==0 || i==istep) {
      IntTrap += func(y)*dx/2.; // 最初と最後だけ 1/2
    } else {
      IntTrap += func(y)*dx;
    }
  }

  return IntTrap;
}

double intfx(vector<double> y) {
  return IntTrap(ff,0,XMIN,XMAX,ISTEP,y); // 0番目の変数を積分
}

double ff(vector<double> x) {
  return 4./(1+x[0]*x[0])*2*cos(2*M_PI*x[1])*cos(2*M_PI*x[1]);
}
