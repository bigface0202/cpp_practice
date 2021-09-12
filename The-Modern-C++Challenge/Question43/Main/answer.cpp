/**
 * @file answer.cpp
 * 
 * 複数のタイムゾーンにおける打ち合わせ時刻
 * @author bigface / created on 2021/09/08
 */
#include <stdio.h>
#include <iostream>
#include <string>
#include <vector>
#include <string_view>
#include <iomanip>
#include "date/date.h"
#include "date/tz.h"

struct user
{
  std::string             Name;
  date::time_zone const * Zone;
  
  // コンストラクタ
  // NameとZoneに初期値を代入
  // structはほぼclassと同義
  user(std::string_view name, std::string_view zone)
    // locate_zoneにはstringを渡す
    : Name{name.data()}, Zone(date::locate_zone(zone.data()))
  {      
  }
};

template <class Duration, class TimeZonePtr>
void print_meeting_times(
  date::zoned_time<Duration, TimeZonePtr> const & time,
  std::vector<user> const & users
)
{
  std::cout << std::left << std::setw(15) << std::setfill(' ') 
            << "Local time:" 
            << time 
            << std::endl;

  for (auto const & user : users)
  {
    std::cout << std::left << std::setw(15) << std::setfill(' ')
              << user.Name
              << date::zoned_time<Duration, TimeZonePtr>(user.Zone, time)
              << std::endl;
  }
}

int main(){
  std::vector<user> users{
    user{ "test1", "Europe/Budapest" },
    user{ "test2", "Europe/Berlin" },
    user{ "test3", "America/New_York" }
  };
  unsigned int h, m;
  std::cout << "Hour: "; std::cin >> h;
  std::cout << "Minutes: "; std::cin >> m;

  date::year_month_day today = date::floor<date::days>(std::chrono::system_clock::now());

  // zoned_timeでタイムゾーンを考慮した時間軸上の一点を表す型
  // 現在地の時刻を取得する
  auto localtime = date::zoned_time<std::chrono::minutes>(
    date::current_zone(),
    static_cast<date::local_days>(today) + std::chrono::hours { h } + std::chrono::minutes { m }
  );

  print_meeting_times(localtime, users);

}