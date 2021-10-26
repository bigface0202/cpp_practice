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
    if (number.find(countryCode) == 0){
      number = "+" + number;
    }
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
  
  std::vector<std::string> results = transform_numbers(numbers, countryCode);

  for (auto number : results){
    std::cout << number << std::endl;
  }
}