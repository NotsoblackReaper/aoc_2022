#include "AOC_Solver.h"
#include<map>
#include<iostream>
#include <charconv>
struct file {
	bool isDir=false;
	size_t size=0;
	size_t name=0;

	std::map<size_t,file>content{};
	file* parent = nullptr;

	file() {};
	file(size_t name, size_t size, file* parent):name(name),size(size),parent(parent),isDir(false) {
		if (parent != nullptr) {
			parent->content.insert({ name,*this });
		}
	}

	file(size_t name, file* parent) :name(name), size(0), parent(parent), isDir(true) {
		if (parent != nullptr) {
			parent->content.insert({ name,*this });
		}
	}

	size_t getSize() const {
		if (size > 0)
			return size;
		size_t total = 0;
		for (const auto& [key, value] : content)
			total += value.getSize();
		return total;
	}

	void print(std::string prefix) const {
		std::cout << prefix<<"- " << name << " (" << (isDir ? "dir" : "file")
			<< ", size=" << getSize()<<")\n";
		if (isDir) {
			for (const auto& [key, value] : content)
				value.print(prefix + "\t");
		}
	}

	size_t getDeletableDirs(size_t limit) const {
		size_t total=0;

		size_t tmp = getSize();
		if (tmp <= limit)
			total += tmp;
		for (const auto& [key, value] : content)
			if(value.isDir)
				total += value.getDeletableDirs(limit);

		return total;
	}

	size_t getMinDelete(size_t needed) const {
		size_t total = SIZE_MAX;

		size_t tmp = getSize();
		if (tmp <= needed)
			return total;
			total = tmp;

		for (const auto& [key, value] : content)
			if (value.isDir) {
				size_t tmp = value.getMinDelete(needed);
				if (tmp <= total)
					total = tmp;
			}

		return total;
	}
};

file buildFileSystem(const std::vector<std::string>& data) {
	auto hasher = std::hash<std::string>();
	file root{ hasher("/"),nullptr};
	file* current = &root;
	bool ls = false;
	for (int i = 1; i < data.size(); ++i) {
		if (data[i][0] == '$') {
			if (data[i][2]=='l') 
				continue;
			if (data[i][2]=='c') {
				if (data[i][5] == '.') {
					current = current->parent;
					continue;
				}
				if (data[i][5] == '/') {
					current = &root;
					continue;
				}
				auto hash = hasher(data[i].substr(5));
				if (current->content.contains(hash)) {
					current = &(current->content[hash]);
					continue;
				}
				file tmp{ hash,current };
				current = &tmp;
				continue;
			}
			break;
		}

		if (data[i][0]=='d') {
			auto hash = hasher(data[i].substr(4));
			file tmp{ hash,current };
			continue;
		}
		size_t space = data[i].find(' ');
		size_t size=0;
		std::from_chars(data[i].data(), data[i].data() +space, size);
		auto hash = hasher(data[i].substr(space + 1));
		file f{ hash,size,current };
	}
	return root;
}

uint64_t aoc::day7::part_1(const std::vector<std::string>& data) {
	file root = buildFileSystem(data);
	
	return root.getDeletableDirs(100000);
}

uint64_t aoc::day7::part_2(const std::vector<std::string>& data) {
	file root = buildFileSystem(data);
	size_t minDelete = 30000000 - (70000000 - root.getSize());

	return root.getMinDelete(minDelete);
}