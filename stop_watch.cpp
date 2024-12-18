#include "stop_watch.h"

#include <iostream>

StopWatch::StopWatch()
{
    Start("");
}

void StopWatch::Start(const std::string& name)
{
    start_ = std::chrono::high_resolution_clock::now();
    name_ = name;
    wraps_.clear();
}

void StopWatch::Wrap(const std::string& message)
{
    wraps_.emplace_back(message, std::chrono::high_resolution_clock::now());
}

void StopWatch::Print()
{
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start_);

    printf("  %-10s: %5lld us\n", name_.c_str(), duration.count());

    for (const auto& wrap : wraps_)
    {
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(wrap.second - start_);
        printf("  %-12s: %5lld us\n", wrap.first.c_str(), duration.count());
    }
}

StopWatch StopWatchG::sw_ = StopWatch();
std::mutex StopWatchG::mtx_;
void StopWatchG::Start(const std::string& name)
{
    std::lock_guard<std::mutex> lock(mtx_);
    sw_.Start( name );
}
void StopWatchG::Wrap(const std::string& message)
{
    std::lock_guard<std::mutex> lock(mtx_);
    sw_.Wrap(message);
}
void StopWatchG::Print()
{
    std::lock_guard<std::mutex> lock(mtx_);
    sw_.Print();
}