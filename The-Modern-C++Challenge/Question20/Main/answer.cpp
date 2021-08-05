/**
 * @file answer.cpp
 * コンテナのany, all, none関数
 * 
 * @author bigface / created on 2021/07/24
 */
#include <stdio.h>
#include <iostream>
#include <iterator>
#include <vector>
#include <cassert>
#include <algorithm>
#include <array>
#include <list>
#include <utility>
#include <memory>

/** 
 * 解答
*/

template<class C, class T>
// ヘルパー関数（以下の関数全てに使われる関数）
bool contains(C const & c, T const & value)
{
  return std::end(c) != std::find(std::begin(c), std::end(c), value);
}

// どれか含まれる
template<class C, class... T>
bool contains_any(C const & c, T &&... value)
{
  return (... || contains(c, value));
}

// 全て含まれる
template<class C, class... T>
bool contains_all(C const & c, T const &&... value)
{
  return (... && contains(c, value));
}

// いずれも含まれない
template<class C, class... T>
bool contains_none(C const & c, T const &&... value)
{
  // std::forwardは右辺値参照の場合は右辺値に、左辺値参照の場合は左辺値にキャストし直す
  return !contains_any(c, std::forward<T>(value)...);
}


int main( int argc, char *argv[] )
{
  std::vector<int> v{1, 2, 3, 4, 5, 6};
  if (contains_any(v, 0, 3, 30))
    std::cout << "一部含まれます。\n";
  else
    std::cout << "含まれません\n";
  
  std::array<int, 6> a{ {1, 2, 3, 4, 5, 6} };
  if (contains_all(a, 1, 3, 5, 6))
    std::cout << "全て含まれます。\n";
  else
    std::cout << "含まれません\n";

  // std::list<int> l{ 1, 2, 3, 4, 5, 6};
  // if (contains_none(l, 0, 6))
  //   std::cout << "0, 6は含まれます\n";
  // else
  //   std::cout << "0, 6は含まれません\n";
  std::cout << std::end(a);
}