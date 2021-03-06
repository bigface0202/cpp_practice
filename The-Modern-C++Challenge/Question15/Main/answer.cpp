/**
 * @file answer.cpp
 * IPv4データ型
 * 
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
  
  // デフォルトコンストラクタ
  // コロンはコンストラクタ初期化子
  constexpr ipv4() : ipv4(0, 0, 0, 0) {}
  // コンストラクタ
  constexpr ipv4(unsigned char const a, unsigned char const b,
                unsigned char c, unsigned char d):
                data{{a, b, c, d}} {}
  // explicitを付けることで暗黙の型変換を防止する
  // 意図しないものが型変換されてコンパイルが通るのはマズイ
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
};

int main()
{
  ipv4 address(168, 192, 0, 1);
  std::cout << address << std::endl;

  ipv4 ip(255);
  std::cout << ip << std::endl; // 初期値(0.0.0.0)が表示される
  std::cin >> ip;
  if (!std::cin.fail())
    std::cout << "入力されたIP:" << ip << std::endl;
  else
    std::cout << "正しくないフォーマットです";
}

// class IPv4 
// {
//   private:
//     std::string ip_address;

//   public:
//     // コンストラクタ
//     IPv4()
//     {
//       std::cout << "IPv4アドレスを入力して下さい";
//       std::cin >> ip_address;
//     };

//     void display()
//     {
//       std::cout << ip_address << '\n';
//     }
// };

// int main( int argc, char *argv[] )
// {
//   IPv4 test;
//   test.display();
// }