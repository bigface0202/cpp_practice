/**
 * @file answer.cpp
 * 
 * 指定日付より古いファイルを削除する
 * @author bigface / created on 2021/08/27
 */
#include <stdio.h>
#include <iostream>
#include <sstream>
#include <filesystem>
#include <ctime>
#include <time.h>
#include <iomanip>

namespace fs = std::filesystem;
namespace ch = std::chrono;
/** 
 * 解答
*/

template <typename Duration>
bool is_older_than(fs::path const & path, Duration const duration)
{
  // time_since_epochは
  // エポックと呼ばれるUNIX誕生の日時(1970年1月1日 0時0分0秒)からの経過時間によって現在の時間を表す。
  auto ftimeduration = fs::last_write_time(path).time_since_epoch();
  auto nowduration = (ch::system_clock::now() - duration).time_since_epoch();
  std::cout << ch::duration_cast<Duration>(nowduration - ftimeduration).count() << std::endl;
  return ch::duration_cast<Duration>(nowduration - ftimeduration).count() > 0;
}

template <typename Duration>
void remove_files_older_than(fs::path const & path, Duration const duration)
{
  try
  {
    if (fs::exists(path))
    {
      if (is_older_than(path, duration))
      {
        // fs:removeだとフォルダが空じゃない場合は削除できない
        // fs::remove(path);
        fs::remove_all(path);
      }
      else if (fs::is_directory(path))
      {
        for (auto const & entry : fs::directory_iterator(path))
        {
          remove_files_older_than(entry.path(), duration);
        }
      }
    }
  }
  catch (std::exception const & ex)
  {
    std::cerr << ex.what() << std::endl;
  }
}

int main()
{
  using namespace std::chrono_literals;
  auto path = "/media/yusuke/Moon/GitHub/cpp_practice/The-Modern-C++Challenge/Question36/test copy";
  remove_files_older_than(path, 1h + 20min);
}

/** 
 * 必要な機能
 * file_time_typeをtimeに変換:done
 * 与えられた時間と↑を比較:done
 * recursive_directory_iteratorで再帰的に削除（？）=> イテレータの更新方法がわからなかった
 * => イテレータの更新方法は存在しないため、悪手だった
*/


// const chrono::system_clock::time_point gEpochTimeBias = 
// chrono::time_point_cast<chrono::system_clock::duration>(chrono::system_clock::now() - std::filesystem::file_time_type::clock::now().time_since_epoch());

// const time_t filetime2time(fs::file_time_type tp)
// {
//   auto sec = chrono::duration_cast<chrono::seconds>(tp.time_since_epoch());
//   chrono::time_point sctp = chrono::time_point_cast<chrono::system_clock::duration>(tp.time_since_epoch() + gEpochTimeBias);

//   const time_t time_tt = chrono::system_clock::to_time_t(sctp);

//   /* time_tをtm構造体に変換 */
//   std::tm* localt = std::localtime(&time_tt);
//   /* time_since_epoch()を使うとなぜか204年遅れるので204足す */
//   localt->tm_year = localt->tm_year + 204;

//   /* もう一回time_tに戻す */
//   time_t tim;
//   tim = mktime(localt);
//   std::cout << std::put_time(localt, "%c") << std::endl;
  
//   return tim;
// }

// void delete_file_directory(fs::path const & dir, tm set_time)
// {
//   if (fs::exists(dir))
//   {
//     for (const fs::directory_entry& entry : fs::recursive_directory_iterator(dir)) {
//       /* ファイル/フォルダ作成時間の抽出 */
//       fs::file_time_type filetime = fs::last_write_time(entry);
//       /* file_time_typeからtime_tに直す */
//       time_t created_time = filetime2time(filetime);
//       // std::cout << entry.path() << std::endl;
//       /* 差分を算出し、削除処理を実行 */
//       if (std::difftime(created_time, std::mktime(&set_time)) < 0)
//         fs::remove_all(entry.path());
//     }
//   }
//   else
//   {
//     std::cout << "File does not exist!" << std::endl;
//   }
// }

// int main( int argc, char *argv[] )
// {
//   /* ファイルパス */
//   fs::path fpath = "/media/yusuke/Moon/GitHub/cpp_practice/The-Modern-C++Challenge/Question36/test";

//   /* 所望の時間をstringからtmに変換 */
//   /* 時刻情報を格納するtm構造体変数tm. */
//   struct tm tm = {0};
//   strptime("2021/08/28 09:09:01", "%Y/%m/%d %H:%M:%S", &tm);

//   /* filesystemでフォルダの作成時間を取得する */
//   delete_file_directory(fpath, tm);
// }