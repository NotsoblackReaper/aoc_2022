#include "AOC_Solver.h"
#include "AOC_Methods.cuh"

#include <iostream>
#include <chrono>
#include <tuple>
#include <numeric>
#include <algorithm>
#include <functional>
#include <iomanip>
#include <Windows.h>   // WinApi header


double scaledTime(double time)
{
	while (time > 1000)
	{
		time /= 1000;
	}
	return time;
}

const char* unitFromNano(double time)
{
	const char* units[4] ={ "ns","us","ms","s" };
	int i = 0;
	while (time > 1000)
	{
		++i;
		time /= 1000;
	}
	return units[i];
}

HANDLE hConsole;
auto print = [](int day, int iterations, const uint64_t part1, double elapsed1_median, double elapsed1_mean,
                double elapsed1_max, const uint64_t part2, double elapsed2_median, double elapsed2_mean,
                double elapsed2_max){
		SetConsoleTextAttribute(hConsole, day % 14 + 1);
	std::cout << "\t~~~~~~~~~~~~~~~ Day: " << day <<"\tIterations: "<<iterations<< " ~~~~~~~~~~~~~~~";
	SetConsoleTextAttribute(hConsole, 15);
	std::cout
		<< "\nPart 1: " << part1 << "\nElapsed Time:"
		<< "\tMedian " << scaledTime(elapsed1_median) << unitFromNano(elapsed1_median)
		<< "\tMean " << scaledTime(elapsed1_mean) << unitFromNano(elapsed1_mean)
		<< "\tMaximum " << scaledTime(elapsed1_max) << unitFromNano(elapsed1_max)
		<< "\nPart 2: " << part2 << "\nElapsed Time:"
		<< "\tMedian " << scaledTime(elapsed2_median) << unitFromNano(elapsed2_median)
		<< "\tMean " << scaledTime(elapsed2_mean) << unitFromNano(elapsed2_mean)
		<< "\tMaximum " << scaledTime(elapsed2_max) << unitFromNano(elapsed2_max) << "\n\n";
};

template<typename F, typename I>
std::tuple<uint64_t, double> Runner(F func, I* input, int dataLenght) {
	auto start = std::chrono::high_resolution_clock::now();
	uint64_t result = func(input,dataLenght);
	auto end = std::chrono::high_resolution_clock::now();
	auto elapsed = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
	return std::make_tuple(result, elapsed);
}

template<typename INPUT, int N, typename F1, typename F2>
double benchmark_day(INPUT* data,int dataLength, F1 part1, F2 part2, int day) {
	std::vector<double>part1_times(N);
	uint64_t r1 = UINT64_MAX, r2 = UINT64_MAX;
	for (int i = 0; i < N; ++i) {
		auto [result1, elapsed1] = Runner(part1, data, dataLength);
		part1_times[i] = elapsed1;
		if (r1 == UINT64_MAX)r1 = result1;
		else if (r1 != result1)throw std::runtime_error("inconsistent result at day " + day);
	}
	std::vector<double>part2_times(N);
	for (int i = 0; i < N; ++i) {
		auto [result2, elapsed2] = Runner(part2, data, dataLength);
		part2_times[i] = elapsed2;
		if (r2 == UINT64_MAX)r2 = result2;
		else if (r2 != result2)throw std::runtime_error("inconsistent result at day " + day);
	}
	double avg1 = std::accumulate(part1_times.begin(), part1_times.end(), 0.0) / N;
	double avg2 = std::accumulate(part2_times.begin(), part2_times.end(), 0.0) / N;
	std::ranges::nth_element(part1_times, part1_times.begin() + N / 2);
	double median1 = part1_times[N / 2];
	std::ranges::nth_element(part2_times, part2_times.begin() + N / 2);
	double median2 = part2_times[N / 2];
	double max1 = *std::ranges::max_element(part1_times);
	double max2 = *std::ranges::max_element(part2_times);

	print(day, N,
		r1, median1, avg1, max1,
		r2, median2, avg2, max2);
	return median1 + median2;
}

#if NDEBUG
constexpr int N = 100;
#endif
#if !NDEBUG
constexpr int N = 1;
#endif
int main()
{
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	std::cout << std::fixed;
	std::cout << std::setprecision(2);
	double total_time{};
	int dataLength = 0;
	int* data = input::data_as_int_array("Input/day1.txt", dataLength);

	total_time += benchmark_day<int, N>(data,dataLength, aoc::day1::part_1, aoc::day1::part_2, 1);
#if NDEBUG
	

#endif
	//total_time += benchmark_day<std::string, N>(input::data_as_string("Input/day25.txt"), aoc::day25::part_1, aoc::day25::part_2, 25);

	SetConsoleTextAttribute(hConsole, 2);
	std::cout << "\t~~~~~~~~~~~~~~~~~~~~~~~~ Total ~~~~~~~~~~~~~~~~~~~~~~~\n";
	SetConsoleTextAttribute(hConsole, 15);
	std::cout<< "Excl. Day 12: " << scaledTime(total_time) << unitFromNano(total_time);
#if NDEBUG
	
#endif

	return 0;
}

