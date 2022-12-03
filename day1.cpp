#include "AOC_Solver.h"
#include <numeric>
#include <algorithm>

uint64_t aoc::day1::part_1(const std::vector<int>& data) {
	std::vector<int>tmp(1);
	std::vector<int>elfs(1);
	for (int i = 0; i < data.size(); ++i) {
		if (data[i] == 0) {
			elfs.push_back(std::reduce(tmp.begin(), tmp.end()));
			tmp.clear();
			continue;
		}
		tmp.push_back(data[i]);
	}
	auto max = *(std::max_element(elfs.begin(), elfs.end()));
	return max;
}

uint64_t aoc::day1::part_2(const std::vector<int>& data) {
	std::vector<int>tmp(1);
	std::vector<int>elfs(1);
	for (int i = 0; i < data.size(); ++i) {
		if (data[i] == 0) {
			elfs.push_back(std::reduce(tmp.begin(), tmp.end()));
			tmp.clear();
			continue;
		}
		tmp.push_back(data[i]);
	}
	std::sort(elfs.begin(), elfs.end());
	size_t size = elfs.size();
	int max = elfs.back() + elfs[size - 2] + elfs[size - 3];
	return max;
}