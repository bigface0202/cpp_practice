/**
 * @file answer.cpp
 * 
 * プロセスのリストを表形式で出力する
 * @author bigface / created on 2021/08/23
 */
#include <stdio.h>
#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>
#include <iomanip>

/** 
 * 解答（途中まで合ってたのでそのまま書く
*/
enum class procstatus {suspended, running};
std::string status2string(procstatus const status)
{
  if (status == procstatus::suspended)
    return "suspended";
  else
    return "running";
}

enum class platforms {p32bit, p64bit};
std::string platform2string(platforms const platform)
{
  if (platform == platforms::p32bit)
    return "32-bit";
  else
    return "64-bit";
}

struct procinfo 
{
  int id;
  std::string name;
  procstatus status;
  std::string account;
  size_t memory;
  platforms platform;
};

void print_processes(std::vector<procinfo> processes)
{
  std::sort(std::begin(processes), std::end(processes),
            // 関数オブジェクトの中身を変更する必要があるので、参照渡し
            // ちなみに実体渡しだとクラスのコンストラクタが呼ばれない
            [](procinfo const & p1, procinfo const & p2) {
              return p1.name < p2.name;
            });
  for (auto const & pi : processes) {
    // setwでフィールドの幅を決定する
    // setfillで与えられた文字で埋める
    // std::left or rightで左 or 右詰め
    std::cout << std::left << std::setw(20) << std::setfill(' ') << pi.name;
    std::cout << std::left << std::setw(8) << std::setfill(' ') << pi.id;
    std::cout << std::left << std::setw(12) << std::setfill(' ') << status2string(pi.status);
    std::cout << std::left << std::setw(15) << std::setfill(' ') << pi.account;
    std::cout << std::right << std::setw(10) << std::setfill(' ') << static_cast<int>(pi.memory / 1024);
    std::cout << std::left << ' ' << platform2string(pi.platform);
    std::cout << std::endl;
  }
}

// void print_processes(std::vector<procinfo> processes)
// {
//   std::ostringstream oss;
//   for (auto process : processes) {
//     if(typeid(process).name() == "procstatus")
//       oss << 
//   }
// }

int main( int argc, char *argv[] )
{
  using namespace std::string_literals;
  std::vector<procinfo> processes
  {
    {512, "cmd.exe"s, procstatus::running, "SYSTEM"s, 148293, platforms::p64bit },
    {1044, "chrome.exe"s, procstatus::running, "marius.bancila"s, 25180454, platforms::p32bit},
    {7108, "explorer.exe"s, procstatus::running, "marius.bancila"s, 2952943, platforms::p64bit },
    {10100, "chrome.exe"s, procstatus::running, "marius.bancila"s, 227756123, platforms::p32bit},
    {22456, "skype.exe"s, procstatus::suspended, "marius.bancila"s, 16870123, platforms::p64bit }, 
  };
  print_processes(processes);
}