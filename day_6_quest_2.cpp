#include <array>
#include <fstream>
#include <iostream>
#include <set>
#include <vector>

const int HEIGHT = 130;
const int WIDTH = 130;

std::array<std::array<char, WIDTH>, HEIGHT> map{};

class Point {
public:
  int x;
  int y;

  Point() : x(0), y(0) {}
  Point(int x, int y) : x(x), y(y) {}

  bool operator==(const Point &other) const {
    return this->x == other.x && this->y == other.y;
  }

  bool operator<(const Point &other) const {
    return std::tie(x, y) < std::tie(other.x, other.y);
  }

  Point operator+(const Point &other) const {
    return Point(this->x + other.x, this->y + other.y);
  }
};

class Guard : public Point {
public:
  char direction;

  Guard() : Point(), direction('^') {}
  Guard(int x, int y, char direction) : Point(x, y), direction(direction) {}

  void move(const Point &newDirection) {
    this->x += newDirection.x;
    this->y += newDirection.y;
  }
};

bool isOutOfBounds(const Point &position) {
  return position.x < 0 || position.y < 0 || position.x >= HEIGHT ||
         position.y >= WIDTH;
}

bool doesGuardLoop(const Guard &start, const Point &newObstruction) {
  std::set<std::pair<Point, Point>> visited;
  Guard guard = start;

  std::array<Point, 4> directions = {Point(-1, 0), Point(0, 1), Point(1, 0),
                                     Point(0, -1)};

  int currentDirectionIndex = 0;

  while (true) {
    if (visited.count(
            {Point(guard.x, guard.y), directions[currentDirectionIndex]})) {
      return true;
    }
    visited.insert(
        {Point(guard.x, guard.y), directions[currentDirectionIndex]});

    Point nextPosition =
        Point(guard.x, guard.y) + directions[currentDirectionIndex];
    if (isOutOfBounds(nextPosition)) {
      break;
    }
    if (map[nextPosition.x][nextPosition.y] == '#' ||
        (nextPosition == newObstruction)) {
      currentDirectionIndex = (currentDirectionIndex + 1) % 4;
      continue;
    }
    guard.move(directions[currentDirectionIndex]);
  }

  return false;
}

std::set<Point> getPotentialObstructionPositions(const Guard &start) {
  std::set<Point> visited;
  Guard guard = start;

  std::array<Point, 4> directions = {Point(-1, 0), Point(0, 1), Point(1, 0),
                                     Point(0, -1)};

  int currentDirectionIndex = 0;
  while (true) {
    visited.insert(Point(guard.x, guard.y));
    Point nextPosition =
        Point(guard.x, guard.y) + directions[currentDirectionIndex];
    if (isOutOfBounds(nextPosition)) {
      break;
    }

    if (map[nextPosition.x][nextPosition.y] == '#') {
      currentDirectionIndex = (currentDirectionIndex + 1) % 4;
      continue;
    }
    guard.move(directions[currentDirectionIndex]);
  }

  return visited;
}

int main() {
  std::ifstream inputFile("input_day_6.txt");
  std::vector<std::string> lines;

  if (!inputFile.is_open()) {
    std::cerr << "Failed to open the input file!" << std::endl;
    return 1;
  }

  std::string line;
  int height = 0;
  while (std::getline(inputFile, line)) {
    for (int x = 0; x < line.size(); ++x) {
      map[height][x] = line[x];
    }
    lines.push_back(line);
    height++;
  }
  inputFile.close();

  Guard startGuard;
  for (int y = 0; y < HEIGHT; ++y) {
    for (int x = 0; x < WIDTH; ++x) {
      if (map[y][x] == '^') {
        startGuard = Guard(y, x, '^');
      }
    }
  }

  auto potentialObstructions = getPotentialObstructionPositions(startGuard);

  int obstructionCount = 0;
  for (const auto &obstruction : potentialObstructions) {
    if (!(obstruction == Point(startGuard.x, startGuard.y)) &&
        doesGuardLoop(startGuard, obstruction)) {
      obstructionCount++;
    }
  }

  std::cout << "Obstruction Count: " << obstructionCount << std::endl;
  return 0;
}
