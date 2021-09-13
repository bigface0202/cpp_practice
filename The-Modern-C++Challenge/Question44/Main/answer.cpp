/**
 * @file answer.cpp
 * 
 * 月間カレンダー
 * @author bigface / created on 2021/09/12
 */
#include <stdio.h>
#include <iostream>
#include <chrono>
#include <date/date.h>
#include <date/iso_week.h>
#include <iomanip>

/** 
 * 解答
*/

// まずは月の初日の曜日を取得する
// 月の日数を取得する
// 初日の曜日で始めの週の1日をオフセットする
// 月の日数でループを回す
// 7日毎に改行する

unsigned int week_day(int const y, unsigned int const m, unsigned int const d)
{
  using namespace date;

  if (m < 1 || m > 12 || d < 1 || d > 31) return 0;

  auto const dt = date::year_month_day{ year{ y }, month{ m }, day{ d } };
  auto const tiso = iso_week::year_weeknum_weekday{ dt };

  return static_cast<unsigned int>(tiso.weekday());
}

void print_month_calendar(int const y, unsigned int m)
{
  using namespace date;
  std::cout << "Mon Tue Wed Thu Fri Sat Sun" << std::endl;

  auto first_day_weekday = week_day(y, m, 1);
  // year_month_day_lastは（）で指定するらしい。ややこしい、、、
  // year_month_day_lastはmonthにmonth_day_lastを引数として受ける
  auto last_day = static_cast<unsigned int>(year_month_day_last( year{ y }, month_day_last{ month{ m } }).day());

  unsigned int index = 1;
  // 最初の日の曜日オフセット分だけずらす
  for (unsigned int day = 1; day < first_day_weekday; ++day, ++index)
  {
    std::cout << "    ";
  }
  
  for (unsigned int day = 1; day <= last_day; ++day)
  {
    std::cout << std::right << std::setfill(' ') << std::setw(3) << day << ' ';
    if (index ++ % 7 == 0) std::cout << std::endl;
  }

  std::cout << std::endl;
}

int main()
{
  print_month_calendar(2021, 9);
}

// int main()
// {
//   unsigned int y, m;
//   std::cout << "Year: "; std::cin >> y;
//   std::cout << "Month: "; std::cin >> m;

// }