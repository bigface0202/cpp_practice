/**
 * @file answer.cpp
 * 
 * 電話番号のリストをフィルタリング
 * @author bigface / created on 2021/10/12
 */
#include <stdio.h>
#include <iostream>
#include <vector>
#include <algorithm>
#include <regex>

/** 
 * 解答
*/
bool starts_with(std::string_view str, std::string_view prefix)
{
  return str.find(prefix) == 0;
}


// 正規表現を用いたフィルタリング
// int main( int argc, char *argv[] )
// {
//   std::string country_code = "81";
//   std::vector<std::string> phone_list = {"090-9449-5202", "+81-0778-42-1081", "81-0778-43-1081"};

//   std::vector<std::string> phone_filtered;

//   for (auto phone_num : phone_list)
//   {
//     auto match = std::smatch{};
//     std::regex_match(phone_num, match, std::regex(R"((\+\d{2,3}|\d{2,3})-(\d{3,4})-(\d{2,4})-(\d{3,4}))"));
//     // auto found = std::find(country_list.begin(), country_list.end(), match[1].str());

//     // if (found != country_list.end())
//     if (country_code == match[1].str() || "+" + country_code == match[1].str())
//     {
//       phone_filtered.push_back(phone_num);
//       std::cout << phone_num << std::endl;
//     }
//   }
// }