#include <iostream> // 標準入出力ストリーム
#include <fstream> // ファイル入出力ストリーム
#include <sstream> // 文字列ストリーム

using namespace std;

int main()
{
  ifstream ifs("norm_var.dat"); // 読み取り用にファイルを開いて保持するオブジェクト
  string str; // 1行ごとにデータを文字列として保持するための変数を用意
  istringstream iss; // 文字列をストリームに

  while (getline(ifs,str)) { // ファイルデータを1行ごとに str に代入
    
  }
  
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
