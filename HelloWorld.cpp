#include <iostream> // 標準データ入出力ライブラリ

int main() // プログラム実行時に起動される関数
{
  std::cout << "Hello World!" << std::endl;
  // 標準出力 (ターミナル) に "Hello World!" を流し込む。endl で実際に表示させて改行

  std::cout << "Hello" << " " << "World!" << std::endl;
  // "Hello" と " " と "World!" を順番に流し込む

  std::cout << "Hello";
  std::cout << " ";
  std::cout << "World!";
  std::cout << std::endl;
  // これでも OK
}
