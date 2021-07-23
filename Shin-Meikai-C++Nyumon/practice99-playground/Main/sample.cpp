/**
 * @file sample.cpp
 *
 * @author bigface / created on 2021/07/05
 */
#include <iostream>
#include <stdio.h>
#include <chrono>
#include <ctime>

using namespace std;

int main( int argc, char *argv[] )
{
  struct timespec ts;
  struct tm t;
  int ret;

  // Get epoch time
  ret = clock_gettime(CLOCK_REALTIME, &ts);
  if (ret < 0) {
    perror("clock_gettime fail");
  }

  // Convert into local and parsed time
  localtime_r(&ts.tv_sec, &t);

  // Create string with strftime
  char buf[32];
  ret = strftime(buf, 32, "%Y/%m/%d %H:%M:%S", &t);
  if (ret == 0) {
    perror("strftime fail");
  }

  // Add milli-seconds with snprintf
  char output[32];
  const int msec = ts.tv_nsec / 1000000;
  ret = snprintf(output, 32, "%s.%03d", buf, msec);
  if (ret == 0) {
    perror("snprintf fail");
  }

  // Result
  std::cout << std::string(output) << std::endl;

  return 0;
}