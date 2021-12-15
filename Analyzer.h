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

  std::chrono::duration<double> printResults(int times, Types... params) {
    //((std::cout << "->" << params), ...); 
    using expander = int[];
    (void)expander{0, (void(std::cout << "->" << params), 0)...};

    std::cout << std::endl;

    auto count = this->test(times, params...);

    //std::cout
        //<< "Time difference = "
        //<< std::chrono::duration_cast<std::chrono::milliseconds>(count).count()
        //<< "[ms]" << std::endl;
    std::cout
        << "Time difference = "
        << std::chrono::duration_cast<std::chrono::microseconds>(count).count()
        << "[µs]" << std::endl;
    //std::cout
        //<< "Time difference = "
        //<< std::chrono::duration_cast<std::chrono::nanoseconds>(count).count()
        //<< "[ns]" << std::endl;
    return count;
  }

  //double calcSpeedup(int times, Types... sec, Types... paral) {
    //auto secTime = std::chrono::duration_cast<std::chrono::microseconds>(test(times, sec...)).count();
    //auto paralTime = std::chrono::duration_cast<std::chrono::microseconds>(test(times, paral...)).count();

    
  //}
};
