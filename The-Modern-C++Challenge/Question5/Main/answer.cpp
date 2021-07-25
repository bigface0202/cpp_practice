/**
 * @file answer.cpp
 * セクシー素数
 * 
 * 
 * @author bigface / created on 2021/07/24
 */
#include <stdio.h>
#include <iostream>

using namespace std;

bool is_prime(int const num){
  if(num <= 3){
    return num > 1;
  }
  else if (num % 2 == 0 || num % 3 == 0){
    return false;
  }
  else{
    // 素数は4n+3, 6n+5, 8n+5で無限に存在する
    // ここでは6n+5, 8n+5を用いている
    for (int i = 5; i * i <= num; i += 6){
      if (num % i == 0 || num % (i + 2) == 0){
        return false;
      }
    }
    return true;
  }
}

int main( int argc, char *argv[] )
{
    unsigned int n, tmp;

    cout << "値を入力して下さい:";
    cin >> n;

    // 5の次が7になって、tmpが更新されてしまうため↓は良くない例
    // for (unsigned int i = 2; i <= n; i++){
    //   if(is_prime(i)){
    //     if ((i - tmp) == 6){
    //       cout << i << "と" << i+6 << "はセクシー素数です\n";
    //     }
    //     tmp = i;
    //   }
    // }

    // i とi+6を見ればよい
    for (unsigned int i = 2; i <= n; i++){
      if(is_prime(i) && is_prime(i + 6)){
        cout << i << "と" << i+6 << "はセクシー素数です\n";
      }
    }
}