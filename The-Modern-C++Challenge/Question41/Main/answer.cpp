/**
 * @file answer.cpp
 * 
 * 曜日
 * @author bigface / created on 2021/09/06
 */
#include <stdio.h>
#include <iostream>
#include <chrono>
#include <date/date.h>
#include <date/iso_week.h>
/** 
 * 解答
*/

std::string day_of_week[7] = {"Mon", "Tue", "Wed", "Thu", "Fri", "Sat", "Sun"};

unsigned int week_day(int const y, unsigned int const m, unsigned int const d)
{
  using namespace date;

  if (m < 1 || m > 12 || d < 1 || d > 31) return 0;

  auto const dt = date::year_month_day{ year{ y }, month{ m }, day{ d } };
  auto const tiso = iso_week::year_weeknum_weekday{ dt };

  // キャストすればint型に変換できる
  return static_cast<unsigned int>(tiso.weekday());
}

int main()
{
  auto wday = week_day(2018, 5, 9);
  std::cout << day_of_week[wday - 1] << std::endl;
}


// 以下でも正解
// using namespace std::chrono_literals;
// namespace chrono = std::chrono;

// int day_of_week(date::sys_days const & date)
// {
//   auto wd = date::weekday{date};
//   return wd.iso_encoding();
// }

// int main()
// {
//   using namespace date::literals;
  
//   std::cout << day_of_week(2018_y/4/1) << std::endl;
// }