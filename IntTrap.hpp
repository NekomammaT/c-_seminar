#ifndef INCLUDED_IntTrap_hpp_

#define INCLUDED_IntTrap_hpp_

#include <functional>
#include <vector>
#ifdef _OPENMP
#include <omp.h>
#endif

using namespace std;

// ---------------- 引数が違えば同名の異なった関数を複数定義できる --------------------
// x の関数 func(x) を xmin から xmax まで istep 分割で積分する
double IntTrap(function<double(double)> func, double xmin, double xmax, int istep);

// 多変数関数 func を Ix 番目の変数に関して xmin から xmax まで istep 分割で積分
// 積分変数以外の変数は値 y に固定
double IntTrap(function<double(vector<double>)> func, int Ix, double xmin, double xmax, int istep, vector<double> y);

// 多変数関数 func を xmin から xmax まで istep 分割で多重積分
double MultiIntTrap(function<double(vector<double>)> func, vector<double> xmin, vector<double> xmax, vector<int> istep);

// 上記の関数をそれぞれ並列化
double ParaIntTrap(function<double(double)> func, double xmin, double xmax, int istep);
double ParaIntTrap(function<double(vector<double>)> func, int Ix, double xmin, double xmax, int istep, vector<double> y);
double ParaMultiIntTrap(function<double(vector<double>)> func, vector<double> xmin, vector<double> xmax, vector<int> istep);
// ------------------------------------------------------------------------------------




double IntTrap(function<double(double)> func, double xmin, double xmax, int istep)
{
  double dx = (xmax-xmin)/istep;
  double IntTrap = (func(xmin)+func(xmax))/2.*dx;
  double x;

  for (int i=1; i<istep; i++) {
    x = xmin + i*dx;
    IntTrap += func(x)*dx;
  }

  return IntTrap;
}

double IntTrap(function<double(vector<double>)> func, int Ix, double xmin, double xmax, int istep, vector<double> y)
{
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

double MultiIntTrap(function<double(vector<double>)> func, vector<double> xmin, vector<double> xmax, vector<int> istep)
{
  // IntTrap 用のダミー変数
  vector<double> v = xmin;

  // 0番目からi番目の変数まで積分し終わった関数を順に定義していく
  vector<function<double(vector<double>)>> intfx(xmin.size());

  // 0番目は func を0番目について積分
  // func はグローバルに定義されてないので lambda 式にキャプチャする必要がある
  intfx[0] = [func,xmin,xmax,istep](vector<double> y) {
    return IntTrap(func,0,xmin[0],xmax[0],istep[0],y);
  };

  // 以降i番目は intfx[i-1] をi番目について積分
  // intfx, i はグローバルに定義されてないので lambda 式にキャプチャする必要がある
  for (int i=1; i<xmin.size(); i++) {
    intfx[i] = [intfx,i,xmin,xmax,istep](vector<double> y) {
      return IntTrap(intfx[i-1],i,xmin[i],xmax[i],istep[i],y);
    };
  }

  // 求めるべきは最後の関数
  return intfx[xmin.size()-1](v);
}


double ParaIntTrap(function<double(double)> func, double xmin, double xmax, int istep)
{
  double dx = (xmax-xmin)/istep;
  double IntTrap = (func(xmin)+func(xmax))/2.*dx;
  double x;

#ifdef _OPENMP
#pragma omp parallel for
#endif
  for (int i=1; i<istep; i++) {
    x = xmin + i*dx;

#ifdef _OPENMP
#pragma omp atomic
#endif
    IntTrap += func(x)*dx;
  }

  return IntTrap;
}

double ParaIntTrap(function<double(vector<double>)> func, int Ix, double xmin, double xmax, int istep, vector<double> y)
{
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

double ParaMultiIntTrap(function<double(vector<double>)> func, vector<double> xmin, vector<double> xmax, vector<int> istep)
{
  vector<double> v = xmin;
  int xsize = xmin.size();
  vector<function<double(vector<double>)>> intfx(xsize);

  intfx[0] = [func,xmin,xmax,istep](vector<double> y) {
    return IntTrap(func,0,xmin[0],xmax[0],istep[0],y);
  };

  for (int i=1; i<xmin.size()-1; i++) {
    intfx[i] = [intfx,i,xmin,xmax,istep](vector<double> y) {
      return IntTrap(intfx[i-1],i,xmin[i],xmax[i],istep[i],y);
    };
  }

  // 大外だけ ParaIntTrap にして返す
  return ParaIntTrap(intfx[xsize-2],xsize-1,xmin[xsize-1],xmax[xsize-1],istep[xsize-1],v);
}


#endif
