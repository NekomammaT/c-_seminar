#include <iostream>
#include "vec_op.hpp"

using namespace std;

int main()
{
  vector<vector<double>> v1{{1,2},{3,4}}, v2{{5,6},{7,8}};
  v1 += v2;

  cout << v1[0][0] << ' ' << v1[0][1] << ' '
       << v1[1][0] << ' ' << v1[1][1] << endl;
}
