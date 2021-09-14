/**
 * @file answer.cpp
 * 
 * 優先度付きキュー
 * @author bigface / created on 2021/09/14
 */
#include <stdio.h>
#include <iostream>
#include <functional>

/** 
 * 解答
*/
// 一番簡単な方法は
// std::vectorを要素のコンテナとして使い、常にソートされた状態に保持する
// →優先度が高いものほど前に来る
// 但し効率が最も良い方法ではない

// 最も適したデータ構造はヒープとなる
// 簡単に言えばツリー構造のデータ
// 親要素は常に子要素より大きい（小さい）もしくは等しい
// 大きい場合は最大ヒープ、小さい場合は最小ヒープ

// std::lessは左辺が右辺より小さいかの比較を行う関数オブジェクト
template <class T, class Compare = std::less<typename std::vector<T>::value_type>>
class priority_queue
{
  // typedefで既存の型名に名前を付けることが出来る
  // 以下だと、std::vector<T>::value_typeにvalue_typeっていう名前を付けている
  typedef typename std::vector<T>::value_type       value_type;
  typedef typename std::vector<T>::size_type        size_type;
  typedef typename std::vector<T>::reference        reference;
  typedef typename std::vector<T>::const_reference  const_reference;

  public:
    bool empty() const noexcept { return data.empty(); }
    
    size_type size() const noexcept { return data.size(); }
    
    // vectorの型↓
    void push(value_type const & value)
    {
      data.push_back(value);
      std::push_heap(std::begin(data), std::end(data), comparer);
    }

    void pop()
    {
      // pop_heapはヒープ化された範囲の先頭と末尾を入れ替え、最終要素を使用せずにヒープ範囲を作り直す
      std::pop_heap(std::begin(data), std::end(data), comparer);
      // 末尾に送った最終要素をpopする
      data.pop_back();
    }

    const_reference top() const { return data.front(); }

    void swap(priority_queue& other) noexcept
    {
      swap(data, other.data);
      swap(comparer, other.comparer);
    }

  private:
    std::vector<T> data;
    Compare comparer;
};

template <class T, class Compare>
void swap(priority_queue<T, Compare>& lhs,
          priority_queue<T, Compare>& rhs)
          noexcept(noexcept(lhs.swap(rhs)))
{
  lhs.swap(rhs);
}

int main( int argc, char *argv[] )
{
  priority_queue<int> q;
  priority_queue<int> q2;
  for (int i : {1, 5, 3, 1, 13, 21, 8})
  {
    q.push(i);
  }

  for (int i : {2, 10, 6, 2, 26, 42, 16})
  {
    q2.push(i);
  }

  q.swap(q2);

  while (!q.empty())
  {
    std::cout << q.top() << ' ';
    q.pop();
  }
}