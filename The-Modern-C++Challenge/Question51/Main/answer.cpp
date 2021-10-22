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
// 再帰を使う方法
void next_permutation_myself(std::string str, std::string perm)
{
  if (str.empty()) std::cout << perm << std::endl;
  else {
    for (size_t i = 0; i < str.size(); ++i) {
      // substr(1)で1番目以降の全体からなる部分文字列を取得する
      next_permutation_myself(str.substr(1), perm + str[0]);

      // std::rotate(first, middle, last)
      // middleの数だけ文字を左にローテートする
      // 今回の場合は1文字だけ左に回転させる（0番目は最後にいく）
      std::rotate(std::begin(str), std::begin(str) + 1, std::end(str));
    }
  }
}

void print_permutations_recursive(std::string str)
{
  next_permutation_myself(str, "");
}


// 再帰を使わない方法
// 標準ライブラリのnext_permutationを使う
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
  std::string text_ = "kenta";

  print_permutation(text);

  print_permutations_recursive(text_);
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