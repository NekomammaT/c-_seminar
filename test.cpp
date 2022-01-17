#include <iostream>

using namespace std;

void f(double a) {
  a[0][1] *= 2;
}

int main()
{
  double a[3][2] = {{1,2},{3,4},{5,6}};

  cout << a[0][0] << ' ' << a[0][1] << endl;

  f(a);

  cout << a[0][0] << ' ' << a[0][1] << endl;
}
