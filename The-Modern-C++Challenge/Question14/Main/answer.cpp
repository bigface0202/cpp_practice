/**
 * @file answer.cpp
 * ISBNの検証
 * 
 * @author bigface / created on 2021/07/24
 */
#include <stdio.h>
#include <string>
#include <iostream>
#include <string_view>
#include <iterator>
#include <algorithm>
#include <numeric>

using namespace std;
/** 
 * 解答
*/
bool validate_isbn_10(std::string_view isbn)
{
  auto valid = false;
  // isdigitで数列かどうかを判断できる
  // all_ofは範囲の全ての要素が条件を満たすか判定する
  if (isbn.size() == 10 && 
      std::all_of(std::begin(isbn), std::end(isbn), isdigit))
  {
    auto w = 10;
    // accumulateは範囲を集計する
    auto sum = std::accumulate(std::begin(isbn), std::end(isbn), 0, [&w](int const total, char const c) {
      return total + w-- * (c - '0');
    });
    valid = !(sum & 11);
  }
  return valid;
}
int main( int argc, char *argv[] )
{
    std::string n;
    std::cout << "ISBN-10の番号を入力して下さい:";
    std::cin >> n;

    if (validate_isbn_10(n))
      std::cout << "ISBN-10です。\n";
    else
      std::cout << "ISBN-10ではありません。\n";
}


// 以下で検証はできるが、数値が入力されている前提になる
// 数列が10桁か？文字が含まれていないか？を検証する必要がある
// int main( int argc, char *argv[] )
// {
//     int num, isbn_sum = 0;
//     std::string n;
//     std::cout << "ISBN-10の番号を入力して下さい:";
//     std::cin >> n;

//     for (int i = 1; i < 11; i++) {
//       num = std::stoi(n.substr(10 - i, 1));
//       isbn_sum += num * i;
//     }

//     if (isbn_sum % 11 == 0)
//       std::cout << "ISBN-10です。\n";
//     else
//       std::cout << "ISBN-10ではありません。\n";
// }