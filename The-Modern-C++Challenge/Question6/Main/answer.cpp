/**
 * @file answer.cpp
 * 過剰数
 * 
 * @author bigface / created on 2021/07/24
 */
#include <stdio.h>
#include <cmath>
#include <iostream>

using namespace std;

/**
 * 解答
 */

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

void print_abundant(int const limit)
{
  for (int number = 10; number <= limit; ++number)
  {
    if (auto sum = sum_proper_division(number); sum > number)
    {
      cout << number << ", abundance=" << sum - number << endl;
    }
  }
}

int main( int argc, char *argv[] )
{
    // int n, sum = 0;
    int limit = 0;

    cout << "値を入力して下さい:";
    cin >> limit;

    print_abundant(limit);

    // 以下でも計算できるが、iをnまで回す必要は無く、nの平方根まででよい
    // またsumは確実に1が含まれるので、sum=1で始めてよく、iも2からでよい
    // あと、以下の判定は過剰数かどうかの判断で、与えられた数値以下の過剰数全てを出す必要がある
    // for (int i = 1; i < n; i++){
    //   if (n % i == 0){
    //     sum += i;
    //   }
    // }
    // if (n * 2 < sum)
    // {
    //   cout << n << "は過剰数で、過剰は" << sum << "です\n";
    // } else
    // {
    //   cout << n << "は過剰数ではありません。\n";
    // }
}