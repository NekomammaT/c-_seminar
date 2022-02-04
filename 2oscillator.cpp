#include <iostream>
#include <fstream>
#include <vector>
#include "RK4.hpp" // RK4 を include

using namespace std;

// 2個の独立な振動子系
// x[0][0] = x, x[0][1] = xdot, x[1][0] = y, x[1][1] = ydot
vector<vector<double>> dxdt(double t, const vector<vector<double>> &x);

int main()
{
  double dt = 0.01;
  double t = 0;
  vector<vector<double>> x{{1,0},{0,1}}; // 初期値
  double tf = 10; // 終了時刻

  ofstream ofs("2oscillator.dat");

  // t が tf に到達するまで RK4 を実行。
  while (t<tf) {
    // ターミナルとファイルに出力
    cout << t << ' ' << x[0][0] << ' ' << x[0][1] << ' '
	 << x[1][0] << ' ' << x[1][1] << endl;
    ofs << t << ' ' << x[0][0] << ' ' << x[0][1] << ' '
	<< x[1][0] << ' ' << x[1][1] << endl;
    
    RK4<vector<vector<double>>>(dxdt,t,x,dt);
  }
}


// 調和振動子 EoM
vector<vector<double>> dxdt(double t, const vector<vector<double>> &x)
{
  vector<vector<double>> dxdt = x; // x のサイズで初期化しとけば楽

  for (int i=0; i<x.size(); i++) {
    dxdt[i][0] = x[i][1];
    dxdt[i][1] = -x[i][0];
  }

  return dxdt;
}
