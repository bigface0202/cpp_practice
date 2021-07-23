/**
 * @file answer.cpp
 * 3または5で割り切れる正の整数の総和
 * 
 * @author bigface / created on 2021/07/05
 */
#include <stdio.h>
#include <iostream>

using namespace std;

int main( int argc, char *argv[] )
{
    int max;
    int sum = 0;
    cout << "上限値:";
    cin >> max;

    for (int i = 3; i <= max; i++){
      if (i % 3 == 0 || i % 5 == 0){
        sum += i;
      }
    }

    cout << "3または5で割り切れる正の整数の総和は" << sum << "です\n";
}