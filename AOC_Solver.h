#ifndef AOC_SOLVER
#define AOC_SOLVER

#include <string>
#include <vector>

namespace input {
	std::vector<std::string> data_as_string(const char*);
	std::vector<int> data_as_int(const char*);
	std::vector<int> data_as_csv_int(const char*);
}
#endif