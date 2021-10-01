/**
 * @file answer.cpp
 * 
 * ダブルバッファ
 * @author bigface / created on 2021/09/27
 */

/** 
 * 解答
*/

#include <stdio.h>
#include <iostream>
#include <mutex>
#include <thread>
#include <numeric>
#include <array>
#include <vector>
#include <algorithm>
#include <iterator>

template <typename T>
class double_buffer
{
  typedef T         value_type;
  typedef T&        reference;
  typedef T const & const_reference;
  typedef T*        pointer;

public:
  explicit double_buffer(size_t const size) : rdbuf(size), wrbuf(size) {}

  size_t size() const noexcept { return rdbuf.size(); }

  void write(T const * const ptr, size_t const size)
  {
    std::unique_lock<std::mutex> lock(mt);
    auto length = std::min(size, wrbuf.size());
    std::copy(ptr, ptr + length, std::begin(wrbuf));
    // wrbufとrdbufの中身を入れ替える = 書き込みが終わった内容をread bufferへ入れる
    wrbuf.swap(rdbuf);
  }

  template <class Output>
  void read(Output it) const
  {
    std::unique_lock<std::mutex> lock(mt);
    // rdbufの中身をitにコピーする
    std::copy(std::cbegin(rdbuf), std::cend(rdbuf), it);
  }
  pointer data() const
  {
    std::unique_lock<std::mutex> lock(mt);
    return rdbuf.data();
  }

  reference operator[](size_t const pos)
  {
    std::unique_lock<std::mutex> lock(mt);
    return rdbuf[pos];
  }

  const_reference operator[](size_t const pos) const
  {
    std::unique_lock<std::mutex> lock(mt);
    return rdbuf[pos];
  }

  void swap(double_buffer other)
  {
    std::swap(rdbuf, other.rdbuf);
    std::swap(wrbuf, other.wrbuf);
  }

private:
  std::vector<T> rdbuf;
  std::vector<T> wrbuf;
  // mutableを付けるとconstメンバ関数内でも値を変更できる
  // mutexはlockしたりunlockしたりするので、変更する必要がある
  mutable std::mutex mt;
};

template <typename T>
void print_buffer(double_buffer<T> const & buf)
{
  buf.read(std::ostream_iterator<T>(std::cout, " "));
  std::cout << std::endl;
}


int main( int argc, char *argv[] )
{
  double_buffer<int> buf(10);
  
  // 書き込み用のスレッド
  std::thread t([&buf]() {
    for (int i = 1; i < 1000; i += 10)
    {
      int data[10] = {};
      // std::iotaは指定された値から始まる整数列を生成する
      std::iota(std::begin(data), std::end(data), i);
      buf.write(data, std::size(data));

      using namespace std::chrono_literals;
      std::this_thread::sleep_for(100ms);
    }
  });

  // 読み出し
  auto start = std::chrono::system_clock::now();
  do
  {
    print_buffer(buf);
    using namespace std::chrono_literals;
    std::this_thread::sleep_for(150ms);
  } while (std::chrono::duration_cast<std::chrono::seconds>(std::chrono::system_clock::now() - start).count() < 12);
  
  // threadはjoinして終了
  t.join();
}