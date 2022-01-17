#include <iostream>
#include <vector>

using namespace std;

vector<double> f(vector<double> &v) { // 2番目の要素だけ2倍した vector を返す
  v[1] *= 2;
  return v;
}

int main()
{
  vector<double> v1{1,2,3};
  vector<double> v2;

  cout << v1[0] << ' ' << v1[1] << ' ' << v1[2] << endl;

  v2 = f(v1);

  cout << v1[0] << ' ' << v1[1] << ' ' << v1[2] << endl; // 参照渡しにしたので v1 も変わる
  cout << v2[0] << ' ' << v2[1] << ' ' << v2[2] << endl;
}
