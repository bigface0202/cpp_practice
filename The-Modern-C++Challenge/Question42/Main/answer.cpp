/**
 * @file answer.cpp
 * 
 * 年間の日と週
 * @author bigface / created on 2021/09/07
 */
#include <stdio.h>
#include <iostream>
#include <chrono>
#include <date/date.h>
#include <date/iso_week.h>
/** 
 * 解答
*/
// 1年の何日目かは1月1日を引けば良い
// 1年の何周目かはyear_weeknum_weekdayを使えば良い

namespace chrono = std::chrono;

unsigned int day_of_year(const int y, unsigned int const m, unsigned int const d)
{
  using namespace date;
  
  if (m < 1 || m > 12 || d < 1 || d > 31) return 0;

  return (sys_days{ year{ y } / month{ m } / day{ d } } - 
          sys_days{ year{ y } / month{ 1 } / day{ 0 } }).count();
}

unsigned int calender_week(const int y, unsigned int const m, unsigned int const d)
{
  using namespace date;

  if (m < 1 || m > 12 || d < 1 || d > 31) return 0;

  auto const dt = date::year_month_day{ year{ y }, month{ m }, day{ d } };
  auto const tiso = iso_week::year_weeknum_weekday{ dt };

  return static_cast<unsigned int>(tiso.weeknum());
}

int main()
{
  using namespace date::literals;
  std::cout << calender_week(2021, 9, 7) << std::endl;
}