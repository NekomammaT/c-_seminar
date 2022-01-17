#include <iostream>

using namespace std;

void f(double &x) { // ポインタを通じて "x" そのものを受け取る
  cout << x << ' ' << &x << endl;
  x *= 5;
  cout << x << endl;
}

int main()
{
  double x = 2;
  cout << x << ' ' << &x << endl;

  f(x);

  cout << x << endl;
}
