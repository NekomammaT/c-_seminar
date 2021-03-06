#define _USE_MATH_DEFINES

#include <algorithm> // 3つのmin
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
#define DTR 0.01 // 時間刻み dt は 0.01/H か 0.01a/k か 0.01/M の小さいものとする
#define KOH 1000
#define DLNK 1 // 波数として 1000H*exp(-2) 1000H*exp(-1), 1000H, 1000H*exp(1), 1000H*exp(2) の5つを用いる
#define FILE "double_chaotic_ptb.dat" // 出力ファイル名
#define DEXPN 0.01 // 毎ステップ出力してると大変なので 0.01 e-folds ごとに出力する

vector<vector<double>> dx0dt(double t, const vector<vector<double>> &x0);
vector<vector<vector<vector<complex<double>>>>>
ddxdt(double t, const vector<vector<double>> &x0, const vector<vector<vector<vector<complex<double>>>>> &dx,
      const vector<double> &kk);

double V(const vector<vector<double>> &x0);
double VI(const vector<vector<double>> &x0, int I);
double VIJ(const vector<vector<double>> &x0, int I, int J);
double H(const vector<vector<double>> &x0);
double Hdot(const vector<vector<double>> &x0);
double epsilon(const vector<vector<double>> &x0);

complex<double> calR(const vector<vector<double>> &x0, const vector<vector<vector<vector<complex<double>>>>> &dx, int ik, int al);
double calPR(const vector<vector<double>> &x0, const vector<vector<vector<vector<complex<double>>>>> &dx,
	     const vector<double> &kk, int ik);

static complex<double> II(0,1); // 虚数単位


int main()
{
  // 初期条件
  double t = 0;
  vector<vector<double>> x0{{PHII,1e-10},{PSII,0},{0}};

  double Hi = H(x0);
  vector<double> kk{KOH*Hi*exp(-2*DLNK), KOH*Hi*exp(-DLNK), KOH*Hi, KOH*Hi*exp(DLNK), KOH*Hi*exp(2*DLNK)};

  // dx は 5*2*2*2 行列
  vector<vector<vector<vector<complex<double>>>>>
    dx(kk.size(), vector<vector<vector<complex<double>>>>(x0.size()-1, vector<vector<complex<double>>>(x0.size()-1, vector<complex<double>>(2) ) ) );

  for (int ik=0; ik<kk.size(); ik++) {
    for (int al=0; al<x0.size()-1; al++) {
      for (int I=0; I<x0.size()-1; I++) {
	if (al == I) {
	  dx[ik][al][I][0] = 1./sqrt(2*kk[ik]);
	  dx[ik][al][I][1] = -II*kk[ik]*dx[ik][al][I][0];
	} else {
	  dx[ik][al][I][0] = 0;
	  dx[ik][al][I][1] = 0;
	}
      }
    }
  }

  // 出力ファイル準備
  ofstream ofs(FILE);

  double dt;   // 時間刻み準備
  double expN = 0; // 出力用 e-folds カウンタ

  while (epsilon(x0) < 1) {
    // データ書き出し
    if (x0[x0.size()-1][0] >= expN) {
      cout << t << ' ';
      ofs << t << ' ';
      for (vector<double> v : x0) {
	for (double e : v) {
	  cout << e << ' ';
	  ofs << e << ' ';
	}
      }
      cout << H(x0) << ' ' << epsilon(x0) << ' ';
      ofs << H(x0) << ' ' << epsilon(x0) << ' ';
      for (int ik=0; ik<kk.size(); ik++) {
	cout << calPR(x0,dx,kk,ik) << ' ';
	ofs << calPR(x0,dx,kk,ik) << ' ';
      }
      cout << endl;
      ofs << endl;

      expN += DEXPN; // カウンタ更新
    }
    
    dt = DTR*min({1./H(x0), exp(x0[x0.size()-1][0])/kk[kk.size()-1], 1./MM}); // 時間刻み
    RK4<vector<vector<double>>, vector<vector<vector<vector<complex<double>>>>>, vector<double>>(dx0dt,ddxdt,t,x0,dx,kk,dt); // RK4 1step
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
      const vector<double> &kk)
{
  double Hc = H(x0); // Hubble
  double N = x0[x0.size()-1][0]; // e-folds
  double aa = exp(N); // scale factor
  double ee = epsilon(x0); // SR param.
  
  vector<vector<vector<vector<complex<double>>>>> ddxdt = dx; // 初期化

  for (int ik=0; ik<ddxdt.size(); ik++) {
    for (int al=0; al<ddxdt[ik].size(); al++) {
      for (int I=0; I<ddxdt[ik][al].size(); I++) {
	// dphi の EoM
	ddxdt[ik][al][I][0] = dx[ik][al][I][1];
	ddxdt[ik][al][I][1] = -3*Hc*dx[ik][al][I][1] - kk[ik]*kk[ik]*dx[ik][al][I][0]/aa/aa;

	for (int J=0; J<ddxdt[ik][al].size(); J++) {
	  ddxdt[ik][al][I][1] += (-VIJ(x0,I,J) + (3+ee)*x0[I][1]*x0[J][1]
				  + x0[I][1]*dx0dt(t,x0)[J][1]/Hc + x0[J][1]*dx0dt(t,x0)[I][1]/Hc)*dx[ik][al][J][0];
	}
      }
    }
  }

  return ddxdt;
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

  for (int I; I<x0.size()-1; I++) {
    kinE += x0[I][1]*x0[I][1]/2.;
  }

  return sqrt( (kinE + V(x0)) / 3. );
}

double Hdot(const vector<vector<double>> &x0)
{
  double Hdot = 0;

  for (int I; I<x0.size()-1; I++) {
    Hdot -= x0[I][1]*x0[I][1]/2.;
  }

  return Hdot;
}

double epsilon(const vector<vector<double>> &x0)
{
  double Hc = H(x0);
  
  return -Hdot(x0)/Hc/Hc;
}


complex<double> calR(const vector<vector<double>> &x0, const vector<vector<vector<vector<complex<double>>>>> &dx, int ik, int al)
{
  complex<double> calR = 0;

  for (int I=0; I<dx[ik][al].size(); I++) {
    calR += x0[I][1]*dx[ik][al][I][0];
  }

  calR *= H(x0)/2./Hdot(x0);

  return calR;
}

double calPR(const vector<vector<double>> &x0, const vector<vector<vector<vector<complex<double>>>>> &dx,
	     const vector<double> &kk, int ik)
{
  double calPR = 0;

  for (int al=0; al<dx[ik].size(); al++) {
    calPR += kk[ik]*kk[ik]*kk[ik]/2./M_PI/M_PI*norm( calR(x0,dx,ik,al) );
  }

  return calPR;
}
