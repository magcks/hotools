// Compile: g++ -oprogress progress.example.cc -std=c++11 -pthread
// Useage:  ./progress

#include "progress.h"

#include <iostream>
#include <chrono>
#include <thread>

int main()
{
	int count = 1000;
	progress::handle prog/*(std::cout, count)*/;
	prog.start(count); // or use this if you don't want to construct with count
	for (int i = 0; i < count; ++i) {
		std::this_thread::sleep_for(std::chrono::milliseconds(2));
		prog(i);
	}
	prog.end(); // make 100%!
	std::cout << "Yeah!" << std::endl;
}
