#include <array>
#include <fstream>
#include <iostream>
#include <vector>

int countXMAS(std::array<std::array<char, 140>, 140> &wordList);

int main(int argc, char **argv) {
  // Vars
  std::array<std::array<char, 140>, 140> arrayWordList{};
  std::vector<std::string> wordList{};
  std::string line{};
  int x_masCount{};
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
  x_masCount = countXMAS(arrayWordList);
  // Output
  std::cout << "Xmas Count " << x_masCount << std::endl;
  return 0;
}

int countXMAS(std::array<std::array<char, 140>, 140> &wl) {
  int x_masCount{};
  for (int i = 1; i < wl.size() - 1; i++) {
    for (int j = 1; j < wl[i].size() - 1; j++) {
      if (wl[i][j] == 'A') {
        if ((i - 1) >= 0 && (i + 1) <= wl.size() && (j - 1) >= 0 &&
            (j + 1) <= wl[i].size() &&
            // M M
            //  A
            // S S
            ((wl[i - 1][j - 1] == 'M' && wl[i + 1][j + 1] == 'S' &&
              wl[i - 1][j + 1] == 'M' && wl[i + 1][j - 1] == 'S') ||
             // M S
             //  A
             // M S
             (wl[i - 1][j - 1] == 'M' && wl[i + 1][j + 1] == 'S' &&
              wl[i - 1][j + 1] == 'S' && wl[i + 1][j - 1] == 'M') ||
             // S S
             //  A
             // M M
             (wl[i - 1][j - 1] == 'S' && wl[i + 1][j + 1] == 'M' &&
              wl[i - 1][j + 1] == 'S' && wl[i + 1][j - 1] == 'M') ||
             // S M
             //  A
             // S M
             (wl[i - 1][j - 1] == 'S' && wl[i + 1][j + 1] == 'M' &&
              wl[i - 1][j + 1] == 'M' && wl[i + 1][j - 1] == 'S'))) {
          x_masCount += 1;
        }
      }
    }
  }
  return x_masCount;
}
