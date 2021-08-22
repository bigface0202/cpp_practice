/**
 * @file answer.cpp
 * 
 * パスカルの三角形
 * @author bigface / created on 2021/07/24
 */
#include <stdio.h>
#include <iostream>
#include <cmath>
/** 
 * 解答
*/
unsigned int number_of_digits(unsigned int const i)
{
  return i > 0 ? (int) log10((double) i) + 1 : 1;
}

void print_pascal_triangle(int const n)
{
  for (int i = 0; i < n; i++)
  {
    auto x = 1;
    // std::string(n, '{文字}')で{文字}をn回出力する
    std::cout << std::string((n - i - 1) * (n / 2), ' ');
    for (int j = 0; j <= i; j++)
    {
      auto y = x;
      std::cout << i << ',' << j << std::endl;
      x = x * (i - j) / (j + 1);
      auto maxlen = number_of_digits(x) - 1;
      std::cout << y << std::string(n - 1 - maxlen - n % 2, ' ');
    }
    std::cout << std::endl;
  } 
}

int main()
{
  int n = 0;
  std::cout << "Levels (up to 10):";
  std::cin >> n;
  if (n > 10)
    std::cout << "Value too large" << std::endl;
  else
    print_pascal_triangle(n);

  std::cout << std::string(10, 'a') << std::endl;
}

// 空白が正しくない
// int combi(int n, int k)
// {
//   int tmp1 = 1;
//   for (int i = n; i > n-k; --i ) {
//     tmp1 *= i;
//   }
//   int tmp2 = 1;
//   for (int j = 1; j <= k; ++j ) {
//     tmp2 *= j;
//   }

//   return tmp1 / tmp2;
// }

// long long combi2(long long n, long long k)
// {
//   if (n == k || k == 0)
//     return 1;
//   else
//     return combi2(n - 1, k - 1) + combi2(n - 1, k);
// }

// int main( int argc, char *argv[] )
// {
//   for (int i = 0; i < 11; i++) {
//     for (int j = 0; j <= i; j++) {
//       if (j == 0)
//         std::cout << 1 << ' ';
//       else {
//         std::cout << combi2(i, j) << ' ';
//       }
//     }
//     std::cout << '\n';
//   }
// }