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

int main( int argc, char *argv[] )
{
  // 電話番号リスト
  std::vector<std::string> numbers{
    "07555 123456",
    "07555123456",
    "+44 7555 123456",
    "44 7555 123456",
    "7555 123456"
    };
  // 結果格納用のvector
  std::vector<std::string> results;
  
  // 
  for (auto number : numbers){
    number.erase(std::remove(number.begin(), number.end(), ' '), number.end());
    results.push_back(number);
  }

  for (auto number : results){
    std::cout << number << std::endl;
  }
  
}