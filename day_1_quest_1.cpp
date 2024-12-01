#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <vector>

int main(int argc, char **argv) {
  std::vector<int> list1{};
  std::vector<int> list2{};
  std::vector<int> distance{};
  // Input
  int temp1{}, temp2{};

  for (int i = 0; i < 1000; i++) {
    std::cin >> temp1 >> temp2;
    list1.push_back(temp1);
    list2.push_back(temp2);
  }

  // Sort
  std::sort(list1.begin(), list1.end());
  std::sort(list2.begin(), list2.end());

  int a{};
  for (int i = 0; i < list1.size(); i++) {
    a = abs(list1[i] - list2[i]);
    distance.push_back(a);
    a = 0;
  }

  int total_distance{};
  for (auto v : distance) {
    total_distance += v;
  }
  std::cout << "Total Distance " << total_distance << std::endl;
  return 0;
}
