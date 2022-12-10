#include "AOC_Solver.h"
#include <algorithm>
#include <numeric>
#include<iostream>
#include<omp.h>
#include <unordered_set>
#include <set>

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
	int c = 1;
	std::vector<op>operations;
	long long sum = 0;
	for (int i = 0; i < data.size()||(!operations.size() == 0); ++i) {
		if (!((c - 20) % 40)) {
			sum += c * x;
			//std::cout << "Cycle " << c << " - " << ((c - 20) % 40) << " val: " << x << "\nSum: "<<sum;
		}
		//std::cout << "Cycle " << c <<" value "<< x<< ":\n";
		if(i<data.size()&&operations.empty())
		operations.push_back(data[i]);
		for (auto it = operations.begin(); it != operations.end();) {
			(*it).cycles -= 1;
			if ((*it).cycles) {
				it++;
				continue;
			}
			if (!(*it).cycles) {
				x += (*it).modifier;
				it=operations.erase(it);
				continue;
			}
		}
		//std::cout << "Value EOC: " << x<<"\n\n";
		c++;
		if (!operations.empty())
			--i;
	}
	return sum;
}

uint64_t aoc::day10::part_2(const std::vector<std::string>& data) {
	long long x = 1;
	int c = 1;
	std::vector<op>operations;
	for (int i = 0; i < data.size() || (!operations.size() == 0); ++i) {
		int index = c % 40;
#if !NDEBUG
		if (!index)
			std::cout << '\n';
		if (index) {
			if (index >= x && index <= x + 2)
				std::cout << '#';
			else
				std::cout << '.';
		}
#endif
		//std::cout << "Cycle " << c <<" value "<< x<< ":\n";
		if (i < data.size() && operations.empty())
			operations.push_back(data[i]);
		for (auto it = operations.begin(); it != operations.end();) {
			(*it).cycles -= 1;
			if ((*it).cycles) {
				it++;
				continue;
			}
			if (!(*it).cycles) {
				x += (*it).modifier;
				it = operations.erase(it);
				continue;
			}
		}
		//std::cout << "Value EOC: " << x<<"\n\n";
		c++;
		if (!operations.empty())
			--i;
	}
	return 0;
}