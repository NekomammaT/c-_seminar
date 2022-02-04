#define _USE_MATH_DEFINES

#include <iostream>
#include <fstream>
#include <cmath>
#include <complex>
#include "vec_op.hpp"
#include "RK4.hpp"

using namespace std;

#define MM 9e-6 // phi の質量 M
#define mm 1e-6 // psi の質量 m
#define PHII 13 // phi0 の初期値
#define PSII 13 // psi0 の初期値
#define DTR 0.01 // 時間刻み dt は 0.01/H か 0.01a/k の小さい方とする
#define KOH 100
#define DLNK 0.01 // 波数として 100H*exp(-0.01), 100H, 100H*exp(0.01) の3つを用いる
#define FILE "double_chaotic_ptb.dat" // 出力ファイル名

vector<vector<double>> dx0dt(double t, const vector<vector<double>> &x0);
vector<vector<vector<vector<complex<double>>>>>
ddxdt(double t, const vector<vector<double>> &x0, const vector<vector<vector<vector<complex<double>>>>> &dx,
      const vector<double> kk);

double V(const vector<vector<double>> &x0);
double VI(const vector<vector<double>> &x0, int I);
double VIJ(const vector<vector<double>> &x0, int I, int J);
double H(const vector<vector<double>> &x0);
double Hdot(const vector<vector<double>> &x0);
double epsilon(const vector<vector<double>> &x0);


int main()
{
  // 初期条件
  double t = 0;
  vector<vector<double>> x0{{PHII,0},{PSII,0},{0}};

  // 出力ファイル準備
  ofstream ofs(FILE);

  // 時間刻み準備
  double dt;

  while (epsilon(x0) < 1) {
    // データ書き出し
    cout << t << ' ';
    ofs << t << ' ';
    for (vector<double> v : x0) {
      for (double e : v) {
	cout << e << ' ';
	ofs << e << ' ';
      }
    }
    cout << H(x0) << ' ' << epsilon(x0) << endl;
    ofs << H(x0) << ' ' << epsilon(x0) << endl;
    
    dt = DTR/H(x0); // 時間刻み
    RK4<vector<vector<double>>>(dx0dt,t,x0,dt); // RK4 1step
  }
}


vector<vector<double>> dx0dt(double t, const vector<vector<double>> &x0)
{
  double Hc = H(x0);
  
  vector<vector<double>> dx0dt = x0; // 初期化

  for (int I=0; I<dx0dt.size()-1; I++) {
    dx0dt[I][0] = x0[I][1];
    dx0dt[I][1] = -3*Hc*x0[I][1] - VI(x0,I);
  }

  dx0dt[dx0dt.size()-1][0] = Hc; // EoM

  return dx0dt;
}

vector<vector<vector<vector<complex<double>>>>>
ddxdt(double t, const vector<vector<double>> &x0, const vector<vector<vector<vector<complex<double>>>>> &dx,
      const vector<double> kk)
{
  return 0;
}


double V(const vector<vector<double>> &x0)
{
  double phi0 = x0[0][0];
  double psi0 = x0[1][0];
  
  return MM*MM*phi0*phi0/2. + mm*mm*psi0*psi0/2.;
}

double VI(const vector<vector<double>> &x0, int I)
{
  double phi0 = x0[0][0];
  double psi0 = x0[1][0];

  if (I == 0)
    return MM*MM*phi0;
  else
    return mm*mm*psi0;
}

double VIJ(const vector<vector<double>> &x0, int I, int J)
{
  if (I == 0 && J == 0)
    return MM*MM;
  else if (I == 1 && J == 1)
    return mm*mm;
  else
    return 0;
}

double H(const vector<vector<double>> &x0)
{
  double kinE = 0;

  for (vector<double> v : x0)
    kinE += v[1]*v[1];

  kinE /= 2.;
  return sqrt( (kinE + V(x0)) / 3. );
}

double Hdot(const vector<vector<double>> &x0)
{
  double Hdot = 0;

  for (vector<double> v : x0)
    Hdot -= v[1]*v[1];

  Hdot /= 2.;
  return Hdot;
}

double epsilon(const vector<vector<double>> &x0)
{
  double Hc = H(x0);
  
  return -Hdot(x0)/Hc/Hc;
}
