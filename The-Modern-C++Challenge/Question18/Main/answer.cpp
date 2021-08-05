/**
 * @file answer.cpp
 * 
 * 任意個数の引数を取る最小値関数
 * @author bigface / created on 2021/07/24
 */
#include <stdio.h>
#include <iostream>

/** 
 * 解答
*/

// 可変引数テンプレートを使う
template <typename T>
T minimum(T const a, T const b) { return a < b ? a : b; }

// コンパイル時再帰
template <typename T1, typename... T>
T1 minimum(T1 a, T... args)
{
  return minimum(a, minimum(args...));
}

// 2項比較関数使うには、↑のオーバーロードでは実装できない
// 新たに関数を定義する必要がある
template <class Compare, typename T>
T minimumc(Compare comp, T const a, T const b)
{ return comp(a, b) ? a : b; }

template <class Compare, typename T1, typename... T>
T1 minimumc(Compare comp, T1 a, T... args)
{
  return minimumc(comp, a, minimumc(comp, args...));
}

int main()
{
  auto x = minimum(5, 2, 1, 9, 2);
  std::cout << "最小値は" << x << "です\n";

  auto y = minimumc(std::less<>(), 5, 2, 1, 9, 2);
  std::cout << "最小値は" << y << "です\n";
}

// template <class Type>
// Type minof(const Type x[])
// {
//   const int arr_size = sizeof(x) / sizeof(x[0]);
//   Type min = x[0];
  
//   for (int i = 1; i < arr_size; i++)
//     if (min > x[i])
//       min = x[i];
//   return min;
// }

// int main( int argc, char *argv[] )
// {
//   const int array[5] = {2, 1, 0, 5, 6};

//   std::cout << "最小値は" << minof(array) << "です。\n";
// }