/**
 * @file answer.cpp
 * 
 * URLパーツの抽出
 * @author bigface / created on 2021/07/24
 */
#include <stdio.h>
#include <iostream>
#include <string>
#include <regex>
#include <vector>
#include <optional>

/** 
 * 解答
*/
// URLをパースした結果を返すのに以下の構造体を使う
struct uri_parts
{
  std::string protocol;
  std::string domain;
  std::optional<int> port;
  std::optional<std::string> path;
  std::optional<std::string> query;
  std::optional<std::string> fragment;
};

std::optional<uri_parts> parse_uri(std::string uri)
{
  // ^(\w+) 文字(アルファベット)が行の先頭にあり、1回以上繰り返す場合マッチ、コロンまでを調べる
  // \ 直後の正規表現記号をエスケープ、スラッシュをエスケープしている
  // 
  std::regex rx(
    R"(^(\w+):\/\/([\w.-]+)(:(\d+))?)"
    R"(([\w\/\.]+)?(\?([\w=&]*)(#?(\w+))?)?$)"
  );
  auto matches = std::smatch{};
  if (std::regex_match(uri, matches, rx))
  {
    if (matches[1].matched && matches[2].matched)
    {
      uri_parts parts;
      parts.protocol = matches[1].str();
      parts.domain = matches[2].str();
      if (matches[4].matched)
        parts.port = std::stoi(matches[4]);
      if (matches[5].matched)
        parts.path = matches[5];
      if (matches[7].matched)
        parts.query = matches[7];
      if (matches[9].matched)
        parts.fragment = matches[9];
      return parts;
    }
  }
  return {};
}


int main()
{
  auto p1 = parse_uri("https://packt.com");
  std::cout << p1->protocol << '\n';
  std::cout << p1->domain << '\n';
  // std::cout << p1->port << '\n';
  // std::cout << p1->path << '\n';
  // std::cout << p1->query << '\n';
  // std::cout << p1->fragment << '\n';
}

// std::vector<std::string> extract_url_part(std::string const & str)
// {
//   // 文字数は{3,6}の様に指定することで3〜6文字になる
//   std::regex protocol(R"(([a-z]{3,6}):)");

//   std::smatch match;
//   std::vector<std::string> results;

//   for(auto i = std::sregex_iterator(std::begin(str), std::end(str), protocol); i != std::sregex_iterator(); ++i)
//   {
//     results.push_back(i->str());
//   }

//   return results;
// }

// int main( int argc, char *argv[] )
// {
//   std::string input = "https://google.com";
//   std::vector<std::string> output;

//   output = extract_url_part(input);

//   for (auto i : output) {
//     std::cout << i << '\n';
//   }
// }