/**
 * @file answer.cpp
 * 任意個数の要素をコンテナに追加
 * 
 * @author bigface / created on 2021/07/24
 */
#include <stdio.h>
#include <iostream>
#include <vector>
#include <list>
#include <iterator>

/** 
 * 解答
*/
// typenameとclassの間に明確な違いはない
// クラス型はclassキーワードで受け取るようにし、int型など基本型はtypenameで受け取るようにするなど
// 工夫してもよい
template<class C, typename... Args>
// Args&&はユニバーサル参照
// 左辺値と右辺値を変更可能な参照で受け取る事ができる
// つまり、1,2,3,4も受け取れるし、a=1, b=2,みたいな変数の箱も受け取れる
void push_back(C& c, Args&&... args)
{
  (c.push_back(args), ...);
}

int main()
{
  std::vector<int> v;
  int a = 1, b = 2, c = 3;
  push_back(v, a, b, c, 4);
  // vの要素をイテレートしながら、std::coutに出力
  std::copy(std::begin(v), std::end(v), std::ostream_iterator<int>(std::cout, " "));
  std::cout << '\n';

  v[2] = 100;
  std::copy(std::begin(v), std::end(v), std::ostream_iterator<int>(std::cout, " "));
  std::cout << '\n';
  std::cout << c;
  std::cout << '\n';

  std::list <int> l;
  push_back(l, 1, 2, 3, 4);
  std::copy(std::begin(l), std::end(l), std::ostream_iterator<int>(std::cout, " "));
}

// template<class C, class T>

// void pushone(C & c, T & value)
// {

// }

// void pushback(C & c, T &&... value)
// {
//   pushone(c, pushone(value...))
// }

// int main( int argc, char *argv[] )
// {
    
// }