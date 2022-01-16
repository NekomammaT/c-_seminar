#include <iostream>

using namespace std;

int main()
{
  cout << "(x, y, z) = ?" << endl;

  double x, y, z;
  cin >> x >> y >> z;

  /*
  cin >> x;
  cin >> y;
  cin >> z; // でも OK
  */

  cout << "x = " << x << ", y = " << y << ", z = " << z << endl;
  cout << "x^2 + y^2 + z^2 = " << x*x + y*y + z*z << endl;
}
