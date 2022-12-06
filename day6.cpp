#include "AOC_Solver.h"
#include <numeric>
#include <algorithm>
#include <iostream>
#include<execution>
#include<map>

uint64_t aoc::day6::part_1(const std::vector < std::string >& data) {
	uint64_t ret = 0;
	
	const char* s = data[0].c_str();

	for (int i = 3; i < data[0].length(); ++i) {
		std::map<char, int>chars{};

		chars.emplace(s[i - 3], 1);
		chars.emplace(s[i - 2], 1);
		chars.emplace(s[i - 1], 1);
		chars.emplace(s[i], 1);

		if(chars.size()==4)
			return i+1;
	}

	return ret;
}

uint64_t aoc::day6::part_2(const std::vector < std::string >& data) {
	uint64_t ret = 0;

	const char* s = data[0].c_str();

	for (int i = 3; i < data[0].length(); ++i) {
		std::map<char, int>chars{};

		for(int j=13;j>-1;--j)
			chars.emplace(s[i - j], 1);

		if (chars.size() == 14)
			return i + 1;
	}

	return ret;
}