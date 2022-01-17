#include <iostream>

using namespace std;

void f(double x) {
  cout << x << endl;
  x *= 5;
  cout << x << endl;
}

int main()
{
  double x = 2;
  cout << x << endl;
  f(x); // f の中で x を 5 倍しても外の x は変わらない
  cout << x << endl;
}
