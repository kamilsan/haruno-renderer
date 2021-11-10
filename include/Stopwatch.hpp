#ifndef STOPWATCH_HPP
#define STOPWATCH_HPP

#include <chrono>
#include <sstream>
#include <string>

class Stopwatch {
 public:
  Stopwatch() : isRunning_(false), startTime_(), elapsedSeconds_(0.0) {}

  static Stopwatch startNew() {
    Stopwatch watch;
    watch.start();
    return watch;
  }

  void start() {
    elapsedSeconds_ = 0.0;
    isRunning_ = true;
    startTime_ = std::chrono::steady_clock::now();
  }

  void stop() {
    const auto now = std::chrono::steady_clock::now();
    const std::chrono::duration<double> duration = now - startTime_;
    elapsedSeconds_ = duration.count();
    isRunning_ = false;
  }

  double getElapsedSeconds() const { return elapsedSeconds_; }

  std::string getElapsedTime() const {
    float seconds = elapsedSeconds_;
    size_t min = seconds / 60;
    seconds -= min * 60;
    size_t hours = min / 60;
    min -= hours * 60;

    std::stringstream ss;
    if (hours > 0) ss << hours << "h ";
    if (min > 0) ss << min << "m ";
    ss << seconds << "s\n";

    return ss.str();
  }

 private:
  bool isRunning_;
  std::chrono::steady_clock::time_point startTime_;
  double elapsedSeconds_;
};

#endif  // STOPWATCH_HPP