#pragma once
#include <chrono>
#include <functional>
#include <iostream>

template <typename... Types> class Analyzer {
  using testfunc_t = std::function<std::chrono::duration<double>(Types...)>;

private:
  testfunc_t run;

public:
  Analyzer(testfunc_t _run) { run = _run; }

  std::chrono::duration<double> test(int times, Types... params) {
    std::chrono::duration<double> count(0);
    for (int i = 0; i < times; i++) {
      count += run(params...);
    }
    count /= times;
    return count;
  }

  void printResults(int times, Types... params) {
    ((std::cout << "->" << params), ...); 

    std::cout << std::endl;

    auto count = this->test(times, params...);

    std::cout
        << "Time difference = "
        << std::chrono::duration_cast<std::chrono::milliseconds>(count).count()
        << "[ms]" << std::endl;
    std::cout
        << "Time difference = "
        << std::chrono::duration_cast<std::chrono::microseconds>(count).count()
        << "[µs]" << std::endl;
    std::cout
        << "Time difference = "
        << std::chrono::duration_cast<std::chrono::nanoseconds>(count).count()
        << "[ns]" << std::endl;
  }
};