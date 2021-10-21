/**
 * @file answer.cpp
 * 
 * 文字列の文字の順列を生成
 * @author bigface / created on 2021/10/14
 */
#include <stdio.h>
#include <iostream>
#include <string>
#include <cstring>
#include <algorithm>

/** 
 * 解答
*/
void print_permutation(std::string str)
{
  std::sort(std::begin(str), std::end(str));

  do
  {
    std::cout << str << std::endl;
  } while (std::next_permutation(std::begin(str), std::end(str)));
}

int main(int argc, char *argv[])
{
  std::string text = "yusuke";

  print_permutation(text);
}

// 順列の意味を勘違いしていた、、、
// 以下はただの文字列のソート
/** 
 * 1. 文字列をfor文で回す
 * 2. 文字をバブルソート
*/

// int main( int argc, char *argv[] )
// {
//   std::string text = "yusuke";
//   std::string result = "";

//   for (int i = 0; i < static_cast<int>(text.length()) - 1; i++)
//   {
//     for (int j = text.length() - 1; j > i; j--)
//     {
//       if (text[j] < text[j - 1])
//       {
//         auto tmp = text[j];
//         std::cout << j << "," << j+1 << std::endl;
//         std::cout << tmp << "," << text[j-1] << std::endl;
//         text.replace(j, 1, 1, text[j-1]);
//         std::cout << text << std::endl;
//         text.replace(j-1, 1, 1, tmp);
//         std::cout << text << std::endl;
//       }
//     }
//   }
//   std::cout << text << std::endl;
// }