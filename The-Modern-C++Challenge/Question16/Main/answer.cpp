/**
 * @file answer.cpp
 * 
 * 範囲内のIPv4アドレスを列挙する
 * 実装しなければいけない内容としては、2つのアドレスの比較operator<、次のアドレスへ繰り上げるoperator++
 * @author bigface / created on 2021/07/24
 */
#include <stdio.h>
#include <iostream>
#include <array>
#include <sstream>

/**
 * 解答
 */

class ipv4 {
  std::array<unsigned char, 4> data;

public:
  // コンストラクタ
  // コロンはコンストラクタ初期化子
  constexpr ipv4() : ipv4(0, 0, 0, 0) {}
  constexpr ipv4(unsigned char const a, unsigned char const b,
                unsigned char c, unsigned char d):
                data{{a, b, c, d}} {}
  explicit constexpr ipv4(unsigned long a)
            :ipv4(static_cast<unsigned char>((a >> 24) & 0xFF),
                  static_cast<unsigned char>((a >> 16) & 0xFF),
                  static_cast<unsigned char>((a >> 8) & 0xFF),
                  static_cast<unsigned char>(a & 0xFF)
                  ) {}
  // noexceptを指定することで例外を送出しない
  ipv4(ipv4 const & other) noexcept : data(other.data) {}

  ipv4& operator= (ipv4 const & other) noexcept
  {
    data = other.data;
    return *this;
  }

  std::string to_string() const
  {
    std::stringstream sstr;
    sstr << *this;
    return sstr.str();
  }

  constexpr unsigned long to_ulong() const noexcept
  {
    return
      (static_cast<unsigned long>(data[0]) << 24) |
      (static_cast<unsigned long>(data[1]) << 16) |
      (static_cast<unsigned long>(data[2]) << 8) |
      static_cast<unsigned long>(data[3]);
  }

  friend std::ostream& operator<<(std::ostream& os, const ipv4& a)
  {
    os << static_cast<int>(a.data[0]) << '.'
       << static_cast<int>(a.data[1]) << '.'
       << static_cast<int>(a.data[2]) << '.'
       << static_cast<int>(a.data[3]);
    return os;
  }

  friend std::istream& operator>>(std::istream& is, ipv4& a)
  {
    char d1, d2, d3;
    int b1, b2, b3, b4;
    is >> b1 >> d1 >> b2 >> d2 >> b3 >> d3 >> b4;
    if (d1 == '.' && d2 == '.' && d3 == '.')
      a = ipv4(b1, b2, b3, b4);
    else
      is.setstate(std::ios_base::failbit);
    return is;
  }

  ipv4& operator++()
  {
    *this = ipv4(1 + to_ulong());
    return *this;
  }

  ipv4 operator++(int)
  {
    ipv4 result(*this);
    ++(*this);
    return result;
  }

  friend bool operator==(ipv4 const & a1, ipv4 const & a2) noexcept
  {
    return a1.data == a2.data;
  }

  friend bool operator!=(ipv4 const & a1, ipv4 const & a2) noexcept
  {
    return !(a1.data == a2.data);
  }

  friend bool operator<(ipv4 const & a1, ipv4 const & a2) noexcept
  {
    return a1.to_ulong() < a2.to_ulong();
  }

  friend bool operator>(ipv4 const & a1, ipv4 const & a2) noexcept
  {
    return a1.to_ulong() > a2.to_ulong();
  }

  friend bool operator<=(ipv4 const & a1, ipv4 const & a2) noexcept
  {
    return a1.to_ulong() <= a2.to_ulong();
  }

  friend bool operator>=(ipv4 const & a1, ipv4 const & a2) noexcept
  {
    return a1.to_ulong() >= a2.to_ulong();
  }
};

int main()
{
  ipv4 a1, a2;
  std::cout << "input 1st ip:";
  std::cin >> a1;
  std::cout << "input 2nd ip:";
  std::cin >> a2;

  std::cout << a1.to_ulong() << '\n';
  
  if (a2 > a1)
  {
    for (ipv4 a = a1; a <= a2; a++)
    {
      std::cout << a << std::endl;
    }
  }
  else
  {
    std::cerr << "invalid range!" << std::endl;
  }
}