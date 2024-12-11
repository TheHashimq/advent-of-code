#include <cstdint>
#include <fstream>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

std::vector<long long int> blink(std::vector<long long int> &list, int i);

int main() {
  // Vars
  std::vector<long long int> list{};
  std::string line{};
  long int result{};
  // Input
  std::ifstream ifs("input_day_11.txt");
  std::getline(ifs, line);

  std::stringstream iss(line);
  long long int num{};
  while (iss >> num) {
    list.push_back(num);
  }

  // Process
  int i = 0;
  while (i < 25) {
    list = blink(list, i);
    i++;
  }
  result = list.size();
  // Output
  std::cout << "Output = " << result << std::endl;
  return 0;
}

std::vector<long long int> blink(std::vector<long long int> &list, int i) {
  std::vector<long long int> out;
  for (auto v : list) {
    if (v == 0) {
      out.push_back(1);
    } else {
      std::string temp = std::to_string(v);
      auto size = temp.size();
      if (size % 2 == 0) {

        auto tmp1 = temp.substr(0, size / 2);
        auto tmp2 = temp.substr(size / 2, size);
        if (std::stoi(tmp1) < 0)
          tmp1 = std::to_string(std::stoull(tmp1) * (-1));
        if (std::stoi(tmp2) < 0)
          tmp2 = std::to_string(std::stoi(tmp2) * (-1));
        try {
          out.push_back(std::stoull(tmp1));
          out.push_back(std::stoull(tmp2));
        } catch (const std::invalid_argument &e) {
          std::cerr << "Error Converting string to interger : " << temp
                    << " temp 1 " << tmp1 << " temp 2 = " << tmp2
                    << " Iteration = " << i << '\n';
        }
      } else {
        try {
          out.push_back((std::stoull(temp) * 2024));
        } catch (const std::invalid_argument &e) {
          std::cerr << "Error Converting string to interger : " << temp << '\n';
        }
      }
    }
  }
  return out;
}
