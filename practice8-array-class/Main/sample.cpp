/**
 * @file sample.cpp
 *
 * @author bigface / created on 2021/07/05
 */
#include <iostream>
#include <iomanip>

#include "Include/IntArray.h"

using namespace std;

/** 要素数sizeの配列にnum個のデータを代入して表示 */
void f(int size, int num)
{
  try {
    IntArray x(size);
    for (int i = 0; i < num; i++){
      x[i] = i;
      cout << "x[" << i << "] = " << x[i] << '\n';
    }
  }
  
  catch (IntArray::IdxRngErr& x){
    cout << "添字オーバーフロー: " << x.index() << '\n';
    return;
  }
  
  catch (bad_alloc) {
    cout << "メモリの確保に失敗しました \n";
    exit(1);
  }
}

int main( int argc, char *argv[] )
{
  int size, num;

  cout << "要素数:";
  cin >> size;

  cout << "データ数:";
  cin >> num;

  f(size, num);

  cout << "main関数終了\n";
}