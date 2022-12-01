#include "AOC_Methods.cuh"

	uint64_t aoc::day1::part_1(int* data, int length) {
		thrust::host_vector<int>tmp(1);
		thrust::host_vector<int>elfs(1);
		for (int i = 0; i < length; ++i) {
			if (data[i] == 0) {
				elfs.push_back(thrust::reduce(tmp.begin(), tmp.end()));
				tmp.clear();
				continue;
			}
			tmp.push_back(data[i]);
		}
		auto max = *(thrust::max_element(elfs.begin(), elfs.end()));
		return max;
	}

	uint64_t aoc::day1::part_2(int* data, int length) {
		thrust::host_vector<int>tmp(1);
		thrust::host_vector<int>elfs(1);
		for (int i = 0; i < length; ++i) {
			if (data[i] == 0) {
				elfs.push_back(thrust::reduce(tmp.begin(), tmp.end()));
				tmp.clear();
				continue;
			}
			tmp.push_back(data[i]);
		}

		thrust::sort(elfs.begin(), elfs.end());
		size_t size = elfs.size();
		int max = elfs.back() + elfs[size - 2] + elfs[size - 3];
		return max;
	}