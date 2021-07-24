/**
 * @file answer.cpp
 * 最小公倍数
 * 
 * @author bigface / created on 2021/07/24
 */
#include <stdio.h>
#include <iostream>

using namespace std;

// ユークリッドの互除法
// ユークリッドの互除法を用いて最小公約数を求め、
// 2つの数の積を最小公約数で割ると最小公倍数が算出できる。
unsigned int gcd(const unsigned int a, const unsigned int b)
{
  return (b == 0) ? a : gcd(b, a % b);
}

// 関数の中で計算してしまう
unsigned int lcm(const unsigned int a, const unsigned int b)
{
  int gcd_ans = (b == 0) ? a : gcd(b, a % b);

  return gcd_ans ? (a * b / gcd_ans) : 0;
}

int main( int argc, char *argv[] )
{
    int i1, i2;
    // int gcd_num, answer;
    int answer;
    cout << "1つ目の正の整数を入力して下さい：";
    cin >> i1;
    cout << "2つ目の正の整数を入力して下さい：";
    cin >> i2;

    // gcd_num = gcd(i1, i2);

    // answer = i1 * i2 / gcd_num;
    answer = lcm(i1, i2);

    cout << "最小公倍数は" << answer << "です\n";
}