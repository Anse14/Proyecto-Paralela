#include "./RngStream.h"
#include "./Analyzer.h"
#include <iostream>
#include <vector>
#include <chrono>
#include <omp.h>
using namespace std;

chrono::duration<double> run(int nP, int numThreads) {
  omp_set_num_threads(numThreads);

  RngStream RngArray[numThreads];

  chrono::steady_clock::time_point begin = chrono::steady_clock::now();

#pragma omp parallel for
  for (int i = 0; i < nP; i++) {
    RngArray[omp_get_thread_num()].RandU01();
  }

  chrono::steady_clock::time_point end = chrono::steady_clock::now();

  return (end - begin);
}

auto main(int argc, const char** argv) -> int {
  unsigned long seed[6] = {1806547166, 3311292359, 643431772,
                           1162448557, 3335719306, 4161054083};
  RngStream::SetPackageSeed(seed);

  int nP = (argc > 1)? atoi(argv[1]) : 200;
  int numThreads = 0;

#pragma omp parallel
  {
    if(omp_get_thread_num() == 0) {
      numThreads = omp_get_num_threads();
    }
  }

  Analyzer<int, int> analyzer(run);

  vector<chrono::duration<double>> tiemposDeEjecucion;

  for(int i = 1; i <= 32; i *= 2) {
    tiemposDeEjecucion.push_back(analyzer.printResults(100, 1000000, i));
  }

  return 0;
}
