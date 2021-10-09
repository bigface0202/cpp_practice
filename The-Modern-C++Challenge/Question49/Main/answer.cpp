/**
 * @file answer.cpp
 * 
 * テキストヒストグラム
 * @author bigface / created on 2021/10/09
 */
#include <stdio.h>
#include <iostream>
#include <map>
#include <string>
#include <numeric>
#include <algorithm>
#include <iomanip>
#include <vector>

/** 
 * 解答
*/
std::map<char, double> analyze_text(std::string_view text)
{
  std::map<char, double> frequencies;
  // 最初にaからzのmapを作る
  for (char ch='a'; ch <= 'z'; ch++)
  {
    frequencies[ch] = 0;
  }

  // 頻出数を記録
  for (auto ch : text)
  {
    if(isalpha(ch))
      frequencies[tolower(ch)]++; 
  }

  // 全文字数の取得
  // 単純にtextの文字数かぞえるだけでもいい？
  // スペースもカウントされるので、スペース除外できればlengthでもいけそう
  auto total = std::accumulate(
    std::cbegin(frequencies), std::cend(frequencies),
    0ULL,
    [](auto const sum, auto const & kvp){
      return sum + static_cast<unsigned long long>(kvp.second);
    }
  );

  // auto total = text.length();
  
  std::cout << total << std::endl;

  // frequenciesに対して、totalで割って100がけしてる
  std::for_each(
    std::begin(frequencies), std::end(frequencies),
    [total](auto & kvp) {
      kvp.second = (100.0 * kvp.second) / static_cast<double>(total);
    }
  );

  return frequencies;
}

int main()
{
  auto result = analyze_text(R"(Lorem ipsum dolar sit amet, consectetur adipiscing elit)");

  // std::fixed 浮動小数点数を固定小数点表記で出力することを指示するマニピュレータ
  for (auto const & [ch, rate] : result)
  {
    std::cout << ch << " : "
    << std::fixed
    << std::setw(5) << std::setfill(' ')
    << std::setprecision(2) << rate << std::endl;
  }
}


// int main( int argc, char *argv[] )
// {
//   std::string text = "abcabc";
//   std::map<char, int> counts;
//   // stringはcharの集合なので、map<char,int>にしないといけない
//   for (auto const & ch : text) counts[ch]++;

//   for (auto const & [ch, count] : counts)
//   {
//     std::cout << ch << ":" << count << std::endl;
//   }
// } 