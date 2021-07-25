/**
 * @file answer.cpp
 * 
 * 与えられた正の整数より小さい最大の素数
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
    unsigned int n;

    cout << "値を入力して下さい:";
    cin >> n;

    for (int i = n; i > 1; i--){
      if(is_prime(i)){
        cout << "最大の素数は" << i <<"です\n";
        return 0;
      }
    }
}