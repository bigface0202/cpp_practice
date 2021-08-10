/**
 * @file answer.cpp
 * 
 * 指定した区切り文字で文字列を連結する
 * @author bigface / created on 2021/07/24
 */
#include <stdio.h>
#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <iterator>
#include <algorithm>

using namespace std;

/** 
 * 解答
*/
template <typename Iter>
std::string join_strings(Iter begin, Iter end, char const * const separator)
{
  std::ostringstream os;
  // std::copyとstd::ostream_iteratorを組み合わせることで、osにvectorの中身を入力していく
  std::copy(begin, end - 1, std::ostream_iterator<std::string>(os, separator));
  // iteratorのポインタに文字が入っている
  os << *(end - 1);
  return os.str();
}

template <typename C>
std::string join_strings(C const & c, char const * const separator)
{
  if (c.size() == 0) return {};
  return join_strings(c.begin(), c.end(), separator);
}

int main()
{
  std::vector<std::string> input{"this", "is", "an", "example"};
  std::cout << join_strings(input, " ");
}


// 以下も80％くらい正解
// int main( int argc, char *argv[] )
// {
//   vector<string> input{"this", "is", "an", "example"};
//   string delim = " ";
//   std::ostringstream oss;

//   if (input.size() != 0) 
//   {
//     for (auto i : input)
//     {
//       if (i == input.back())
//         oss << i << endl;
//       else
//         oss << i << delim;
//     }
//     cout << oss.str();
//   } else {
//     cout << "";
//   }
// }