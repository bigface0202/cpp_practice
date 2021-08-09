/**
 * @file answer.cpp
 * 
 * 文字列からバイナリへの変換
 * @author bigface / created on 2021/07/24
 */
#include <stdio.h>
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <iomanip>
#include <string_view>

/** 
 * 解答
*/
unsigned char hexchar_to_int(char const ch)
{
  // 前にもあったが、'0'のunicodeコードポイントを引くことで文字列から数字に変換する
  // 他も然り
  if (ch >= '0' && ch <= '9') return ch - '0';
  if (ch >= 'A' && ch <= 'F') return ch - 'A' + 10;
  if (ch >= 'a' && ch <= 'f') return ch - 'a' + 10;
  throw std::invalid_argument("Invalid hexadecimal character");
}

std::vector<unsigned char> hexstr_to_bytes(std::string_view str)
{
   std::vector<unsigned char> result;

   for (size_t i = 0; i < str.size(); i += 2) 
   {  
    // 1文字ずつhexchar_to_intに渡している 
    result.push_back(
         (hexchar_to_int(str[i]) << 4) | hexchar_to_int(str[i+1]));
   }

   return result;
}

int main()
{
  std::vector<unsigned char> out1 = hexstr_to_bytes("BAADF00D");
  std::vector<unsigned char> out2 = hexstr_to_bytes("010203040506");

  for (unsigned char i : out1)
    printf("%02X\n", i);
  for (unsigned char i : out2)
    printf("%X\n", i);
  // for (auto i : out2)
  //   std::cout << std::uppercase << std::hex << std::setw(2) << std::setfill('0') << i;
 }

// int main( int argc, char *argv[] )
// {
//   std::string input1 = "BAADFOOD";
//   std::vector<int> output{};

//   int tmp;

//   for (int i = 0; i < input1.size(); i += 2) {
//     std::istringstream(input1.substr(i, 2)) >> std::hex >> std::setw(2) >> tmp;
//     output.push_back(tmp);
//     std::cout << tmp << '\n';    
//   }

//   for (auto j : output)
//     std::cout << j << '\n';
// }