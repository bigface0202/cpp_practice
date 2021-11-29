/**
 * @file answer.cpp
 * 
 * ペア作成アルゴリズム
 * @author bigface / created on 2021/11/26
 */
#include <stdio.h>
#include <iostream>
#include <vector>


int main( int argc, char *argv[] )
{
  std::vector<int> input{1, 1, 3, 5, 8, 13, 21};

  std::size_t size = input.size();

  // 2で割り切れない場合は、最後の1つを消す
  if (size % 2 != 0)
  {
    input.erase(std::end(input) - 1, std::end(input));
  }

  std::vector<std::vector<int>> output;
  std::vector<int> tmp;
  for (int i = 0; i < size; i++) 
  {
    tmp.push_back(input[i]);
    if (i % 2 != 0) {
      output.push_back(tmp);
      tmp = {};
    }
  }
}