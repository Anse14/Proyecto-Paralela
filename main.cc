#include "./RngStream.h"
#include <iostream>
#include <omp.h>
using namespace std;

auto main() -> int {
  // unsigned long seed[6] = {327612383, 317095578,  14704821,
  // 884064067, 1017894425, 16401881};
  // RngStream::SetPackageSeed(seed);

  // RngStream R;

  // R.IncreasedPresic(true);
  // R.SetAntithetic(true);

  // cout << "Valor: " << R.RandU01() << endl;
  // cout << "Valor: " << R.RandU01() << endl;
  // cout << "Valor: " << R.RandU01() << endl;

  // R.ResetNextSubstream();
  //  R.AdvanceState(10, 6);
  // cout << endl;

  // cout << "Valor: " << R.RandU01() << endl;
  // cout << "Valor: " << R.RandU01() << endl;
  // cout << "Valor: " << R.RandU01() << endl;

  // cout << endl;

  // cout << R.RandInt(10, 20) << endl;
  // cout << R.RandInt(10, 20) << endl;
  // cout << R.RandInt(10, 20) << endl;
  // cout << R.RandInt(10, 20) << endl;
  // cout << R.RandInt(10, 20) << endl;

  // R.WriteState();

  //int nP = omp_get_num_procs();
  omp_set_num_threads(2000); // set number of threads
  unsigned long seed[6] = {1806547166, 3311292359, 643431772,
                           1162448557, 3335719306, 4161054083};
  RngStream::SetPackageSeed(seed);
  RngStream RngArray[2000]; // array of RngStream objects
  int myRank;
#pragma omp parallel private(myRank)
  {
    myRank = omp_get_thread_num();
#pragma omp critical
    { std ::cout << RngArray[myRank].RandU01() << " "; }
  }
  std ::cout << std ::endl;

  return 0;
}
