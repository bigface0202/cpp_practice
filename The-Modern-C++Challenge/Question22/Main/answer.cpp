/**
 * @file answer.cpp
 * さまざまな温度単位のリテラル
 * 
 * @author bigface / created on 2021/07/24
 */
#include <stdio.h>
#include <iostream>
#include <cmath>
#include <assert.h>

/**
 * 解答
 */

// 浮動小数点の比較をする
bool are_equal(double const d1, double const d2, double const epsilon = 0.001)
{
  // std::fabs 絶対値を取得する
  return std::fabs(d1 - d2) < epsilon;
}

// 温度単位の列挙型と温度値を表すクラス
namespace temperature
{
  enum class scale { celsius, fahrenheit, kelvin };

  template <scale S>
  class quantity
  {
    double const amount;
  public:
    constexpr explicit quantity(double const a): amount(a) {}
    explicit operator double() const { return amount; }  
  };
}

namespace temperature
{
  template <scale S>
  inline bool operator==(quantity<S> const & lhs, quantity<S> const & rhs)
  {
    return are_equal(static_cast<double>(lhs), static_cast<double>(rhs));
  }

  template <scale S>
  inline bool operator!=(quantity<S> const & lhs, quantity<S> const & rhs)
  {
    return !(lhs == rhs);
  }

  template <scale S>
  inline bool operator<(quantity<S> const & lhs, quantity<S> const & rhs)
  {
    return static_cast<double>(lhs) < static_cast<double>(rhs);
  }

  template <scale S>
  inline bool operator>(quantity<S> const & lhs, quantity<S> const & rhs)
  {
    return rhs < lhs;
  }

  template <scale S>
  inline bool operator<=(quantity<S> const & lhs, quantity<S> const & rhs)
  {
    return !(lhs > rhs);
  }
  
  template <scale S>
  inline bool operator>=(quantity<S> const & lhs, quantity<S> const & rhs)
  {
    return !(lhs < rhs);
  }

  template <scale S>
  constexpr quantity<S> operator+(quantity<S> const &q1, quantity<S> const &q2)
  {
    return quantity<S>(static_cast<double>(q1) + static_cast<double>(q2));
  }

  template <scale S>
  constexpr quantity<S> operator-(quantity<S> const &q1, quantity<S> const &q2)
  {
    return quantity<S>(static_cast<double>(q1) - static_cast<double>(q2));
  }

  // Traits
  // 特殊化を用いている
  // テンプレートクラスや関数に対して、特定の型が指定された場合の実装や定義を記述できる
  // 型に応じた型を返すことができる
  template <scale S, scale R>
  struct conversion_traits
  {
    static double convert(double const value) = delete;
  };

  template <>
  struct conversion_traits<scale::celsius, scale::kelvin>
  {
    static double convert(double const value)
    {
      return value + 273.15;
    }
  };

  template <>
  struct conversion_traits<scale::kelvin, scale::celsius>
  {
    static double convert(double const value)
    {
      return value - 273.15;
    }
  };

  template <>
  struct conversion_traits<scale::celsius, scale::fahrenheit>
  {
    static double convert(double const value)
    {
      return (value * 9) / 5 + 32;;
    }
  };

  template <>
  struct conversion_traits<scale::fahrenheit, scale::celsius>
  {
    static double convert(double const value)
    {
      return (value - 32) * 5 / 9;
    }
  };

  template<>
  struct conversion_traits<scale::fahrenheit, scale::kelvin>
  {
    static double convert(double const value)
    {
      return (value + 459.67) * 5 / 9;
    }
  };

  template<>
  struct conversion_traits<scale::kelvin, scale::fahrenheit>
  {
    static double convert(double const value)
    {
      return (value * 9) / 5 - 459.67;
    }
  };
  
  // S:今のスケール、R:キャストするスケール
  template <scale R, scale S>
  constexpr quantity<R> temperature_cast(quantity<S> const q)
  {
    return quantity<R>(conversion_traits<S, R>::convert(static_cast<double>(q)));
  }

  // ユーザー定義リテラル演算子
  // 識別子はアンダースコアから始めないといけない
  // temperatureに新たな名前空間を設ける
  namespace temperature_scale_literals
  {
    constexpr quantity<scale::celsius> operator "" _deg(long double const amount)
    {
      return quantity<scale::celsius> {static_cast<double>(amount)};
    }
    
    constexpr quantity<scale::fahrenheit> operator "" _f(long double const amount)
    {
      return quantity<scale::fahrenheit> {static_cast<double>(amount)};
    }

    constexpr quantity<scale::kelvin> operator "" _k(long double const amount)
    {
      return quantity<scale::kelvin> {static_cast<double>(amount)};
    }
  }
}


int main( int argc, char *argv[] )
{
  using namespace temperature;
  using namespace temperature_scale_literals;

  auto t1{ 1.0_deg };
  auto t2{ 79.0_f };
  auto t3{ 274.15_k };
  // temperature_castでは、
  // まずscale::~で型を与える
  // Traitsを使って、与えられた型に対する数値の変換を行う（セルシウスに273.15を足し引きするなど）
  if (temperature_cast<scale::kelvin>(t1) == t3)
  {
    std::cout << "同じです\n";
  }
  else{
    std::cout << "違います\n";
  }
}