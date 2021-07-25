/**
 * @file answer.cpp
 * 
 * 友愛数
 * @author bigface / created on 2021/07/24
 */
#include <stdio.h>
#include <cmath>
#include <iostream>

using namespace std;

int sum_proper_division(int const number)
{
  int result = 1;
  int const root = static_cast<int>(std::sqrt(number));
  
  for (int i = 2; i <= root; i++)
  {
    if (number % i == 0){
      result += ( (i == (number / i)) ? i : i + number / i );
    }
  }
  return result;
}

/**
 * 解答
 */

void print_amicables(int const limit)
{
  for (int number = 4; number < limit; ++number)
  {
    if (auto sum1 = sum_proper_division(number); sum1 < limit)
    {
      if (auto sum2 = sum_proper_division(sum1); sum2 == number && number != sum1){
        cout << number << "と" << sum1 << "は友愛数です\n";
        number = sum1;
      }
    }
  }
}

// 以下の手法に、約数の和がlimit以下かどうかの判別を加える必要がある
int main( int argc, char *argv[] )
{
  // for (int i = 220; i <= 1000000; i++){
  //   int res = sum_proper_division(i);
  //   if (auto res_i = sum_proper_division(res); i == res_i && i != res){
  //     cout << i << "と" << res << "は友愛数です\n";
  //     i = res;
  //   }
  // }
  print_amicables(1000000);   
}