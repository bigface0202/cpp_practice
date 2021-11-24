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

/** 
 * 最高と最低の評価5%を取り除く
 * 平均評価を計算して出力 [done]
*/

struct movie
{
  int id;
  std::string title;
  std::vector<int> ratings;
};

int main( int argc, char *argv[] )
{
  std::vector<movie> movies{
    { 101, "The Matrix", { 10, 9, 10, 9, 9, 8, 7, 10, 5, 9, 9, 8 } },
    { 102, "Gladiator", { 10, 5, 7, 8, 9, 8, 9, 10, 10, 5, 9, 8, 10 } },
    { 103, "Interstellar", { 10, 10, 10, 9, 3, 8, 8, 9, 6, 4, 7, 10 } }
  };

  for (auto const movie : movies)
  {
    double avg = std::accumulate(movie.ratings.begin(), movie.ratings.end(), 0) / static_cast<double>(movie.ratings.size());

    std::cout << "Rating Avg.: " << std::setprecision(2) << avg << std::endl;
  }
}