/**
 * @file answer.cpp
 * 
 * 文字列の日付を変換する
 * @author bigface / created on 2021/08/20
 */
#include <stdio.h>
#include <iostream>
#include <string>
#include <regex>

/** 
 * 解答
*/
// std::regex_replace()を使えば正規表現でテキスト変換が出来る
std::string transform_date(std::string const & text)
{
  auto rx = std::regex{ R"((\d{2})(\.|-)(\d{2})(\.|-)(\d{4}))" };
  // regex_replaceを使えば一致した箇所のみ変換することができる
  return std::regex_replace(text.c_str(), rx, "$5-$3-$1");
}

int main()
{
  auto output = transform_date("my birthday is 02.02.1993");
  std::cout << output << std::endl;
}


// ほぼほぼ正解
// std::string convert_datetime(std::string date)
// {
//   std::regex rx(R"(^([\d]{2})(\.|-)([\d]{2})(\.|-)([\d]{4}))");
//   auto matches = std::smatch{};
//   std::ostringstream oss;

//   if (std::regex_match(date, matches, rx))
//   {
//     if (matches[1].matched && matches[2].matched)
//     {
//       oss << matches[5] << "-" << matches[3] << "-" << matches[1]; 
//     }
//   }

//   return oss.str();
// }

// int main( int argc, char *argv[] )
// {
//   std::string input = "02.02.1993";
//   auto output = convert_datetime(input);

//   std::cout << output << std::endl;
// }