/**
 * @file answer.cpp
 * 要素列の最頻出要素
 * 
 * @author bigface / created on 2021/10/06
 */
#include <stdio.h>
#include <iostream>
#include <vector>
#include <map>

/** 
 * 解答
 * - 各要素の出現回数をstd::mapに記録する。キーが要素で、値が出現回数
 * - std::max_element()を用いて出現回数最大の要素を求める。結果の型は連想記憶の要素であり、要素と出現回数のペア。
 * - 最大要素の値と等しい値を持つ全マップ要素をコピーして、最終結果として返す。
*/

template <typename T>
std::vector<std::pair<T, size_t>> find_most_frequent(std::vector<T> const & range)
{
  std::map<T, size_t> counts;
  
  // countsというmapを作り、eがkeyで、同じkeyに対してインクリメントしている
  // 配列をインクリメントしてるように見えて若干違和感あるけど、
  // デバッグで中身見ると確かにな、という感じ
  for (auto const & e : range) counts[e]++;

  // std::max_elementで最大値を抽出
  // e1.secondには頻出数が格納されている
  auto maxelem = std::max_element(
    std::cbegin(counts), std::cend(counts),
    [](auto const & e1, auto const & e2){
      return e1.second < e2.second;
    }
  );

  // mapを格納するときはvectorの型にstd::pairを指定する
  std::vector<std::pair<T, size_t>> result;

  // copy_ifは条件を満たす要素のみをコピー
  // max_elementのみでは、一番最初に適合した数値のみを返すので、
  // copy_ifで頻度が等しいものを全て抽出する
  // なので、条件としてkvp.second == maxelem->secondになっている
  std::copy_if(
    std::cbegin(counts), std::cend(counts),
    std::back_inserter(result),
    [maxelem](auto const & kvp) {
      return kvp.second == maxelem->second;
    }
  );

  return result;
}

int main( int argc, char *argv[] )
{
  auto range = std::vector<int>{1, 1, 3, 5, 8, 13, 3, 5, 8, 8, 5};
  auto result = find_most_frequent(range);

  for (auto const & [e, count] : result)
  {
    std::cout << e << ":" << count << std::endl;
  }
}