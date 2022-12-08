#include "AOC_Solver.h"
#include <algorithm>
#include <numeric>
#include<iostream>
#include<omp.h>
uint64_t aoc::day8::part_1(const std::vector<std::string>& data) {
	size_t height = data.size();
	size_t widht = data[0].length();

	size_t visible = 0; //(height * 2 + widht * 2) - 4;

	int* visMap = new int[height * widht];

	#pragma omp parallel for 
	for (int i = 0; i < height*widht; ++i) {
		size_t x = i % widht, y = i / widht;
			if (y == 0 || y == height - 1 || x == 0 || x == height - 1) {

				visMap[y*widht+x] = 1;
				continue;
			}
			size_t value = data[y][x];
			bool Yn=true, Yp = true, Xn = true, Xp = true;

			for (int offset = height-1; offset >0; --offset) {
				int idxAy = y - offset;
				int idxBy = y + offset;
				int idxAx = x - offset;
				int idxBx = x + offset;

				if (idxAy > -1 && data[idxAy][x] >= value) {
					Yn = false;
				}
				if (idxBy < height && data[idxBy][x] >= value) {
					Yp = false;
				}
				if (idxAx > -1 && data[y][idxAx] >= value) {
					Xn = false;
				}
				if (idxBx < widht && data[y][idxBx] >= value) {
					Xp = false;
				}
			}
			visMap[y*widht+x] = (Yn||Yp||Xn||Xp);
	}
	
	visible = std::reduce(visMap, visMap + (height * widht));
	return visible;
}

uint64_t aoc::day8::part_2(const std::vector<std::string>& data) {
	size_t height = data.size();
	size_t widht = data[0].length();

	size_t visible = 0; //(height * 2 + widht * 2) - 4;

	int* results=new int[height* widht];
	#pragma omp parallel for shared(results)
	for (int i = 0; i < height * widht; ++i) {
		size_t x = i % widht, y = i / widht;
			if (y == 0 || y == height - 1 || x == 0 || x == height - 1) {
				results[i] = 0;
				continue;
			}

			int vYn=0, vYp=0, vXn=0, vXp=0;
			size_t value = data[y][x];

			for (int yT = y-1; yT > -1; --yT) {
				vYn++;
				if (data[yT][x] >= value)
					break;
			}

			for (int yT = y+1; yT < height; ++yT) {
					vYp++;
					if (data[yT][x] >= value)
					break;
			}

			for (int xT = x-1; xT > -1; --xT) {
					vXn++;
					if (data[y][xT] >= value)
					break;
			}

			for (int xT = x+1; xT < widht; ++xT) {
					vXp++;
					if (data[y][xT] >= value)
					break;
			}
			size_t score = vYn * vYp * vXn * vXp;
			results[i] =score;
	}
	return *std::max_element(results, results+(height*widht));
}