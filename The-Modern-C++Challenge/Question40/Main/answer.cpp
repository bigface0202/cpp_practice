/**
 * @file answer.cpp
 * 
 * 2つの日付間の日数
 * @author bigface / created on 2021/09/04
 */
#include <stdio.h>
#include <iostream>
#include <chrono>
#include <date/date.h>
/** 
 * 解答
*/

namespace chrono = std::chrono;

inline int number_of_days(
  int const y1, unsigned int const m1, unsigned int const d1,
  int const y2, unsigned int const m2, unsigned int const d2
)
{
  using namespace date;

  return (sys_days{ year{ y1 } / month{ m1 } / day{ d1 } } - 
          sys_days{ year{ y2 } / month{ m2 } / day{ d2 } }).count();
}

inline int number_of_days(date::sys_days const & first, date::sys_days const & last)
{
  return (last - first).count();
}

int main()
{
  auto diff1 = number_of_days(2016, 9, 23, 2017, 5, 15);
  std::cout << diff1 << std::endl;

  using namespace date::literals;
  auto diff2 = number_of_days(2016_y/sep/23, 15_d/may/2017);
  std::cout << diff2 << std::endl;
}

// 下記でも正解
// int day_difference(std::string time1, std::string time2)
// {
//   /* 所望の時間をstringからtmに変換 */
//   /* 時刻情報を格納するtm構造体変数tm. */
//   struct tm tm1 = {0}, tm2 = {0};
//   strptime(time1.c_str(), "%Y/%m/%d %H:%M:%S", &tm1);
//   strptime(time2.c_str(), "%Y/%m/%d %H:%M:%S", &tm2);

//   return std::abs(tm1.tm_mday - tm2.tm_mday);
// }

// int main( int argc, char *argv[] )
// {
//   std::string time1 = "2021/09/04 09:08:00";
//   std::string time2 = "2021/09/05 09:08:00";

//   std::cout << day_difference(time1, time2) << std::endl;
// }