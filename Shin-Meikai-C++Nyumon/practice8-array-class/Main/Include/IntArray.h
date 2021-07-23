/**
 * @file Include.h
 * @author ykishishita / created on 2021/07/18
 * 
*/

#ifndef ___Class_IntArray
#define ___Class_IntArray

class IntArray {
  int nelem; // 配列の要素数
  int* vec; // 先頭要素へのポインタ
  
  public:
    /** 添字範囲エラー */
    class IdxRngErr {
      private:
        const IntArray* ident;
        int idx;
      public:
        IdxRngErr(const IntArray* p, int i) : ident(p), idx(i) { }
        int index() const { return idx; }
    };

    /** 明示的Constructor */
    explicit IntArray(int size) : nelem(size) { vec = new int[nelem]; }

    /** コピーコンストラクタ */
    IntArray(const IntArray& x);

    /** デストラクタ */
    ~IntArray() { delete[] vec; }

    /** Return number of element */
    int size() const { return nelem; }

    /** 代入演算子= */
    IntArray& operator=(const IntArray& x);

    /** 添付演算子[] */
    int& operator[](int i) { 
      if (i < 0 || i >= nelem)
        throw IdxRngErr(this, i);
      return vec[i]; 
    }

    /** const版添付演算子[] */
    const int& operator[](int i) const { 
      if (i < 0 || i >= nelem)
        throw IdxRngErr(this, i);
      return vec[i]; 
    } 
};

#endif