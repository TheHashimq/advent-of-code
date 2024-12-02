#include <array>
#include <cctype>
#include <cstdlib>
#include <iostream>
#include <sstream>
#include <vector>

bool is_safe(const std::vector<int> &list);
bool is_increasing(const std::vector<int> &list);
bool is_decreasing(const std::vector<int> &list);

int main(int argc, char **argv) {

  std::array<std::vector<int>, 1000> list;
  int inp{};
  int safe_count{};

  for (int i = 0; i < 1000; i++) {
    std::string line;
    if (!std::getline(std::cin, line)) { // Read the entire line
      std::cerr << "Error reading input. Terminating." << std::endl;
      break;
    }
    std::istringstream input(line);
    int number{};
    while (input >> number) {
      list[i].push_back(number);
    }
  }

  std::cout << "----------------------DONE-------------------" << std::endl;
  std::cout << "----------------------DONE-------------------" << std::endl;

  for (auto v : list) {
    for (auto i : v) {
      std::cout << i << " ";
    }
    std::cout << std::endl;
  }

  std::cout << "----------------------DONE-------------------" << std::endl;
  std::cout << "----------------------DONE-------------------" << std::endl;
  std::cout << "Done " << std::endl;
  for (auto v : list) {
    if (is_safe(v) && (is_increasing(v) || is_decreasing(v))) {
      for (auto i : v) {
        std::cout << i << " ";
      }
      std::cout << std::endl;
      safe_count += 1;
    }
  }

  std::cout << "Safe Count " << safe_count << std::endl;
  return 0;
}

bool is_increasing(const std::vector<int> &list) {
  for (size_t i = 0; i < list.size() - 1; ++i) {
    if (list[i] >= list[i + 1]) { // Ensure strictly increasing
      return false;
    }
  }
  return true;
}

bool is_decreasing(const std::vector<int> &list) {
  for (size_t i = 0; i < list.size() - 1; ++i) {
    if (list[i] <= list[i + 1]) { // Ensure strictly decreasing
      return false;
    }
  }
  return true;
}

bool is_safe(const std::vector<int> &list) {
  for (size_t i = 0; i < list.size() - 1; ++i) { // Compare consecutive elements
    if (std::abs(list[i] - list[i + 1]) > 3) {
      return false;
    }
  }
  return true;
}
