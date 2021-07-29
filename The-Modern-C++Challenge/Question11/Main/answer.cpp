/**
 * @file answer.cpp
 * ローマ数字に変換
 * 
 * @author bigface / created on 2021/07/24
 */
#include <stdio.h>
#include <iostream>
#include <vector>
#include <utility>

using namespace std;

/** 
 * 解答
*/

std::string to_roman(unsigned int value)
{
  std::vector<std::pair<unsigned int, char const*>> const roman
  {
    {1000, "M"}, {900, "CM"}, {500, "D"}, {400, "CD"},
    {100, "C"}, {90, "XC"}, {50, "L"}, {40, "XL"},
    {10, "X"}, {9, "IX"}, {5, "V"}, {4, "IV"}, {1, "I"}
  };

  std::string result;
  // pythonのzipみたいな表現
  for (auto const & [num, str] : roman) {
    while (value >= num) {
      result += str;
      value -= num;
    }
  }
  return result;
}


// 以下でも正解
int main( int argc, char *argv[] )
{
  int n;

  cout << "数値を入力：";
  cin >> n;

  string roman = to_roman(n);
  cout << "ローマ数字：" << roman;

  // string singles[9] = {"I", "II", "III", "IV", "V", "VI", "VII", "VIII", "IX"};
  // string doubles[9] = {"X", "XX", "XXX", "XL", "L", "LX", "LXX", "LXXX", "XC"};
  // string triples[9] = {"C", "CC", "CCC", "CD", "D", "DC", "DCC", "DCCC", "CM"};

  // cout << "ローマ数字：";
  // while (n > 1000){
  //   cout << "M";
  //   n -= 1000;
  // }

  // if (n >= 100 && n < 1000){
  //   int t = n / 100;
  //   cout << triples[t - 1];
  //   n -= t * 100;
  // }

  // if (n >= 10 && n < 100){
  //   int d = n / 10;
  //   cout << doubles[d - 1];
  //   n -= d * 10;
  // }
  
  // if (n > 0 && n < 10){
  //   cout << singles[n - 1] << '\n';
  // }
  
}