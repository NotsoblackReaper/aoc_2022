#include "AOC_Solver.h"
#include <numeric>
#include <algorithm>
#include <iostream>
#include<execution>
#include<charconv>
uint64_t aoc::day4::part_1(const std::vector < std::string >& data) {
	uint64_t ret = 0;
	std::vector<int> res(data.size());

	std::for_each(std::execution::par_unseq,data.begin(), data.end(), [&res,&data](auto&& s) {
		int comma = s.find(',');
		int firstDash = s.find('-'), secondDash = s.find('-', comma);

		int a1=0, b1=0, a2=0, b2=0;
		std::from_chars(s.data(),s.data()+firstDash,a1);
		std::from_chars(s.data() + (firstDash + 1), s.data() + comma, b1);
		std::from_chars(s.data() + (comma + 1), s.data() + secondDash, a2);
		std::from_chars(s.data() + (secondDash + 1), s.data() + s.length(), b2);
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

		int a1 = 0, b1 = 0, a2 = 0, b2 = 0;
		std::from_chars(s.data(), s.data() + firstDash, a1);
		std::from_chars(s.data() + (firstDash + 1), s.data() + comma, b1);
		std::from_chars(s.data() + (comma + 1), s.data() + secondDash, a2);
		std::from_chars(s.data() + (secondDash + 1), s.data() + s.length(), b2);

		if (b1 < a2 || b2 < a1)return;
		int idx = &s - &data[0];
		if (b1 >= a2)res[idx] = 1;
		else if (b2 >= a1)res[idx] = 1;;
		});

	ret = std::reduce(res.begin(), res.end());
	return ret;
}