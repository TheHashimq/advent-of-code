#include <algorithm>
#include <array>
#include <iostream>
#include <vector>

int main(int argc, char **argv) {
  std::array<int, 1000> list1;
  std::array<int, 1000> list2;
  std::vector<int> similarity;

  // Input
  int temp1{}, temp2{};

  for (int i = 0; i < 1000; i++) {
    std::cin >> temp1 >> temp2;
    list1[i] = temp1;
    list2[i] = temp2;
  }
  std::sort(list1.begin(), list1.end());
  std::sort(list2.begin(), list2.end());

  int count{};
  long int similar_count{};

  for (auto v : list1) {
    for (int i = 0; i < list2.size(); i++) {
      if (v == list2[i]) {
        count += 1;
      }
    }
    similar_count = v * count;
    similarity.push_back(similar_count);
    similar_count = 0;
    count = 0;
  }

  long int similarity_score{};
  for (auto v : similarity) {
    similarity_score += v;
  }

  std::cout << "Score " << similarity_score << std::endl;
  return 0;
}
