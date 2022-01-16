#include <iostream>

using namespace std;

int main()
{
  cout << "x = ?" << endl;

  double x; // 入力された実数を代入するための変数を宣言
  cin >> x; // 入力された実数を x に代入

  cout << "x = " << x << endl; // x の値を確認
  cout << "x^2 = " << x*x << endl; // x の 2 乗を出力
}
