#define _USE_MATH_DEFINES

#include <iostream>
#include <fstream>
#include <cmath>
#include "vec_op.hpp"
#include "RK4.hpp"

using namespace std;

#define mm 1./9 // psi の質量 m
#define PHII 13 // phi0 の初期値
#define PSII 13 // psi0 の初期値
#define DTH 0.01 // 時間刻み dt は 0.01/H とする
#define FILE "double_chaotic_bg.dat" // 出力ファイル名

vector<vector<double>> dxdt(double t, const vector<vector<double>> &x);
double V(const vector<vector<double>> &x);
double Vphi(const vector<vector<double>> &x);
double Vpsi(const vector<vector<double>> &x);
double H(const vector<vector<double>> &x);
double epsilon(const vector<vector<double>> &x);


int main()
{
  // 初期条件
  double t = 0;
  vector<vector<double>> x{{PHII,0},{PSII,0},{0}};

  // 出力ファイル準備
  ofstream ofs(FILE);

  // 時間刻み準備
  double dt;

  while (epsilon(x) < 1) {
    // データ書き出し
    cout << t << ' ';
    ofs << t << ' ';
    for (vector<double> v : x) {
      for (double e : v) {
	cout << e << ' ';
	ofs << e << ' ';
      }
    }
    cout << H(x) << ' ' << epsilon(x) << endl;
    ofs << H(x) << ' ' << epsilon(x) << endl;
    
    dt = DTH/H(x); // 時間刻み
    RK4<vector<vector<double>>>(dxdt,t,x,dt); // RK4 1step
  }
}


vector<vector<double>> dxdt(double t, const vector<vector<double>> &x)
{
  // わかりやすく名前をつけておく
  double phi0 = x[0][0];
  double phi0dot = x[0][1];
  double psi0 = x[1][0];
  double psi0dot = x[1][1];
  double N = x[2][0];

  // Hubble は繰り返し使うので先に求めておく
  double Hc = H(x);
  
  vector<vector<double>> dxdt = x; // 初期化

  dxdt[0][0] = phi0dot;
  dxdt[1][0] = psi0dot; // phi0dot, psi0dot の定義

  dxdt[0][1] = - 3*Hc*phi0dot - Vphi(x);
  dxdt[1][1] = - 3*Hc*psi0dot - Vpsi(x);
  dxdt[2][0] = Hc; // EoM

  return dxdt;
}

double V(const vector<vector<double>> &x)
{
  double phi0 = x[0][0];
  double psi0 = x[1][0];
  
  return phi0*phi0/2. + mm*mm*psi0*psi0/2.;
}

double Vphi(const vector<vector<double>> &x)
{
  double phi0 = x[0][0];
  
  return phi0;
}

double Vpsi(const vector<vector<double>> &x)
{
  double psi0 = x[1][0];
  
  return mm*mm*psi0;
}

double H(const vector<vector<double>> &x)
{
  double phi0dot = x[0][1];
  double psi0dot = x[1][1];
  
  return sqrt( (phi0dot*phi0dot/2. + psi0dot*psi0dot/2. + V(x)) / 3. );
}

double epsilon(const vector<vector<double>> &x)
{
  double phi0dot = x[0][1];
  double psi0dot = x[1][1];
  
  return (phi0dot*phi0dot + psi0dot*psi0dot)/2./H(x)/H(x);
}
