#include "AOC_Solver.h"
#include <numeric>
#include <algorithm>
#include <iostream>

uint64_t aoc::day3::part_1(const std::vector < std::string >& data) {
	uint64_t ret = 0;
	for (int i = 0; i < data.size(); ++i) {
		int compSize = data[i].size() / 2;
		bool found = false;
		for (int comp1 = 0; comp1 < compSize&&!found; ++comp1) {

			int val1 = data[i].c_str()[comp1] - 96;
			if(val1>26||val1<1)
				val1= data[i].c_str()[comp1] - '@' +26;

			for (int comp2 = 0; comp2 < compSize; ++comp2) {

				int val2 = data[i].c_str()[comp2+compSize] - 96;
				if (val2 > 26 || val2 < 1)
					val2 = data[i].c_str()[comp2 + compSize] - '@' + 26;

				if (val1 == val2) {
					ret += val1;
					found = true;
					break;
				}
			}
		}
		

	}
	return ret;
}

uint64_t aoc::day3::part_2(const std::vector < std::string >& data) {
	uint64_t ret = 0;
	for (int i = 0; i < data.size()-2; i+=3) {
		std::string e1 = data[i];
		std::string e2 = data[i+1];
		std::string e3 = data[i+2];

		bool found = false;
		for (int e1 = 0; e1 < data[i].size()&&!found; ++e1) {

			int val1 = data[i].c_str()[e1] - 96;
			if (val1 > 26 || val1 < 1)
				val1 = data[i].c_str()[e1] - '@' + 26;

			for (int e2 = 0; e2 < data[i+1].size() && !found; ++e2) {

				int val2 = data[i+1].c_str()[e2] - 96;
				if (val2 > 26 || val2 < 1)
					val2 = data[i+1].c_str()[e2] - '@' + 26;

				if(val1==val2)
					for (int e3 = 0; e3 < data[i+2].size(); ++e3) {

						int val3 = data[i + 2].c_str()[e3] - 96;
						if (val3 > 26 || val3 < 1)
							val3 = data[i + 2].c_str()[e3] - '@' + 26;

						if (val2 == val3) {
							ret += val1;
							found = true;
							break;
						}
					}
			}
		}
	}
	return ret;
}