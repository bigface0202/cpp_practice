/**
 * @file answer.cpp
 * 
 * バイナリから文字列への変換
 * @author bigface / created on 2021/07/24
 */
#include <stdio.h>
#include <iostream>
#include <vector>
#include <iomanip>
#include <iterator>
#include <array>

/** 
 * 解答
*/
template <typename Iter>
std::string bytes_to_hexstr(Iter begin, Iter end, bool const uppercase = false)
{
  // 文字列ストリームを使って、文字列へ書き込みを行う
  std::ostringstream oss;
  if (uppercase) oss.setf(std::ios_base::uppercase);
  for (; begin != end; ++begin) {
    // <<演算子でossにデータを流し込む
    oss << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(*begin);
  }
  // 最終的にstrメンバ関数を呼び出すと、完成した文字列をbasic_string型で受け取れる
  return oss.str();
}

template <typename C>
std::string bytes_to_hexstr(C const & c, bool const uppercase = false)
{
  return bytes_to_hexstr(std::begin(c), std::end(c), uppercase);
}

int main()
{
  std::vector<int> input1{ 0xBA, 0xAD, 0xF0, 0x0D };
  std::array<unsigned char, 6> input2{ 1, 2, 3, 4, 5, 6 };
  // arrayは以下の様な初期化の書き方をしなくてもよい
  // std::array<unsigned char, 6> input2{{ 1, 2, 3, 4, 5, 6 }};
  unsigned char buf[5] = { 0x11, 0x22, 0x33, 0x44, 0x55 };

  std::cout << bytes_to_hexstr(input1, true) << std::endl;
  std::cout << bytes_to_hexstr(input2) << std::endl;
  std::cout << bytes_to_hexstr(buf) << std::endl;

  // std::vectorのみ以下の表現ができる
  // for (auto i : input1)
  // {
  //   std::cout <<  i;
  // }
}

// int main( int argc, char *argv[] )
// {
//   std::vector<int> input1 = { 0xBA, 0xAD, 0xF0, 0x0D };
//   std::vector<int> input2 = { 1, 2, 3, 4, 5, 6 };
//   for (auto i : input1)
//   {
//     std::cout << std::hex << std::setw(2) << std::setfill('0') << i;
//   }

//   std::cout << std::endl;

//   for (auto i : input2)
//   {
//     std::cout << std::hex << std::setw(2) << std::setfill('0') << i;
//   }

//   std::cout << std::endl;
// }