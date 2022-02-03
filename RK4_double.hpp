#ifndef INCLUDED_RK4_hpp_

#define INCLUDED_RK4_hpp_

#include <functional>
#include "vec_op.hpp"

using namespace std;

void RK4(function<vector<double>(double,vector<double>)> dxdt,
	 double &t, vector<double> &x, double dt);


// t と x は更新するので参照渡し
void RK4(function<vector<double>(double,vector<double>)> dxdt,
	 double &t, vector<double> &x, double dt)
{
  // ---------- RK4 の Butcher 係数 ------------------
  double a[4][4], b[4], c[4];

  a[0][0]=0;     a[0][1]=0;     a[0][2]=0;    a[0][3]=0;
  a[1][0]=1./2;  a[1][1]=0;     a[1][2]=0;    a[1][3]=0;
  a[2][0]=0;     a[2][1]=1./2;  a[2][2]=0;    a[2][3]=0;
  a[3][0]=0;     a[3][1]=0;     a[3][2]=1;    a[3][3]=0;
  
  b[0]=1./6;     b[1]=1./3;     b[2]=1./3;    b[3]=1./6;
  
  c[0]=0;        c[1]=1./2;     c[2]=1./2;    c[3]=1;
  // ------------------------------------------------


  vector<double> k[4]; // 4つの k_i
  vector<double> y; // k_i を求めるには y = x + dt sum_j^(i-1) a_ij k_j が必要


  for (int i=0; i<4; i++) {
    y = x;

    for (int j=0; j<i; j++) {
      y += dt * a[i][j] * k[j];
    }

    k[i] = dxdt(t+c[i]*dt, y);
  }

  
  t += dt; // t を更新

  for (int i=0; i<4; i++) {
    x += dt * b[i] * k[i]; // x を更新
  }
}

#endif
