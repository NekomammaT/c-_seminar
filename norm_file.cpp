#include <iostream> // 標準入出力ストリーム
#include <fstream> // ファイル入出力ストリーム
#include <sstream> // 文字列ストリーム

using namespace std;

int main()
{
  ifstream ifs("norm_var.dat"); // 読み取り用にファイルを開いて保持
  ofstream ofs("norm_result.dat"); // 出力用にファイルを開いて保持
  string str; // 1行ごとにデータを文字列として保持するための変数を用意

  double x, y, z;
  
  while (getline(ifs,str)) { // ファイルデータを1行ごとに str に代入
    istringstream iss(str); // str の中身を入力用ストリームに変換
    iss >> x >> y >> z;

    ofs << x << ' ' << y << ' ' << z << ' '
	<< x*x + y*y + z*z << endl; // 出力ファイルに結果を出力
    cout << x << ' ' << y << ' ' << z << ' '
	 << x*x + y*y + z*z << endl; // 標準出力にも出力
  }
}
