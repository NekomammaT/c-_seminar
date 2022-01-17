#include <iostream>

using namespace std;

void f(double* p) { // ポインタ p を受け取る
  cout << *p << ' ' << p << endl; // p の指す変数 *p と p そのもの (アドレス) を表示
  *p *= 5; // p の指す変数を 5 倍
  cout << *p << endl;
}

int main()
{
  double x = 2;
  cout << x << ' ' << &x << endl; // x の値と "アドレス" を表示

  f(&x); // x の "アドレス" を渡す

  cout << x << endl; // main と f で共通の変数 x を操作したので値が変わる
}
