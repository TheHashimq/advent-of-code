#include <cctype>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

std::vector<std::string> intermediateForm(std::vector<int> &input);
std::vector<std::string> amphipod(std::vector<std::string> &intermediate);
unsigned long long int sumAll(std::vector<std::string> &amphipod);
int findPlace(std::vector<std::string> &intermediate, int size);

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

int findPlace(std::vector<std::string> &intermediate, int size) {
  int place = -1;

  for (int i = 0; i < intermediate.size();) {
    int count = 0;
    int start = i;

    while (i < intermediate.size() && intermediate[i] == ".") {
      ++count;
      ++i;
    }

    if (count >= size) {
      return start;
    }

    ++i;
  }

  return place;
}

std::vector<std::string> amphipod(std::vector<std::string> &intermediate) {
  int sizeOfCharacterToReplace = 0;

  for (int j = intermediate.size() - 1; j >= 0;) {
    while (j >= 0 && intermediate[j] == ".") {
      --j;
    }

    if (j < 0)
      break;

    std::string target = intermediate[j];
    int l = j;
    sizeOfCharacterToReplace = 0;

    while (l >= 0 && intermediate[l] == target) {
      ++sizeOfCharacterToReplace;
      --l;
    }

    int place = findPlace(intermediate, sizeOfCharacterToReplace);
    if (place != -1 && place < j) {
      for (int k = 0; k < sizeOfCharacterToReplace; ++k) {
        intermediate[place + k] = target;
      }
      for (int k = 0; k < sizeOfCharacterToReplace; ++k) {
        intermediate[j - k] = ".";
      }
    }
    j = l;
  }

  return intermediate;
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
