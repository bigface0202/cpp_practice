/**
 * @file answer.cpp
 * 
 * 一時ログファイル
 * @author bigface / created on 2021/08/30
 */
#include <stdio.h>
#include <iostream>
#include <string>
#include <filesystem>
#include <fstream>
#include <ostream>

#include "uuid.h"

namespace fs = std::filesystem;

class logger
{
  fs::path logpath;
  std::ofstream logfile;

public:
  logger()
  {
    std::random_device rd;
    auto seed_data = std::array<int, std::mt19937::state_size> {};
    std::generate(std::begin(seed_data), std::end(seed_data), std::ref(rd));
    std::seed_seq seq(std::begin(seed_data), std::end(seed_data));
    std::mt19937 engine(seq);
    uuids::uuid_random_generator gen(&engine);
    auto name = uuids::to_string(gen());
    logpath = fs::temp_directory_path() / (name + ".tmp");
    logfile.open(logpath.c_str(), std::ios::out | std::ios::trunc);
  }

  ~logger() noexcept
  {
    try {
      if (logfile.is_open()) logfile.close();
      if (!logpath.empty()) fs::remove(logpath);
    }
    catch (...) {}
  }

  void persist(fs::path const & path)
  {
    logfile.close();
    fs::rename(logpath, path);
    logpath.clear();
  }

  logger& operator<<(std::string const & message)
  {
    logfile << message.c_str() << '\n';
    return *this;
  }
};

int main()
{
  logger log;
  try {
    log << "this is a line" << "and this is another one";
    throw std::runtime_error("error");
  }
  catch(...) {
    log.persist(R"(/media/yusuke/Moon/GitHub/cpp_practice/The-Modern-C++Challenge/Question38/Main/lastlog.txt)");
    
  }
}

// ↓でほぼ正解（さすがにサードパーティのuuid使うとは思わなかった）
// ログファイルを書き出し・削除するクラスを作る
// ログを書き込むメンバ関数を作る
// ログファイルを保存するかどうかをbooleanで受け取る
// ログファイル削除する場合はディストラクタで削除する

// class Logger 
// {
// private:
//   fs::path temppath;
//   std::ofstream fileout;
//   bool is_save;

// public:
//   Logger(bool save)
//   {
//     is_save = save;
//     temppath = fs::temp_directory_path() / "temp.txt";
//     fileout.open(temppath.native(), std::ios::out | std::ios::trunc);
//     if (!fileout.is_open())
//       throw std::runtime_error("Failed to open file.");
//   }

//   ~Logger()
//   {
//     fileout.close();
//     if (!is_save)
//       fs::remove(temppath);
//   }

//   void writeLogger(std::string log)
//   {
//     if (!fileout.is_open())
//       throw std::runtime_error("Failed to write file.");
//     fileout << log << '\n';
//   }
// };

// int main( int argc, char *argv[] )
// {
//   Logger logger(true);

//   logger.writeLogger("aaaa");
// }