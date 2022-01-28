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

// 他変数関数 func を Ix 番目の変数に関して xmin から xmax まで istep 分割で積分
// 積分変数以外の変数は値 y に固定
double IntTrap(function<double(vector<double>)> func, int Ix, double xmin, double xmax, int istep, vector<double> y);

// 上記の関数をそれぞれ並列化
double ParaIntTrap(function<double(double)> func, double xmin, double xmax, int istep);
double ParaIntTrap(function<double(vector<double>)> func, int Ix, double xmin, double xmax, int istep, vector<double> y);
// ------------------------------------------------------------------------------------




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

double ParaIntTrap(function<double(double)> func, double xmin, double xmax, int istep) {
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

#endif
