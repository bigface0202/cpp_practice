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
  // findは見つかれば、その位置を返す
  return str.find(prefix) == 0;
}

template <typename InputIt>
std::vector<std::string> filter_numbers(InputIt begin, InputIt end, std::string const & countryCode)
{
  std::vector<std::string> result;
  // back_inserterはback_insert_iteratorのヘルパ関数
  // back_insert_iteratorは出力イテレータであり、代入の際にコンテナのpush_back()メンバ関数を呼び出すイテレータアダプタ
  std::copy_if(
    begin, end,
    std::back_inserter(result),
    [countryCode](auto const & number) {
      return starts_with(number, countryCode) || starts_with(number, "+" + countryCode);
    }
  );
  return result;
}

// filter_numbersのWrapper
std::vector<std::string> filter_numbers(std::vector<std::string> const & numbers, std::string const & countryCode)
{
  return filter_numbers(std::cbegin(numbers), std::cend(numbers), countryCode);
}

int main()
{
  std::vector<std::string> numbers{
    "+4074909080",
    "44 7520 112233",
    "+44 7555 123456",
    "40 7200 123456",
    "4412345665",
    "7555 123456"
  };

  auto result = filter_numbers(numbers, "44");

  for (auto const & number : result)
  {
    std::cout << number << std::endl;
  }
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