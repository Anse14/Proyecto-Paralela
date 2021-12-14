#include "./RngStream.h"
#include <iostream>
#include <chrono>
#include <omp.h>
using namespace std;

auto main(int argc, const char** argv) -> int {
  int nP = (argc > 1)? atoi(argv[1]) : 200;

  omp_set_num_threads(1000); // set number of threads

  unsigned long seed[6] = {1806547166, 3311292359, 643431772,
                           1162448557, 3335719306, 4161054083};
  RngStream::SetPackageSeed(seed);
  RngStream RngArray[nP]; // array of RngStream objects

  std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();

#pragma omp parallel for
  for (int i = 0; i < nP; i++) {
    double number = RngArray[i].RandU01();
#pragma omp critical
    { std ::cout << number << " "; }
  }

  std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();

  std::cout << "Time difference = " << std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count() << "[ms]" << std::endl;
  std::cout << "Time difference = " << std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count() << "[µs]" << std::endl;
  std::cout << "Time difference = " << std::chrono::duration_cast<std::chrono::nanoseconds> (end - begin).count() << "[ns]" << std::endl;

  return 0;
}
