/**
 * @file answer.cpp
 * πの計算
 * 全然わからんかった
 * @author bigface / created on 2021/07/24
 */
#include <stdio.h>
#include <iostream>
#include <random>
#include <algorithm>
#include <iterator>
#include <array>
#include <functional>

using namespace std;

/** 
 * 解答
*/

// mt19937は疑似乱数の種類, uniform_real_distributionは浮動小数点の一様分布乱数
template <typename E = std::mt19937, typename D = std::uniform_real_distribution<>>

double compute_pi(E& engine, D& dist, int const samples = 1000000)
{
  auto hit = 0;
  for (auto i = 0; i < samples; i++)
  {
    auto x = dist(engine);
    auto y = dist(engine);

    // hitは円の中、samplesは円を囲む正方形の中
    // 円の半径を1と仮定して、x^2 + y^2 <= 1であれば円の中となる。
    // 以下は式変形してyの値で比較している
    if (y <= std::sqrt(1 - std::pow(x, 2))) hit++;
  }

  return 4.0 * hit / samples;
}


int main( int argc, char *argv[] )
{
  std::random_device rd;
  // 擬似乱数生成器の状態シーケンスのサイズ分、
  // シードを用意する
  auto seed_data = std::array<int, std::mt19937::state_size> {};

  // generateではseed_dataにrdの値を代入する
  std::generate(std::begin(seed_data), std::end(seed_data), std::ref(rd));

  // 疑似乱数を生成するためのシード列seed_seq, 疑似乱数を複数のシードで初期化するために使用する
  std::seed_seq seq(std::begin(seed_data), std::end(seed_data));

  // 擬似乱数生成器をシード列で初期化
  auto eng = std::mt19937{ seq };

   // 0以上1未満の値を等確率で発生させる
  auto dist = std::uniform_real_distribution<>{0, 1};

  for (auto j = 0; j < 10; j++)
  {
    std::cout << compute_pi(eng, dist) << std::endl;
  }
}