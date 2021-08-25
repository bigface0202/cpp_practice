/**
 * @file answer.cpp
 * 
 * テキストファイルから空行を取り除く
 * @author bigface / created on 2021/07/24
 */
#include <stdio.h>
#include <iostream>
#include <string>
#include <fstream>
#include <ostream>
#include <filesystem>

/** 
 * 解答
 * 1. 元のファイルから保持したいテキストだけを含める一時ファイルを作る
 * 2. 入力ファイルから1行ずつ読み込んで、空ではない全ての行を一時ファイルにコピー
 * 3. 処理が終わると基のファイルを削除
 * 4. 一時ファイルを元のファイルのあったパスに移動
*/

namespace fs = std::filesystem;

void remove_empty_lines(fs::path filepath)
{
  // std::ios::inで読み込み専用で開く
  std::ifstream filein(filepath.native(), std::ios::in);
  if (!filein.is_open())
    throw std::runtime_error("Failed to open file.");
  auto temppath = fs::temp_directory_path() / "temp.txt";
  // std::ios::out 出力用にファイルを開く
  // std::ios::trunc 既存のファイルに上書きする
  std::ofstream fileout(temppath.native(), std::ios::out | std::ios::trunc);
  if (!fileout.is_open())
    throw std::runtime_error("Failed to open file.");

  std::string line;
  while (std::getline(filein, line))
  {
    if (line.length() > 0 && line.find_first_not_of(' ') != line.npos)
    {
      fileout << line << '\n';
    }
  }

  filein.close();
  fileout.close();

  fs::remove(filepath);
  fs::rename(temppath, filepath);
}

int main ()
{
  std::cout << "aaa" << std::endl;
  fs::path file_path = "test.txt";
  // remove_empty_lines(file_path);
}

// void extract_brank(std::string file_name)
// {
//   std::fstream ifs(file_name);
//   std::string str;

//   if(ifs.fail()) {
//     throw std::runtime_error("Failed to open file.");
//   }

//   while (getline(ifs, str)) {
//     std::cout << str << std::endl;
//   }
// }

// int main( int argc, char *argv[] )
// {
//   std::string file_name = "/media/yusuke/Moon/GitHub/cpp_practice/The-Modern-C++Challenge/Question34/Main/test.txt";
  
//   extract_brank(file_name);
// }