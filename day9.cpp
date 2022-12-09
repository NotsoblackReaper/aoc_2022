#include "AOC_Solver.h"
#include <algorithm>
#include <numeric>
#include<iostream>
#include<omp.h>
#include <unordered_set>
#include <set>

uint64_t aoc::day9::part_1(const std::vector<std::string>& data) {
	std::set<std::pair<int, int>>tailPos{};
	tailPos.insert({0,0});
	int hX = 0, hY = 0, tX = 0, tY = 0;
	for (size_t i = 0; i < data.size(); ++i) {
		char dir = data[i][0];
		size_t count = std::stoull(data[i].substr(2));
		int dX = 0, dY = 0;
		switch (dir)
		{
		case 'R':
			dX = 1;
			break;
		case 'L':
			dX = -1;
			break;
		case 'U':
			dY = -1;
			break;
		case 'D':
			dY = 1;
			break;
		}
		for (size_t j = 0; j < count; ++j) {
			hX += dX;
			hY += dY;
			if (hY == tY) {
				if ((hX - tX) * (hX - tX) > 1) {
					tX += dX;
				}
			}
			if (hX == tX) {
				if ((hY - tY) * (hY - tY) > 1) {
					tY += dY;
				}
			}
			if (hX != tX && hY != tY) {
				if ((hY - tY) * (hY - tY) > 1) {
					tY += dY;
					tX += (hX > tX ? 1 : -1);
				}
				if ((hX - tX) * (hX - tX) > 1) {
					tX += dX;
					tY += (hY > tY ? 1 : -1);
				}
			}
			tailPos.insert({tX,tY});
		}
	}

	return tailPos.size();
}

uint64_t aoc::day9::part_2(const std::vector<std::string>& data) {
	std::set<std::pair<int, int>>tailPos{};
	tailPos.insert({ 0,0 });
	std::vector< std::pair<int, int>>knots(10);
	for (int i = 0; i < 10; ++i)knots[i]={ 0,0 };
	for (size_t i = 0; i < data.size(); ++i) {
		char dir = data[i][0];
		size_t count = std::stoull(data[i].substr(2));
		int dX = 0, dY = 0;
		switch (dir)
		{
		case 'R':
			dX = 1;
			break;
		case 'L':
			dX = -1;
			break;
		case 'U':
			dY = -1;
			break;
		case 'D':
			dY = 1;
			break;
		}

		for (size_t j = 0; j < count; ++j) {
			knots[0].first += dX;
			knots[0].second += dY;

			for (size_t k = 1; k < 10; ++k) {
				int hX = knots[k - 1].first, hY = knots[k - 1].second;
				int tX = knots[k].first, tY = knots[k].second;

				if (hY == tY) {
					if ((hX - tX) * (hX - tX) > 1) {
						tX += (hX > tX ? 1 : -1);;
					}
				}
				if (hX == tX) {
					if ((hY - tY) * (hY - tY) > 1) {
						tY += (hY > tY ? 1 : -1);;
					}
				}
				if (hX != tX && hY != tY) {
					if ((hY - tY) * (hY - tY) > 1) {
						tY += (hY > tY ? 1 : -1);
						tX += (hX > tX ? 1 : -1);
					}
					if ((hX - tX) * (hX - tX) > 1) {
						tX += (hX > tX ? 1 : -1);
						tY += (hY > tY ? 1 : -1);
					}
				}

				knots[k] = { tX,tY };
			}
			tailPos.insert({ knots.back().first,knots.back().second});
		}
	}

	return tailPos.size();
}