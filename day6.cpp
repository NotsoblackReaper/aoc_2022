#include "AOC_Solver.h"

uint64_t solve(const std::string& data, size_t n) {
	for (size_t i = n; i < data.length();++i) {
		uint32_t chars = 0;
		bool dupe = false;

		for (int j = n - 1; j > -1; --j) {
			if (chars & 0b1 << (data[i - j] - 'a')) {
				dupe = true;
				break;
			}
			chars = chars | 0b1 << (data[i - j] - 'a');
		}
		if (!dupe)
			return i + 1;
	}
	return 0;
}

uint64_t aoc::day6::part_1(const std::vector < std::string >& data) {
	return solve(data[0], 4);
}

uint64_t aoc::day6::part_2(const std::vector < std::string >& data) {
	return solve(data[0], 14);
}