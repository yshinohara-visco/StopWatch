#include <iostream>
#include <thread>

#include "stop_watch.h"

int main()
{
	// Wrapで時間を記録し、Printで出力
	StopWatch sw;
	sw.Start("main");
	for (size_t i = 0; i < 10; i++)
	{
		std::this_thread::sleep_for(std::chrono::milliseconds(1));
		sw.Wrap(std::to_string(i));
	}
	sw.Wrap("end");
	sw.Print();

	// StopWatchGはスコープを跨ぐ時とかに使う
	auto wrap = [](const std::string& message)
    {
		for (size_t i = 0; i < 10; i++)
		{
			std::this_thread::sleep_for(std::chrono::milliseconds(1));
			StopWatchG::Wrap(message + std::to_string(i));
		}
	};
	StopWatchG::Start("main");
	auto th = std::thread([&]{
		wrap("th1-");
	});
	wrap("main-");
	th.join();
	StopWatchG::Print();


	return 0;
}
