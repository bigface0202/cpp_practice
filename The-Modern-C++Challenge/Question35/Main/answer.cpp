/**
 * @file answer.cpp
 * 
 * ディレクトリのサイズを計算する
 * @author bigface / created on 2021/08/26
 */
#include <stdio.h>
#include <iostream>
#include <filesystem>
#include <numeric>

/** 
 * 解答
*/

namespace fs = std::filesystem;

// uintmax_tは最大の符号なし整数型
std::uintmax_t get_directory_size(fs::path const & dir, bool const follow_symlinks = false)
{
  auto iterator = fs::recursive_directory_iterator(
    dir,
    follow_symlinks ? fs::directory_options::follow_directory_symlink :
                      fs::directory_options::none
  );

  return std::accumulate(
    fs::begin(iterator), fs::end(iterator),
    0ull, //初期値
    // ラムダ式の第一引数にはこれまでの総和、第二引数には配列要素のオブジェクトが入る
    [](std::uintmax_t const total, fs::directory_entry const & entry) {
      return total + (fs::is_regular_file(entry) ? fs::file_size(entry) : 0);
    }
  );
}

int main()
{
  std::string path = "/media/yusuke/Moon/GitHub/cpp_practice/The-Modern-C++Challenge/Question33";
  std::cout << "Size:" << get_directory_size(path) << std::endl;
}

// void directory_size(fs::path rootpath, unsigned long long & f_size)
// {
//   if(fs::exists(rootpath)) {
//     // for (const fs::directory_entry & x : fs::directory_iterator(rootpath)) {
//     for (fs::directory_iterator dirIte(rootpath); dirIte != fs::directory_iterator(); ++ dirIte) {
//       if (!fs::is_directory(dirIte->path()))
//         std::cout << fs::file_size(dirIte->path()) << std::endl;
//       else
//         directory_size(dirIte->path(), f_size);
//     }
//   }
// }

// int main( int argc, char *argv[] )
// {
//   unsigned long long f_size = 0;
//   directory_size("/media/yusuke/Moon/GitHub/cpp_practice/The-Modern-C++Challenge/Question33", f_size);
//   std::cout << f_size << std::endl;
// }