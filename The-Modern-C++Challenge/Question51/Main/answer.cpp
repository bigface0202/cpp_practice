/**
 * @file answer.cpp
 * 
 * 電話番号のリストの変換
 * @author bigface / created on 2021/10/25
 */
#include <stdio.h>
#include <iostream>
#include <vector>
#include <string>

/** 
 * 解答
 * 電話番号が0で始まる場合も考慮する必要がある。
 * 0を取り除いて、国番号を付与する
*/

bool starts_with(std::string_view str, std::string_view prefix)
{
  return str.find(prefix) == 0;
}

// numbersを参照引数にしているので、returnする必要がない
void normalize_phone_numbers(std::vector<std::string>& numbers, std::string const & countryCode)
{
  std::transform(std::cbegin(numbers), std::cend(numbers), std::begin(numbers),
                [countryCode](std::string const & number){
                  std::string result;
                  if (number.size() > 0)
                  {
                    if (number[0] == '0')
                      result = "+" + countryCode + number.substr(1);
                    else if (starts_with(number, countryCode))
                      result = "+" + number;
                    else if (starts_with(number, "+" + countryCode))
                      result = number;
                    else
                      result = "+" + countryCode + number;
                  }

                  result.erase(
                    std::remove_if(std::begin(result), std::end(result),
                      [](const char ch) {return isspace(ch); }),
                    std::end(result));
                  return result;
                });
}

/** 
 * 1. リストの文字列に対してスペースを取り除く
 * 2. 指定の国番号があるか確認する
 * 3. あれば、+のみ付与する
 * 4. なければ+と国番号を付与する
*/

std::vector<std::string> transform_numbers(std::vector<std::string> numbers, std::string countryCode)
{
  // 結果格納用のvector
  std::vector<std::string> results;
  
  for (auto number : numbers){
    // std::removeでは該当を削除するが、不要な要素が末尾に寄せられただけとなる
    // そこで、removeで該当文字を最後尾に追いやって、毎回eraseで末尾を削除する
    number.erase(std::remove(number.begin(), number.end(), ' '), number.end());
    // 最初に国番号のみが見つかれば+のみ付与
    if (number.find(countryCode) == 0){
      number = "+" + number;
    }
    else if (number[0] == '0'){
      number = "+" + countryCode + number.substr(1);
    }
    // +国番号が見つからなければ、+国番号を付与
    else if (!(number.find("+" + countryCode) == 0)){
      number = "+" + countryCode + number;
    }
    results.push_back(number);
  }

  return results;
}

int main( int argc, char *argv[] )
{
  // 国番号
  std::string countryCode = "44";

  // 電話番号リスト
  std::vector<std::string> numbers{
    "07555 123456",
    "07555123456",
    "+44 7555 123456",
    "44 7555 123456",
    "7555 123456"
    };
  
  // normalize_phone_numbers(numbers, "44");
  
  // for (auto const & number : numbers)
  // {
  //   std::cout << number << std::endl;
  // }

  std::vector<std::string> results = transform_numbers(numbers, countryCode);

  for (auto number : results){
    std::cout << number << std::endl;
  }
}