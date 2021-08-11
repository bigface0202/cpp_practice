/**
 * @file answer.cpp
 * 
 * 区切り文字集合で文字列をトークンに分割する
 * @author bigface / created on 2021/07/24
 */
#include <stdio.h>
#include <iostream>
#include <string>
#include <vector>
#include <sstream>

/**
 * 解答
 */
// basic_stringは文字型から文字列を作るためのクラステンプレート
// stringはそのクラステンプレートをcharに特化させたもの
// なので、basic_stringを定義しておけばどんな文字型も受けられる
template <class Elem>
using tstring = std::basic_string<Elem, std::char_traits<Elem>, std::allocator<Elem>>;

template <class Elem>
using tstringstream = std::basic_stringstream<Elem, std::char_traits<Elem>, std::allocator<Elem>>;

// delimiterが1つの場合
template<typename Elem>
inline std::vector<tstring<Elem>> split(tstring<Elem> text, Elem const delimiter)
{
  auto sstr = tstringstream<Elem>{ text };
  auto tokens = std::vector<tstring<Elem>>{};
  auto token = tstring<Elem>{};

  while (std::getline(sstr, token, delimiter))
  {
    if (!token.empty()) tokens.push_back(token);
  }
  return tokens;
}

// delimiterが複数の場合
template<typename Elem>
inline std::vector<tstring<Elem>> split(tstring<Elem> text, tstring<Elem> const & delimiters)
{
  auto tokens = std::vector<tstring<Elem>>{};
  size_t pos, prev_pos = 0;
  // find_first_ofは複数の文字列で検索をかけることができる
  // 第二引数は検索開始位置
  while ((pos = text.find_first_of(delimiters, prev_pos)) != tstring<Elem>::npos)
  {
    if (pos > prev_pos)
      token.push_back(text.substr(prev_pos, pos - prev_pos));
    prev_pos = pos + 1;
  }
  if (prev_pos < text.length())
    // nposの場合は、prev_pos番目以降の全体を返す
    tokens.push_back(text.substr(prev_pos, tstring<Elem>::npos));
  return tokens;
}

// 以下でも正解
// std::vector<std::string> split(const std::string &s, std::string delims) 
// {
//   std::vector<std::string> elems;
//   std::string item;
//   // std::getline
//   // ストリームから改行文字が現れるまで（1行すべて）あるいは仮引数delimで指定された文字までの文字列を入力
//   for (auto delim : delims)
//   {
//     if (s.find(delim) != std::string::npos)
//     {
//       // ssをsで初期化
//       std::stringstream ss(s);
//       while (std::getline(ss, item, delim)) {
//         if (!item.empty()) {
//           elems.push_back(item);
//         }
//       }
//     } 
//   }
//   return elems;
// }

// int main( int argc, char *argv[] )
// {
//   std::string input = "this is an example";
//   std::string delims = ",.! ";
//   std::vector<std::string> outputs;

//   outputs = split(input, delims);

//   for (auto output : outputs)
//     std::cout << output << '\n';
// }