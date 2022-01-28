#include <iostream>
#include <fstream>
#include <vector>
#include "RK4.hpp"

using namespace std;

vector<double> dxdt(double t, vector<double> x);

int main()
{
  double dt = 0.01;
  double t = 0;
  vector<double> x{1,0};
  double tf = 10;

  ofstream ofs("oscillator.dat");
  
  cout << t << ' ' << x[0] << ' ' << x[1] << endl;
  ofs << t << ' ' << x[0] << ' ' << x[1] << endl;
  
  while (t<tf) {
    RK4(dxdt,t,x,dt);
    cout << t << ' ' << x[0] << ' ' << x[1] << endl;
    ofs << t << ' ' << x[0] << ' ' << x[1] << endl;
  }
}


vector<double> dxdt(double t, vector<double> x) {
  vector<double> dxdt(2);

  dxdt[0] = x[1];
  dxdt[1] = -x[0];

  return dxdt;
}
