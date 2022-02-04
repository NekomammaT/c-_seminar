#include <iostream>
#include <fstream>
#include <vector>
#include "RK4.hpp" // RK4 を include

using namespace std;

vector<double> dxdt(double t, const vector<double> &x);

int main()
{
  double dt = 0.01;
  double t = 0;
  vector<double> x{1,0}; // 初期値
  double tf = 10; // 終了時刻

  ofstream ofs("oscillator.dat");

  // t が tf に到達するまで RK4 を実行。
  while (t<tf) {
    // ターミナルとファイルに出力
    cout << t << ' ' << x[0] << ' ' << x[1] << endl;
    ofs << t << ' ' << x[0] << ' ' << x[1] << endl;
    
    RK4<vector<double>>(dxdt,t,x,dt);
  }
}


// 調和振動子 EoM
vector<double> dxdt(double t, const vector<double> &x)
{
  vector<double> dxdt(2);

  dxdt[0] = x[1];
  dxdt[1] = -x[0];

  return dxdt;
}
