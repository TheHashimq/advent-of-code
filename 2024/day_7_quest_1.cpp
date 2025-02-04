#include <algorithm>
#include <fstream>
#include <iostream>
#include <sstream>
#include <stack>
#include <string>
#include <vector>

//
//
//
// NOTE : Please use this code with limited about of input like :200-300 lines
// 	 if your input is more than that please do it in parts :cries:
// 	 i will learn more and make it better!.
//
//
//
//
typedef unsigned long long int ull;
// Declarations
std::vector<std::vector<ull>>
validCalibration(std::vector<std::vector<ull>> &vec);
bool isValid(std::vector<ull> &vec);
std::vector<std::vector<char>> findPermutations(const int &size);
ull totalValidCalibrations(std::vector<std::vector<ull>> &validCalib);

int main() {
  // Vars
  std::string line{};
  std::vector<std::string> vecInput{};
  ull totalCalibrationResult{};
  std::vector<std::vector<ull>> inp{};
  // Input
  std::ifstream input("input_day_7.txt");
  while (std::getline(input, line)) {
    vecInput.push_back(line);
  }
  for (auto &v : vecInput) {
    v = v.c_str();
    for (int i = 0; i < static_cast<int>(v.size()); i++) {
      if (v[i] == ':') {
        v[i] = ' ';
      }
    }
  }
  ull num{};
  for (auto v : vecInput) {
    std::istringstream iss(v);
    std::vector<ull> intline{};
    while (iss >> num) {
      intline.push_back(num);
    }
    inp.push_back(intline);
  }

  // Process
  std::vector<std::vector<ull>> validCalib = validCalibration(inp);

  totalCalibrationResult = totalValidCalibrations(validCalib);
  // Output
  std::cout << "The Total Calibration Result = " << totalCalibrationResult
            << std::endl;
  return 0;
}

std::vector<std::vector<char>> findPermutations(const int &size) {
  std::vector<std::vector<char>> permutations{};
  std::vector<char> character{};
  for (int i = 0; i < size; i++) {
    character.push_back('*');
    character.push_back('+');
  }
  std::sort(character.begin(), character.end());
  do {
    permutations.push_back(character);
  } while (std::next_permutation(character.begin(), character.end()));
  for (auto &v : permutations) {
    v.erase(v.begin() + v.size() / 2, v.end());
  }
  return permutations;
}

bool isValid(std::vector<ull> &vec) {
  ull out = vec[0];
  std::vector<std::vector<char>> permutations =
      findPermutations(vec.size() - 2);
  std::stack<ull> stk;

  for (int i = vec.size() - 1; i > 0; i--) {
    stk.push(vec[i]);
  }

  auto tempStk = stk;

  for (auto v : permutations) {
    ull Result{};
    stk = tempStk;
    bool validPermutation = true;
    for (auto c : v) {
      if (stk.size() < 2) {
        validPermutation = false;
        break;
      }

      ull operand1 = stk.top();
      stk.pop();
      ull operand2 = stk.top();
      stk.pop();

      switch (c) {
      case '*':
        Result = operand1 * operand2;
        break;
      case '+':
        Result = operand1 + operand2;
        break;
      }
      stk.push(Result);
    }

    if (validPermutation && Result == out) {
      return true;
    }
  }
  return false;
}

/*
bool isValid(std::vector<ull> &vec) {
  ull out = vec[0];
  std::vector<std::vector<char>> permutations =
      findPermutations(vec.size() - 2);
  std::stack<ull> stk;
  for (int i = vec.size() - 1; i > 0; i--) {
    stk.push(vec[i]);
  }
  auto tempStk = stk;

  for (auto v : permutations) {
    ull Result{};
    for (auto c : v) {
      ull operand1 = stk.top();
      stk.pop();
      ull operand2 = stk.top();
      stk.pop();
      switch (c) {
      case '*':
        Result = operand1 * operand2;
        break;
      case '+':
        Result = operand1 + operand2;
        break;
      }
      stk.push(Result);
    }
    if (Result == out) {
      return true;
    }
    stk = tempStk;
  }
  return false;
}

*/
std::vector<std::vector<ull>>
validCalibration(std::vector<std::vector<ull>> &vec) {
  std::vector<std::vector<ull>> validCalib{};
  for (auto v : vec) {
    if (isValid(v)) {
      validCalib.push_back(v);
    }
  }
  return validCalib;
}

ull totalValidCalibrations(std::vector<std::vector<ull>> &validCalib) {
  ull total{};

  for (auto v : validCalib) {
    total += v[0];
  }
  return total;
}
