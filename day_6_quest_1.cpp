#include <array>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

// Global Vars
const int HEIGHT = 130;
const int WIDTH = 130;
char guard_CHARACTER{};
std::array<std::array<char, WIDTH>, HEIGHT> map{};
std::array<int, 2> guardPosition{};
// Function Declarations
std::array<int, 2> findguardPosition();
void guardMove();
void printMap();
int countVisitedPosition();

int main(int argc, char **argv) {
  // Vars
  std::vector<std::string> input{};
  std::string inputLine{};
  int distinctPositionVisited{};

  // Input
  std::ifstream inp("input_day_6.txt");
  while (std::getline(inp, inputLine)) {
    input.push_back(inputLine);
  }
  inp.close();

  for (int i = 0; i < input.size(); i++) {
    auto cline = input[i].c_str();
    auto size = input[i].size();
    for (int j = 0; j < size; j++) {
      map[i][j] = cline[j];
    }
  }

  // Process
  guardPosition = findguardPosition();
  std::cout << "Found Guard at" << guardPosition[0] << " " << guardPosition[1]
            << std::endl;

  /*
  for (int i = 0; i < 40; i++) {

    guardMove();
    printMap();
  };
  */
  while (guardPosition[0] >= 0 && guardPosition[0] < HEIGHT &&
         guardPosition[1] >= 0 && guardPosition[1] < WIDTH) {
    guardMove();
  }

  printMap();
  distinctPositionVisited = countVisitedPosition();
  // Output
  std::cout << "Distinct Position Visited by Guard = "
            << distinctPositionVisited << std::endl;
  return 0;
}

std::array<int, 2> findguardPosition() {
  for (int i = 0; i < map.size(); i++) {
    for (int j = 0; j < map[i].size(); j++) {
      if (map[i][j] == '^') {
        guardPosition[0] = i;
        guardPosition[1] = j;
        std::cout << "Going up" << std::endl;
        guard_CHARACTER = '^';
        break;
      }
      if (map[i][j] == 'v') {
        guardPosition[0] = i;
        guardPosition[1] = j;
        std::cout << "Going Down " << std::endl;
        guard_CHARACTER = 'v';
        break;
      }
      if (map[i][j] == '>') {
        guardPosition[0] = i;
        guardPosition[1] = j;
        std::cout << "Going Right " << std::endl;
        guard_CHARACTER = '>';
        break;
      }
      if (map[i][j] == '<') {
        guardPosition[0] = i;
        guardPosition[1] = j;
        std::cout << "Going Left " << std::endl;
        guard_CHARACTER = '<';
        break;
      }
    }
  }
  return guardPosition;
}

void guardMove() {
  auto x = guardPosition[0];
  auto y = guardPosition[1];

  map[x][y] = 'X';
  if (guard_CHARACTER == '^' && (map[x - 1][y] != '#')) {
    guard_CHARACTER = '^';
    x -= 1;
  } else if (guard_CHARACTER == '^' && (map[x - 1][y] == '#')) {
    guard_CHARACTER = '>';
  }
  if (guard_CHARACTER == 'v' && (map[x + 1][y] != '#')) {
    guard_CHARACTER = 'v';
    x += 1;
  } else if (guard_CHARACTER == 'v' && (map[x + 1][y] == '#')) {
    guard_CHARACTER = '<';
  }

  if (guard_CHARACTER == '>' && (map[x][y + 1] != '#')) {
    guard_CHARACTER = '>';
    y += 1;
  } else if (guard_CHARACTER == '>' && (map[x][y + 1] == '#')) {
    guard_CHARACTER = 'v';
  }

  if (guard_CHARACTER == '<' && (map[x][y - 1] != '#')) {
    guard_CHARACTER = '<';
    y -= 1;
  } else if (guard_CHARACTER == '<' && (map[x][y - 1] == '#')) {
    guard_CHARACTER = '^';
  }

  guardPosition[0] = x;
  guardPosition[1] = y;
}

void printMap() {
  for (auto line : map) {
    for (auto chars : line) {
      std::cout << chars;
    }
    std::cout << '\n';
  }
}

int countVisitedPosition() {
  int visitedCount{};
  for (auto v : map) {
    for (auto c : v) {
      if (c != '.' && c != '#') {
        visitedCount += 1;
      }
    }
  }
  return visitedCount;
}
