#include "AOC_Solver.h"
#include<map>
#include<iostream>
struct file {
	bool isDir=false;
	size_t size=0;
	std::string name="";

	std::map<std::string,file>content{};
	file* parent = nullptr;

	file() {};
	file(std::string name, size_t size, file* parent):name(name),size(size),parent(parent),isDir(false) {
		if (parent != nullptr) {
			parent->content.insert({ name,*this });
		}
	}

	file(std::string name, file* parent) :name(name), size(0), parent(parent), isDir(true) {
		if (parent != nullptr) {
			parent->content.insert({ name,*this });
		}
	}

	size_t getSize() const {
		if (!isDir) {
			return size;
		}
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
		if (tmp >= needed)
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
	file root{ "/",nullptr };

	file* current = &root;
	bool ls = false;
	for (int i = 1; i < data.size(); ++i) {
		if (data[i][0] == '$') {
			if (data[i].starts_with("$ ls")) {
				continue;
			}
			if (data[i].starts_with("$ cd")) {
				std::string name = data[i].substr(5);
				if (name == "..") {
					current = current->parent;
					continue;
				}
				if (current->content.contains(name)) {
					current = &(current->content[name]);
					continue;
				}
				if (name[0] == '/') {
					current = &root;
					continue;
				}

				file tmp{ name,current };
				current = &tmp;
				continue;
			}
			break;
		}

		if (data[i].starts_with("dir")) {
			std::string name = data[i].substr(4);
			file tmp{ name,current };
			continue;
		}
		size_t space = data[i].find(' ');
		size_t size = std::stoi(data[i].substr(0, space));
		std::string name = data[i].substr(space + 1);
		file f{ name,size,current };
	}
	return root;
}

uint64_t aoc::day7::part_1(const std::vector<std::string>& data) {
	file root = buildFileSystem(data);
	
	return root.getDeletableDirs(100000);
}

uint64_t aoc::day7::part_2(const std::vector<std::string>& data) {
	file root = buildFileSystem(data);
	size_t totalSize = 70000000;
	size_t neededSize = 30000000;
	size_t availableSize = totalSize - root.getSize();
	size_t minDelete = neededSize - availableSize;

	return root.getMinDelete(minDelete);
}