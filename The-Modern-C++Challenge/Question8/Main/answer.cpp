/**
 * @file answer.cpp
 * アームストロング数
 * 
 * @author bigface / created on 2021/07/24
 */
#include <stdio.h>
#include <iostream>
#include <cmath>

using namespace std;

/** 
 * 解答
*/
void print_narcissistics()
{
  for (auto a = 1; a <= 9; a++)
  {
    for (auto b = 0; b <= 9; b++)
    {
      for(auto c = 0; c <= 9; c++)
      {
        auto abc = a * 100 + b * 10 + c;
        auto arm = a * a * a + b * b * b + c * c * c;
        if ( abc == arm )
        {
          cout << abc << "はナルシシスト数です\n";
        }  
      }
    }
  }
}


// 以下でも正解。
// 追記：と思ったら、アームストロング数を勘違いしていた
// 追記：n桁の数の各n乗の和なので、3乗のみを考慮すれば良い
// 但し、除算や剰余演算より乗算の方が速い
int main( int argc, char *argv[] )
{
  // for (int i = 100; i < 1000; i++){
  //   int num_hud = i / 100;
  //   int num_ten = (i - 100 * num_hud) / 10;
  //   int num_one = i - 100 * num_hud - 10 * num_ten;
  /** 
   * ↓のfor文要らない
  */
  //   for (int j = 0; j < 5; j++){
  //     if(auto sum = pow(num_hud, j) + pow(num_ten, j) + pow(num_one, j); sum == i){
  //       cout << sum << "はナルシシスト数です\n";
  //     }
  //   }
  // }
  print_narcissistics();
}