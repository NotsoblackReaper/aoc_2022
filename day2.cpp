#include "AOC_Solver.h"
#include <numeric>
#include <algorithm>

uint64_t aoc::day2::part_1(const std::vector < std::string > & data) {
	uint64_t ret = 0;
	for (int i = 0; i < data.size(); ++i) {
		int e = data[i].c_str()[0] - '@', p = data[i].c_str()[2] - 'W';
		ret += p;
		if (e == 1 && p == 2 || e == 2 && p == 3 || e == 3 && p == 1)
			ret += 6;
		if (e == p)ret += 3;
	}
	return ret;
}

uint64_t aoc::day2::part_2(const std::vector < std::string >& data) {
	uint64_t ret = 0;
	for (int i = 0; i < data.size(); ++i) {
		int e = data[i].c_str()[0] - '@', p = data[i].c_str()[2] - 'W';
		if (p == 2) {
			ret += 3+e;
			continue;
		}
		if (p == 3) {
			ret += 6+((e%3)+1);
			continue;
		}
		ret += ((e + 1) % 3) + 1;
	}
	return ret;
}