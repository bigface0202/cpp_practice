/**
 * @file answer.cpp
 * 
 * ナンバープレートの検証
 * @author bigface / created on 2021/08/15
 */
#include <stdio.h>
#include <iostream>
#include <string>
#include <regex>
#include <vector>

/** 
 * 解答（全部正規表現でいけるみたい、、、）
*/
// ライセンスのフォーマットが正しいかどうか
bool validate_license_plate_format(std::string const & str)
{
  std:: regex rx(R"([A-Z]{3}-[A-Z]{2} \d{3,4})");
  return std::regex_match(str, rx);
}
// ライセンスのフォーマットに沿った文字列を抽出
std::vector<std::string> extract_license_plate(std::string const & str)
{
  std::regex rx(R"(([A-Z]{3}-[A-Z]{2} \d{3,4})*)");
  
  std::smatch match;
  std::vector<std::string> results;
  // sregex_iteratorの終端はsregex_iteratorオブジェクトをデフォルトコンストラクタにより構築した場合にも生成される
  // ので、sregex_iterator()で終端であるか否かを判別できる
  for (auto i = std::sregex_iterator(std::begin(str), std::end(str), rx); i != std::sregex_iterator(); ++i) {
    // (*i)はmatch_resultsで正規表現によるマッチ結果を格納するコンテナ
    // if文なくてもいいのでは？
    if ((*i)[1].matched) {
      results.push_back(i->str());
    }
  }

  return results;
}

int main()
{
  std::vector<std::string> output;
  std::string text("AAA-AA 123abceddfga ABC-DE 222 aawafa");
  output = extract_license_plate(text);
  for (auto i : output) {
    std::cout << i << '\n';
  }
}

// bool is_numberplate(std::string & noplate)
// { 
//   // アルファベットを取り出す1
//   std::string alpha = noplate.substr(0, 6);
//   // ハイフンを消す
//   alpha.erase(3);
//   // 文字列の長さを確認
//   if (noplate.length() == 10) {
//     std::string number = noplate.substr(7, 10);
//   } else {
//     std::string number = noplate.substr(7, 11);
//   }
//   // フォーマットチェック
//   std::regex format1 (R"(\w{3}-\w{2} \d{3})");
//   std::regex format2 (R"(\w{3}-\w{2} \d{4})");
//   if (!std::regex_match(noplate, format1) || !std::regex_match(noplate, format1)) {
//     std::cout << "フォーマットが正しくありません" << std::endl;
//     return false;
//   }

//   for (auto c : alpha)
//   {
//     if (!(std::isupper(c) && std::isalpha(c))) {
//       std::cout << "文字のフォーマットが正しくありません" << std::endl;
//       return false;
//     }
//   }

//   return true;
// }

// int main( int argc, char *argv[] )
// {
//   std::string input = "ABC-DE 123";
//   bool noplate = is_numberplate(input);
//   if (noplate)
//     std::cout << "ナンバープレートです" << std::endl;
//   else
//     std::cout << "ナンバープレートではありません" << std::endl;
// }