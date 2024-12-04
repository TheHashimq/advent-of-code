#include <array>
#include <fstream>
#include <iostream>
#include <vector>

int countVertical(std::array<std::array<char, 140>, 140> &wordList);
int countHorizontal(std::array<std::array<char, 140>, 140> &wordList);
int countDiagonal(std::array<std::array<char, 140>, 140> &wordList);
int countReverseDiagonal(std::array<std::array<char, 140>, 140> &wordList);

int main(int argc, char **argv) {
  // Vars
  std::array<std::array<char, 140>, 140> arrayWordList{};
  std::vector<std::string> wordList{};
  std::string line{};
  int xmasCount{};
  // Input
  std::ifstream input("input_day_4.txt");
  while (std::getline(input, line)) {
    wordList.push_back(line);
  }
  input.close();

  for (int i = 0; i < wordList.size(); i++) {
    auto temp = wordList[i].c_str();
    for (int j = 0; j < wordList[i].size(); j++) {
      arrayWordList[i][j] = temp[j];
    }
  }
  // Process
  xmasCount += countDiagonal(arrayWordList);
  xmasCount += countHorizontal(arrayWordList);
  xmasCount += countVertical(arrayWordList);
  xmasCount += countReverseDiagonal(arrayWordList);
  // Output
  std::cout << "Xmas Count " << xmasCount << std::endl;
  return 0;
}

int countHorizontal(std::array<std::array<char, 140>, 140> &wordList) {
  int xmasCount{};
  for (int i = 0; i < wordList.size(); i++) {
    for (int j = 0; j < wordList[i].size(); j++) {
      if (j + 3 < wordList[i].size() &&
              (wordList[i][j] == 'X' && wordList[i][j + 1] == 'M' &&
               wordList[i][j + 2] == 'A' && wordList[i][j + 3] == 'S') ||
          (wordList[i][j] == 'S' && wordList[i][j + 1] == 'A' &&
           wordList[i][j + 2] == 'M' && wordList[i][j + 3] == 'X')) {
        xmasCount += 1;
      }
    }
  }
  return xmasCount;
};

int countVertical(std::array<std::array<char, 140>, 140> &wordList) {
  int xmasCount{};
  for (int i = 0; i < wordList.size(); i++) {
    for (int j = 0; j < wordList[i].size(); j++) {
      if (j + 3 < wordList.size() &&
              (wordList[j][i] == 'X' && wordList[j + 1][i] == 'M' &&
               wordList[j + 2][i] == 'A' && wordList[j + 3][i] == 'S') ||
          (wordList[j][i] == 'S' && wordList[j + 1][i] == 'A' &&
           wordList[j + 2][i] == 'M' && wordList[j + 3][i] == 'X')) {
        xmasCount += 1;
      }
    }
  }
  return xmasCount;
};

int countDiagonal(std::array<std::array<char, 140>, 140> &wordList) {
  int xmasCount{};
  for (int i = 0; i < wordList.size(); i++) {
    for (int j = 0; j < wordList[i].size(); j++) {
      if ((i + 3 < wordList.size()) && (j + 3 < wordList[i].size()) &&
              (wordList[i][j] == 'X' && wordList[i + 1][j + 1] == 'M' &&
               wordList[i + 2][j + 2] == 'A' &&
               wordList[i + 3][j + 3] == 'S') ||
          (wordList[i][j] == 'S' && wordList[i + 1][j + 1] == 'A' &&
           wordList[i + 2][j + 2] == 'M' && wordList[i + 3][j + 3] == 'X')) {
        xmasCount += 1;
      }
    }
  }
  return xmasCount;
};

int countReverseDiagonal(std::array<std::array<char, 140>, 140> &wordList) {
  int xmasCount{};
  for (int i = 0; i < wordList.size(); i++) {
    for (int j = wordList[i].size(); j > 0; j--) {
      if ((j - 3 > 0) && (i < wordList.size()) &&
              (wordList[i][j] == 'X' && wordList[i + 1][j - 1] == 'M' &&
               wordList[i + 2][j - 2] == 'A' &&
               wordList[i + 3][j - 3] == 'S') ||
          (wordList[i][j] == 'S' && wordList[i + 1][j - 1] == 'A' &&
           wordList[i + 2][j - 2] == 'M' && wordList[i + 3][j - 3] == 'X')) {
        xmasCount += 1;
      }
    }
  }
  return xmasCount;
}
