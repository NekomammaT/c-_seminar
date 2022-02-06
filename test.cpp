#include <iostream>
#include <complex>
#include "vec_op.hpp"

using namespace std;

int main()
{
  vector<vector<vector<complex<double>>>> v1(2, vector<vector<complex<double>>>(2, vector<complex<double>>(2) ) );

  for (int i=0; i<2; i++) {
    for (int j=0; j<2; j++) {
      for (int k=0; k<2; k++) {
	v1[i][j][k] = 1;
      }
    }
  }
  
  v1[0] *= 3.;

  for (vector<vector<complex<double>>> m : v1) {
    for (vector<complex<double>> v : m) {
      for (complex<double> e : v) {
	cout << e << ' ';
      }
      cout << endl;
    }
    cout << endl;
  }
}
