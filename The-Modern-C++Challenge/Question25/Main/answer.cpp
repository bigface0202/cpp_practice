/**
 * @file answer.cpp
 * 
 * 英文タイトルのキャピタライズ
 * @author bigface / created on 2021/08/10
 */
#include <stdio.h>
#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <iterator>

/** 
 * 解答
*/
template <class Elem>
using tstring = std::basic_string<Elem, std::char_traits<Elem>, std::allocator<Elem>>;

template <class Elem>
using tstringstream = std::basic_stringstream<Elem, std::char_traits<Elem>, std::allocator<Elem>>;

template <class Elem>
tstring<Elem> capitalize(tstring<Elem> const & text)
{
  tstringstream<Elem> result;
  bool newWord = true;
  // 1文字ずつfor文回す
  for (auto const ch : text)
  {
    // ispunctは句読点や記号かどうかを判別する
    // isspaceはスペースかどうか
    // スペース、句読点、記号の次の文字はnewWord=trueとなる
    newWord = newWord || std::ispunct(ch) || std::isspace(ch);
    // isalphaはアルファベットかどうか
    if (std::isalpha(ch))
    {
      if (newWord)
      {
        result << static_cast<Elem>(std::toupper(ch));
        newWord = false;
      }
      else
        result << static_cast<Elem>(std::tolower(ch));
    }
    else result << ch;
  }
  return result.str();
}

int main()
{
  using namespace std::string_literals;
  auto output = capitalize("the c++ chalenger"s);

  std::cout << output;
}


// 以下も正解
// std::vector<std::string> split(const std::string &s, char delim) 
// {
//   std::vector<std::string> elems;
//   // ssをsで初期化
//   std::stringstream ss(s);
//   std::string item;
//   // std::getline
//   // ストリームから改行文字が現れるまで（1行すべて）あるいは仮引数delimで指定された文字までの文字列を入力
//   while (std::getline(ss, item, delim)) {
//     if (!item.empty()) {
//       elems.push_back(item);
//     }
//   }
//   return elems;
// }

// int main( int argc, char *argv[] )
// {
//   std::string input = "the c++ challenger";
//   std::vector<std::string> output;
//   std::ostringstream oss;
//   // std::cin >> input;

//   output = split(input, ' ');

//   // for (auto i : output) {
//   //   i[0] = std::toupper(i[0]);
//   //   oss << i << ' ';
//   // }

//   for (size_t i = 0; i < output.size(); i++) {
//     output[i][0] = std::toupper(output[i][0]);
//     if (i == output.size() - 1)
//       oss << output[i];
//     else
//       oss << output[i] << ' ';
//   }

//   std::cout << oss.str();
// }