/**
 * @file answer.cpp
 * 
 * 映画の平均評価
 * @author bigface / created on 2021/11/24
 */
#include <stdio.h>
#include <iostream>
#include <vector>
#include <numeric>
#include <iomanip>
#include <algorithm>

/** 
 * 最高と最低の評価5%を取り除く
 * 平均評価を計算して出力 [done]
*/

/** 
 * 解答
 * トリム平均を使う
 * - 列をソートして要素を昇順、または降順に整列する
 * - 両側から必要なパーセント分の要素を取り除く
 * - 残りの要素の総和を計算する
 * - 総和を残りの要素数で割った値を平均値とする
*/

struct movie
{
  int id;
  std::string title;
  std::vector<int> ratings;
};

double truncated_mean(std::vector<int> values, double const percentage)
{
  std::sort(std::begin(values), std::end(values));
  auto remove_count = static_cast<size_t>(values.size() * percentage + 0.5);

  // 頭からremove_count番目まで消す
  values.erase(std::begin(values), std::begin(values) + remove_count);
  // ケツからremove_count番目まで消す
  values.erase(std::end(values) - remove_count, std::end(values));

  auto total = std::accumulate(std::begin(values), std::end(values), 0ULL);

  return static_cast<double>(total) / values.size();
}

void print_movie_ratings(std::vector<movie> const & movies)
{
  for (auto const & m : movies)
  {
    std::cout << m.title 
              << " : "
              << std::fixed 
              << std::setprecision(1)
              << truncated_mean(m.ratings, 0.05) 
              << std::endl;
  }
}

int main( int argc, char *argv[] )
{
  std::vector<movie> movies{
    { 101, "The Matrix", { 10, 9, 10, 9, 9, 8, 7, 10, 5, 9, 9, 8 } },
    { 102, "Gladiator", { 10, 5, 7, 8, 9, 8, 9, 10, 10, 5, 9, 8, 10 } },
    { 103, "Interstellar", { 10, 10, 10, 9, 3, 8, 8, 9, 6, 4, 7, 10 } }
  };

  print_movie_ratings(movies);

  // for (auto const movie : movies)
  // {
  //   double avg = std::accumulate(movie.ratings.begin(), movie.ratings.end(), 0) / static_cast<double>(movie.ratings.size());

  //   std::cout << "Rating Avg.: " << std::setprecision(2) << avg << std::endl;
  // }
}