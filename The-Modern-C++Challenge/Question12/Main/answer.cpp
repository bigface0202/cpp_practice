/**
 * @file answer.cpp
 * 最長コラッツ数列
 * 
 * @author bigface / created on 2021/07/24
 */
#include <stdio.h>
#include <iostream>
#include <utility>
#include <vector>

using namespace std;

/** 
 * 解答
 * 値nから出発した現在の数列の項がnより小さくなったら、
 * そのコラッツ数列の長さは既に求まっているはずなので、
 * キャッシュからその値を取り出して現在の長さに加えることで高速化を試みる
 * 
*/

std::pair<unsigned long long, long> longest_collatz(unsigned long long const limit)
{
  long length = 0;
  unsigned long long number = 0;

  // limit+1の配列を作り、全て0で初期化する
  std::vector<int> cache(limit + 1, 0);

  for (unsigned long long i = 2; i <= limit; i++) {
    auto n = i;
    long steps = 0;
    while (n != 1 && n >= i)
    {
      if ((n % 2) == 0)
        n /= 2;
      else
        n = n * 3 + 1;
      steps++;
    }
    cache[i] = steps + cache[n];

    if (cache[i] > length)
    {
      length = cache[i];
      number = i;
    }
  }

  return std::make_pair(number, length);
}

int main( int argc, char *argv[] )
{ 
  int x;
  cout << "値を入力：";
  cin >> x;

  auto answer = longest_collatz(x);
  cout << x << "の最長コラッツ数列は" << answer.first << "で長さは" << answer.second << endl;

  // for (int i = 1; i < 10; i++) {
  //   auto n = i;
  //   while (n != 1) {
  //     if (n % 2 == 0) {
  //       n = n / 2;
  //     } else {
  //       n = 3 * n + 1;
  //     }
  //     cout << n << ' ';
  //   }
  //   cout << '\n';
  // }
}