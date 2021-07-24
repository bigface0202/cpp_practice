/**
 * @file answer.cpp
 * 
 * 最大公約数
 * @author bigface / created on 2021/07/24
 */
#include <stdio.h>
#include <iostream>

using namespace std;

// ユークリッドの互除法
unsigned int gcd(const unsigned int a, const unsigned int b)
{
  return (b == 0) ? a : gcd(b, a % b);
}

int main( int argc, char *argv[] )
{
    int i1, i2;
    // int min, max;
    // int gcd = 1; gcd: Greatest common divisor 答えがゼロの場合もあり得る（入力がゼロ）
    int answer;
    cout << "1つ目の正の整数を入力して下さい：";
    cin >> i1;
    cout << "2つ目の正の整数を入力して下さい：";
    cin >> i2;

    answer = gcd(i1, i2);
    /**
     * 再帰関数を使ったほうが簡単に実装できる。
     */ 
    // if (i1 < i2){
    //   max = i2;
    //   min = i1;
    // }else{
    //   max = i1;
    //   min = i2;
    // }

    // for(int i = min; i >= 1; --i){
    //   if (max % i == 0 && min % i == 0){
    //     gcd = i;
    //     break;
    //   }
    // }

    cout << "最大公約数は" << answer << "です。\n";
}