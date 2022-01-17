#include <iostream>

using namespace std;

// 関数名だけ先に宣言
int square_sum(int n); // k = 1 から n まで k^2 を足し上げる

int main()
{
  int n = 5;
  cout << square_sum(n) << ' ' << n*(n+1)*(2*n+1)/6 << endl;

  n = 10;
  cout << square_sum(n) << ' ' << n*(n+1)*(2*n+1)/6 << endl;
}


int square_sum(int n) {
  int square_sum = 0; // 関数名と同名の変数も定義できる

  for (int k = 1; k <= n; k++) {
    square_sum += k*k;
  }

  return square_sum;
}
