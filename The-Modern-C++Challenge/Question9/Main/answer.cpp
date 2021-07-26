/**
 * @file answer.cpp
 * 素因数分解
 * 
 * @author bigface / created on 2021/07/24
 */
#include <stdio.h>
#include <iostream>
#include <vector>
#include <cmath>
#include <iterator>
#include <algorithm>

using namespace std;

/** 
 * 解答
*/

std::vector<unsigned long long> prime_factors(unsigned long long n)
{
  // 2で割り切れるだけ割り切る
  std::vector<unsigned long long> factors;
  while (n % 2 == 0)
  {
    factors.push_back(2);
    n = n / 2;
  }

  // 3以降の奇数で割り切れる数を探す
  // ループの回数はnの平方根
  int const root = static_cast<int>(std::sqrt(n));
  for (unsigned long long i = 3; i <= root; i += 2)
  {
    while (n % i == 0)
    {
      factors.push_back(i);
      n = n / i;
    }
  }

  // nが2より大きなままなら、nは素数
  if (n > 2)
  {
    factors.push_back(n);
  }

  return factors;
}

int main( int argc, char *argv[] )
{
  unsigned long long number = 0;
  cout << "number:";
  cin >> number;

  auto factors = prime_factors(number);

  std::copy(
    factors.begin(), factors.end(),
    std::ostream_iterator<unsigned long long>(std::cout, " ")
  );
}

// 以下でも正解

// 素数判定の問題から借用
// bool is_prime(int const num){
//   if(num <= 3){
//     return num > 1;
//   }
//   else if (num % 2 == 0 || num % 3 == 0){
//     return false;
//   }
//   else{
//     for (int i = 5; i * i <= num; i += 6){
//       if (num % i == 0 || num % (i + 2) == 0){
//         return false;
//       }
//     }
//     return true;
//   }
// }

// int main( int argc, char *argv[] )
// {
//   int n;
//   int i = 2;

//   cout << "数値を入力して下さい：";
//   cin >> n;

//   while ( i <= n )
//   {
//     if (is_prime(n))
//     {
//       cout << n << '\n';
//       break;
//     }

//     if (n % i == 0)
//     {
//       cout << i << '\n';
//       n = n / i;
//     } else
//     {
//       i++;
//     }
//   }
//   cout << "Done\n"; 
// }