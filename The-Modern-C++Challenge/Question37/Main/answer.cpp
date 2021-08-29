/**
 * @file answer.cpp
 * 
 * ディレクトリ内で正規表現にマッチするファイルを見つける
 * @author bigface / created on 2021/07/24
 */
#include <stdio.h>
#include <iostream>
#include <filesystem>
#include <regex>
#include <vector>

namespace fs = std::filesystem;

std::vector<fs::directory_entry> find_files(fs::path const & path, std::string const & regex)
{
  std::vector<fs::directory_entry> result;
  std::regex rx(regex.c_str());

  // copy_ifは条件を満たす要素のみをコピーする
  std::copy_if(
    fs::recursive_directory_iterator(path),
    fs::recursive_directory_iterator(),
    std::back_inserter(result),
    [&rx](fs::directory_entry const & entry) {
      // filename()をつければ、filenameのみ返ってくる
      return fs::is_regular_file(entry.path()) && std::regex_match(entry.path().filename().string(), rx);
    }
  );

  for (auto const & entry : result)
  {
    std::cout << entry.path().string() << std::endl;
  }
  
  return result;
}

int main()
{
  auto fpath = "/media/yusuke/Moon/GitHub/cpp_practice/The-Modern-C++Challenge/Question37/test";
  std::string rx = R"(^(?=.*(\d)_(\d).txt).*$)";
  std::vector<fs::directory_entry> files = find_files(fpath, rx);
}

// 下記でも正解
// std::vector<std::string> find_files(fs::path const & fpath, std::regex rx)
// {
//   std::vector<std::string> files = {};
//   try {
//     if (fs::exists(fpath))
//     {
//       for (const fs::directory_entry& entry : fs::recursive_directory_iterator(fpath))
//       {
//         if (std::regex_match(entry.path().string(), rx))
//         { 
//           files.push_back(entry.path().string());
//         }
//       }
//     }
//   }
//   catch (std::exception const & ex)
//   {
//     std::cerr << ex.what() << std::endl;
//   }

//   for (auto file : files) {
//     std::cout << file << std::endl;
//   }
//   return files;
// }

// int main( int argc, char *argv[] )
// {
//   // fpathはfs::pathで渡すとセグフォる（？）
//   auto fpath = "/media/yusuke/Moon/GitHub/cpp_practice/The-Modern-C++Challenge/Question37/test";
//   std::regex rx = std::regex{ R"(^(?=.*(\d)_(\d).txt).*$)" };
//   std::vector<std::string> files = find_files(fpath, rx);
// }