#include "AOC_Solver.h"
#include<iostream>
#include <math.h>
#include <charconv>
struct op {
	int modifier=0;
	int cycles=0;

	op(std::string cmd) {
		//std::cout << "Creating OP: " << cmd << "\n";
		if (cmd[0] == 'n') {
			modifier = 0;
			cycles = 1;
			return;
		}
		cycles = 2;
		modifier = std::stoi(cmd.substr(5));
	}
};

uint64_t aoc::day10::part_1(const std::vector<std::string>& data) {
	long long x = 1;
	long long sum = 0;
	for (int i = 0,c=1; i < data.size(); ++i) {
		if (data[i][0] == 'n') {
			if (!((c + 20) % 40))
				sum += c * x;
			c++;
			continue;
		}
		if (!((c + 20) % 40) || ((c + 20) % 40) > 38) {
			sum += ((std::ceil((c + 20) / 40.0) * 40) - 20) * x;
		}
		int mod;
		std::from_chars(data[i].data() + 5, data[i].data() + data[i].size(), mod);
		x += mod;
		c += 2;
	}
	return sum;
}

uint64_t aoc::day10::part_2(const std::vector<std::string>& data) {
	char* result = new char[6 * 40];
	long long x = 1;
	long long sum = 0;
	for (int i = 0, c = 1; i < data.size(); ++i) {
		int index = c % 40;
		if (!index)
			result[c] = '\n';
		if (index) {
			if (index >= x && index <= x + 2)
				result[c] = '#';
			else
				result[c] = ' ';
		}
		if (data[i][0] == 'n') {
			c++;
			continue;
		}
		
		index = (c+1) % 40;
		if (!index)
			result[c+1] = '\n';
		if (index) {
			if (index >= x && index <= x + 2)
				result[c+1] = '#';
			else
				result[c+1] = ' ';
		}
		int mod;
		std::from_chars(data[i].data() + 5, data[i].data() + data[i].size(), mod);
		x += mod;
		c += 2;
	}
	std::string crt{ result,6 * 40 };
#if NDEBUG
	std::ostream(0) << crt << std::endl;
#else 
	std::cout << crt << std::endl;
#endif;
	return 0;
}