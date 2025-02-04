#include <cctype>
#include <cstddef>
#include <fstream>
#include <iostream>
#include <regex>
#include <sstream>
#include <vector>

std::vector<std::string> validateMul(const std::vector<std::string> &mulList);
std::vector<std::string> findMul(const std::string &inp);
std::vector<int> get_value_from_mul(const std::vector<std::string> &mulList);

int main(int argc, char **argv) {
  std::string input{};
  std::ifstream myfile("input.txt");

  if (!myfile.is_open()) {
    std::cerr << "Error: Could not open file 'input.txt'\n";
    return 1;
  }

  std::string line;
  while (std::getline(myfile, line)) {
    input += line;
  }
  myfile.close();
  std::vector<std::string> mul_str = findMul(input);
  std::vector<std::string> validatedList = validateMul(mul_str);
  std::vector<int> multiple = get_value_from_mul(validatedList);

  long long int sum{};
  for (auto v : multiple) {
    sum += v;
  }
  std::cout << "Total Sum is " << sum << std::endl;
  return 0;
}

std::vector<std::string> validateMul(const std::vector<std::string> &mulList) {
  std::vector<std::string> validatedList;
  std::regex mulRegex(R"(\d+,\d+)");

  for (const auto &mul : mulList) {
    size_t start = mul.find('(');
    size_t end = mul.find(')');
    if (start != std::string::npos && end != std::string::npos &&
        end > start + 1) {
      std::string content = mul.substr(start + 1, end - start - 1);
      if (std::regex_match(content, mulRegex)) {
        validatedList.push_back(content);
      }
    }
  }
  return validatedList;
}

std::vector<int>
get_value_from_mul(const std::vector<std::string> &validatedList) {
  std::vector<int> multiples;
  for (const auto &v : validatedList) {
    std::stringstream ss(v);
    int num1, num2;
    char delimiter;
    ss >> num1 >> delimiter >> num2;
    if (ss && delimiter == ',') {
      multiples.push_back(num1 * num2);
    }
  }
  return multiples;
}

std::vector<std::string> findMul(const std::string &inp) {
  std::vector<std::string> res;
  std::regex mulRegex(R"(mul\(\d+,\d+\))");
  std::sregex_iterator begin(inp.begin(), inp.end(), mulRegex);
  std::sregex_iterator end;

  size_t last_end_pos = 0;
  std::string do_str = "do()";
  std::string don_tstr = "don't()";
  std::string currentValue;
  bool isDisabled = false;
  for (auto it = begin; it != end; ++it) {
    currentValue = it->str();
    size_t current_position = it->position();
    if (last_end_pos < current_position) {
      std::string between =
          inp.substr(last_end_pos, current_position - last_end_pos);
      if (between.find(don_tstr) != std::string::npos) {
        isDisabled = true;
      } else if (between.find(do_str) != std::string::npos) {
        isDisabled = false;
      }
    }
    if (!isDisabled) {
      res.push_back(it->str());
    }

    last_end_pos = current_position + currentValue.size();
  }

  return res;
}
