/**
 * @file answer.cpp
 * 
 * 最長回分部分文字列
 * @author bigface / created on 2021/08/12
 */
#include <stdio.h>
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>
#include <string_view>

/** 
 * 解答
*/
std::string longest_palindrome(std::string_view str)
{
  size_t const len = str.size();
  size_t longestBegin = 0;
  size_t maxLen = 1;
  // 回分部分判定をストアするためのテーブル
  // 一次元配列で定義しているが、二次元配列で考えた方が理解しやすいと思う
  std::vector<bool> table(len * len, false);

  // テーブルの初期化
  // 配列[i, i]は全てTrue
  for (size_t i = 0; i < len; i++) table[i * len + i] = true;
  // まずはiとi+1が同じ文字かどうかを判定する
  for (size_t i = 0; i < len - 1; i++)
  {
    if (str[i] == str[i + 1])
    {
      table[i * len + i + 1] = true;
      if (maxLen < 2)
      {
        longestBegin = i;
        maxLen = 2;
      }
    }
  }
  // 3文字以上の文字列[i, j]に対して、[i + 1, j - 1]がtrueで[i, j]の文字が等しいならtrue
  for (size_t k = 3; k <= len; k++)
  {
    for (size_t i = 0; i < len - k + 1; i++)
    {
      size_t j = i + k - 1;
      if (str[i] == str[j] && table[(i + 1) * len + j - 1])
      {
        table[i * len + j] = true;
        if (maxLen < k)
        {
          longestBegin = i;
          maxLen = k;
        }
      }
    }
  }
  return std::string(str.substr(longestBegin, maxLen));
}

int main()
{
  std::string input = "nowiwon";
  std::string output;

  output = longest_palindrome(input);

  std::cout << output << std::endl;
}

// 回分部分なので部分文字列も見るらしい
// 以下のアルゴリズムでは最初の文字から一致する回分しか探索できない
// template <class Elem>
// using tstring = std::basic_string<Elem, std::char_traits<Elem>, std::allocator<Elem>>;

// template <class Elem>
// using tstringstream = std::basic_stringstream<Elem, std::char_traits<Elem>, std::allocator<Elem>>;

// template <class Elem> 
// tstring<Elem> palindrome(tstring<Elem> & text)
// {
//   text.erase(std::remove(text.begin(), text.end(), ' '), text.end());
//   tstring<Elem> reverse (text.rbegin(), text.rend());
//   tstringstream<Elem> candidate;
//   tstringstream<Elem> result;
  
//   candidate << "";
//   result << "";

//   for(size_t i; i < text.size(); i++)
//   {
//     if (text[i] == reverse[i])
//     {
//       candidate << reverse[i];
//     }
//     else if (text[i] != reverse[i] && !candidate.str().empty())
//     {
//       if (candidate.str().size() > result.str().size())
//       {
//         result.str(candidate.str());
//       }
//       candidate.str("");
//     }
//   }
//   if (candidate.str().size() > result.str().size())
//   {
//     result.str(candidate.str());
//   }
//   return result.str();
// }


// int main( int argc, char *argv[] )
// {
//   std::string input = "noe i won";

//   std::string output = palindrome(input);

//   std::cout << output << std::endl;
// }