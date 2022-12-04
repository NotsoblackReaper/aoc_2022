#include "AOC_Solver.h"
#include <numeric>
#include <algorithm>
#include <iostream>
#include<execution>

uint64_t aoc::day4::part_1(const std::vector < std::string >& data) {
	uint64_t ret = 0;
	std::vector<int> res(data.size());

	std::for_each(std::execution::par_unseq,data.begin(), data.end(), [&res,&data](auto&& s) {
		int comma = s.find(',');
		int firstDash = s.find('-'), secondDash = s.find('-', comma);

		int a1, b1, a2, b2;
		a1 = std::stoi(s.substr(0, firstDash));
		b1 = std::stoi(s.substr(firstDash + 1, comma - firstDash));
		a2 = std::stoi(s.substr(comma + 1, secondDash - comma - 1));
		b2 = std::stoi(s.substr(secondDash + 1));

		if ((a1 >= a2 && b1 <= b2) || (a2 >= a1 && b2 <= b1)) {
			int idx = &s - &data[0];
			res[idx] = 1;
			return;
		}
		});

	ret = std::reduce(res.begin(), res.end());
	return ret;
}

uint64_t aoc::day4::part_2(const std::vector < std::string >& data) {
	uint64_t ret = 0;
	std::vector<int> res(data.size());

	std::for_each(std::execution::par_unseq,data.begin(), data.end(), [&res, &data](auto&& s) {
		int comma = s.find(',');
		int firstDash = s.find('-'), secondDash = s.find('-', comma);

		int a1, b1, a2, b2;
		a1 = std::stoi(s.substr(0, firstDash));
		b1 = std::stoi(s.substr(firstDash + 1, comma - firstDash));
		a2 = std::stoi(s.substr(comma + 1, secondDash - comma - 1));
		b2 = std::stoi(s.substr(secondDash + 1));

		if (b1 < a2 || b2 < a1)return;
		int idx = &s - &data[0];
		if (b1 >= a2)res[idx] = 1;
		else if (b2 >= a1)res[idx] = 1;;
		});

	ret = std::reduce(res.begin(), res.end());
	return ret;
}