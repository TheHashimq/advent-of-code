#include <cctype>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

std::vector<std::string> intermediateForm(std::vector<int> &input);
std::vector<std::string> amphipod(std::vector<std::string> &intermediate);
bool allTogther(std::vector<std::string> &amphipod);
unsigned long long int sumAll(std::vector<std::string> &amphipod);

int main() {
  // Vars
  std::ifstream inpFile("input_day_9.txt");
  std::string input{};
  std::string lineFile{};
  std::vector<int> intList{};
  // Input
  while (std::getline(inpFile, lineFile)) {
    input.append(lineFile);
  }

  for (int i = 0; i < input.size(); i++) {
    intList.push_back(input[i] - '0');
  }

  // Process
  std::vector<std::string> intermediate = intermediateForm(intList);
  std::vector<std::string> finalForm = amphipod(intermediate);
  auto sum = sumAll(finalForm);
  // OutPut
  std::cout << "Sum " << sum << std::endl;
  return 0;
}

std::vector<std::string> intermediateForm(std::vector<int> &input) {
  std::vector<std::string> res{};
  for (int i = 0; i < input.size(); i++) {
    if (i % 2 == 0) {
      for (int j = 0; j < input[i]; j++) {

        res.push_back(std::to_string(i / 2));
      }
    } else {
      for (int j = 0; j < input[i]; j++) {
        res.push_back(".");
      }
    }
  }
  return res;
}

std::vector<std::string> amphipod(std::vector<std::string> &intermediate) {
  int i = 0, j = intermediate.size() - 1;

  while (!allTogther(intermediate)) {
    while (i < intermediate.size() && intermediate[i] != ".") {
      ++i;
    }

    while (j >= 0 && intermediate[j] == ".") {
      --j;
    }

    if (i < j) {
      std::swap(intermediate[i], intermediate[j]);
    } else {
      break;
    }
  }
  return intermediate;
}

bool allTogther(std::vector<std::string> &amphipod) {
  int firstIndexOfDot = -1;

  for (int i = 0; i < amphipod.size(); ++i) {
    if (amphipod[i] == ".") {
      firstIndexOfDot = i;
      break;
    }
  }

  if (firstIndexOfDot == -1) {
    return true;
  }

  for (int i = firstIndexOfDot; i < amphipod.size(); ++i) {
    if (amphipod[i] != ".") {
      return false;
    }
  }

  return true;
}

unsigned long long int sumAll(std::vector<std::string> &amphipod) {
  unsigned long long int sum = 0;
  for (int i = 0; i < amphipod.size(); i++) {
    if (amphipod[i] != ".") {
      sum += (std::stoi(amphipod[i]))*i;
    }
  }

  return sum;
}
