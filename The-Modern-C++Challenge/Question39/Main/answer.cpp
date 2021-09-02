/**
 * @file answer.cpp
 * 
 * 実行時間を測定する関数
 * @author bigface / created on 2021/09/02
 */
#include <stdio.h>
#include <iostream>
#include <chrono>
#include <thread>
#include <functional>

/** 
 * 解答
*/
template <typename Time = std::chrono::microseconds,
          typename Clock = std::chrono::high_resolution_clock>
// structはclassとほぼ同義
// デフォルトのアクセシビリティがpublicになる（classはprivate）
struct perf_timer
{
  template <typename F, typename... Args>
  // 各オブジェクトに属しないメンバ関数の場合は、静的メンバ関数にしたほうがよい
  static Time duration(F&& f, Args... args)
  {
    auto start = Clock::now();
    // std::invokeは関数呼び出し可能なオブジェクトfとその引数args...の組み合わせでINVOKE要件に従った関数呼び出しを行う
    // @see INVOKE要件：https://cpprefjp.github.io/reference/concepts/Invoke.html
    std::invoke(std::forward<F>(f), std::forward<Args>(args)...);
    auto end = Clock::now();

    return std::chrono::duration_cast<Time>(end - start);
  }
};

using namespace std::chrono_literals;
void f()
{
  std::this_thread::sleep_for(2s);
}

void g(int const /*a*/, int const /*b*/)
{
  std::this_thread::sleep_for(1s);
}

int main()
{
  // 静的メンバ関数なので、このような呼び出し方になっている
  auto t1 = perf_timer<std::chrono::microseconds>::duration(f);
  auto t2 = perf_timer<std::chrono::milliseconds>::duration(g, 1, 2);

  // durationに単位を渡すことで、その単位で表現してくれる（std::nanoでナノ単位）
  auto total = std::chrono::duration<double, std::nano>(t1 + t2).count();

  std::cout << total << std::endl;
}



// using namespace std::literals::chrono_literals;

// template<class Fn> void measurement(Fn fn)
// {
//   std::chrono::system_clock::time_point start, end;
//   std::time_t time_stamp;

//   start = std::chrono::system_clock::now();

//   fn();

//   end = std::chrono::system_clock::now();

//   auto time = end - start;

//   auto msec = std::chrono::duration_cast<std::chrono::milliseconds>(time).count();
//   std::cout << msec << " msec" << std::endl;
// }

// void test_func(int a)
// {
//   int ans;
//   for (int i = 0; i < a; i++)
//   {
//     ans = a + a;
//   }
// }

// int main( int argc, char *argv[] )
// {
//   measurement(test_func(10));
// }