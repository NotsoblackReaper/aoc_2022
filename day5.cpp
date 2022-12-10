#include "AOC_Solver.h"
#include <numeric>
#include <algorithm>
#include <iostream>
#include<execution>
#include<charconv>

struct operation {
	int n=0, from=0, to=0;
	operation(const std::string& s) {
		int s1 = s.find(' ', 5);
		std::from_chars(s.data() + 5, s.data() + s1, n);
		int s2 = s.find(' ', s1+6);
		std::from_chars(s.data() + (s1 + 6), s.data() + s2, from);
		std::from_chars(s.data() + (s2 + 4), s.data() + s.length(), to);
	}

	void execute(std::vector<char>& from,std::vector<char>&to) {
		for (int i = 0; i < n; ++i) {
			to.insert(to.begin(), from[i]);
		}
		from.erase(from.begin(), from.begin() + n);
	}

	void execute2(std::vector<char>& from, std::vector<char>& to) {
		for (int i = 0; i < n; ++i) {
			to.insert(to.begin(), from[n-i-1]);
		}
		from.erase(from.begin(), from.begin() + n);
	}
};

uint64_t aoc::day5::part_1(const std::vector < std::string >& data) {
	uint64_t ret = 0;
	int stacks = 0,initHeight=0;

	for (int i = 0; i < data.size(); ++i) {
		if (!data[i].empty())continue;
		stacks = data[i - 1].c_str()[data[i - 1].length() - 2] - 48;
		initHeight = i - 1;
		break;
	}

	std::vector<char>*stacklist=new std::vector<char>[stacks];
	for (int i = 0; i < stacks; ++i)stacklist[i]=std::vector<char>{};

	for (int i = 0; i < initHeight; ++i) {
		std::string curr = data[i];
		for (int j = 0,currstack=-1; j < curr.length(); ++j) {
			char val = curr.c_str()[j];
			if (!((j - 1) % 4))currstack++;
			if (val == ' ' || val == '[' || val == ']')continue;
			stacklist[currstack].push_back(val);
		}
	}

	for (int i = initHeight + 2; i < data.size(); ++i) {
		operation op{ data[i] };
		op.execute(stacklist[op.from-1],stacklist[op.to-1]);
		//std::cout << "move " << op.n << " from " << op.from << " to " << op.to << "\n";
	}

	std::string res = "";
	for (int i = 0; i < stacks; ++i) {
		res.push_back(stacklist[i].front());
	}
#if !NDEBUG
	std::cout << "Result: " << res << "\n";
#endif

	return std::hash<std::string>{}(res);
}

uint64_t aoc::day5::part_2(const std::vector < std::string >& data) {
	uint64_t ret = 0;
	int stacks = 0, initHeight = 0;

	for (int i = 0; i < data.size(); ++i) {
		if (!data[i].empty())continue;
		stacks = data[i - 1].c_str()[data[i - 1].length() - 2] - 48;
		initHeight = i - 1;
		break;
	}

	std::vector<char>* stacklist = new std::vector<char>[stacks];
	for (int i = 0; i < stacks; ++i)stacklist[i] = std::vector<char>{};

	for (int i = 0; i < initHeight; ++i) {
		std::string curr = data[i];
		for (int j = 0, currstack = -1; j < curr.length(); ++j) {
			char val = curr.c_str()[j];
			if (!((j - 1) % 4))currstack++;
			if (val == ' ' || val == '[' || val == ']')continue;
			stacklist[currstack].push_back(val);
		}
	}

	for (int i = initHeight + 2; i < data.size(); ++i) {
		operation op{ data[i] };
		op.execute2(stacklist[op.from - 1], stacklist[op.to - 1]);
		//std::cout << "move " << op.n << " from " << op.from << " to " << op.to << "\n";
	}

	std::string res = "";
	for (int i = 0; i < stacks; ++i) {
		res.push_back(stacklist[i].front());
	}
#if !NDEBUG
	std::cout << "Result: " << res << "\n";
#endif

	return std::hash<std::string>{}(res);
}