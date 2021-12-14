#include "./RngStream.h"
#include <iostream>
#include <omp.h>
using namespace std;

auto main(int argc, const char** argv) -> int {
  int nP = 200;
  omp_set_num_threads(nP); // set number of threads
  unsigned long seed[6] = {1806547166, 3311292359, 643431772,
                           1162448557, 3335719306, 4161054083};
  RngStream::SetPackageSeed(seed);
  RngStream RngArray[nP]; // array of RngStream objects

#pragma omp parallel for
  for (int i = 0; i < nP; i++) {
    double number = RngArray[i].RandU01();
#pragma omp critical
    { std ::cout << number << " "; }
  }

  return 0;
}
