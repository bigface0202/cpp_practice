/**
 * @file answer.cpp
 * 
 * グレイコード
 * @author bigface / created on 2021/07/24
 */
#include <stdio.h>
#include <bitset>
#include <iostream>

using namespace std;

/** 
 * 解答
*/

unsigned int gray_encode(unsigned int const num)
{
  // ^は排他的論理和
  return num ^ (num >> 1);
}

unsigned int gray_decode(unsigned int gray)
{
  for (unsigned int bit = 1U << 31; bit > 1; bit >>= 1)
  {
    if (gray & bit) gray ^= bit >> 1;
  }
  return gray;
}

std::string to_binary(unsigned int const value, int const digits)
{
  // substrは第一引数が開始位置、第二引数が取り出す長さ
  return std::bitset<32>(value).to_string().substr(32 - digits, digits);
}

int main()
{
  std::cout << "Number\tBinary\tGray\tDecoded" << std::endl;
  std::cout << "------\t------\t----\t-------" << std::endl;

  for (unsigned int n = 0; n < 32; ++n)
  {
    auto encg = gray_encode(n);
    auto decg = gray_decode(encg);

    // 二進数もグレイコードもフォーマットは同じなので、to_binaryで表現できる
    std::cout << n << "\t" << to_binary(n, 5) << "\t" << to_binary(encg, 5) << "\t" << decg << std::endl;
  }
}




// 2進数表現までしかわからんかった
// int count_bits(unsigned x)
// {
//   int bits = 0;
//   while (x) 
//   {
//     if (x & 1U) bits++;
//     // 1bit右へずらす
//     x >>=1;
//   }
//   return bits;
// }

// int int_bits()
// {
//   return count_bits(~0U);
// }

// void print_bits(unsigned x)
// {
//   for (int i = int_bits() - 1; i >= 0; i--)
//   {
//     // iだけ右にずらして、1Uと論理積を取る
//     cout << ((x >> i) & 1U ? '1' : '0');
//   }
// }

// int main( int argc, char *argv[] )
// {
//   for (unsigned int i = 0; i <= 32; i++)
//   {
//     cout << i << ":";
//     print_bits(i);
//     cout << '\n';
//   }
// }