#include <algorithm>
#include <array>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

std::vector<std::string> replace_comman(const std::vector<std::string> &input);
std::vector<std::vector<int>>
get_ordered_pages(std::vector<std::vector<int>> &pagingList,
                  std::vector<std::array<int, 2>> &pagingOrder);
int get_middle_page_sum(std::vector<std::vector<int>> &orderedPages);
std::vector<std::array<int, 2>>
get_order_rules(std::vector<int> &v, std::vector<std::array<int, 2>> &c);
bool is_ordered(std::vector<int> &update,
                std::vector<std::array<int, 2>> &rules);

bool is_ordered(std::vector<int> &v, std::array<int, 2> &c);
bool vector_has(const std::vector<int> &v, const int &x);

int main(int argc, char **argv) {
  // Vars
  std::string line{};
  std::vector<std::string> inputList{};
  std::vector<std::string> inputList2{};
  std::vector<std::array<int, 2>> pagingOrder{};
  std::vector<std::vector<int>> pagingList{};

  // Input
  std::ifstream input("input_day_5_1.txt");
  while (std::getline(input, line)) {
    inputList.push_back(line);
  }
  input.close();
  std::ifstream input2("input_day_5_2.txt");
  while (std::getline(input2, line)) {
    inputList2.push_back(line);
  }

  int num1{}, num2{};
  char delimiter{};
  for (const auto &v : inputList) {
    std::istringstream ss(v);
    ss >> num1 >> delimiter >> num2;
    pagingOrder.push_back({num1, num2});
  }
  inputList2 = replace_comman(inputList2);

  std::vector<int> temp{};
  for (const auto &v : inputList2) {
    std::istringstream iss(v);
    for (int i = 0; i < v.size(); i++) {
      while (iss >> num1) {
        temp.push_back(num1);
      }
    }
    pagingList.push_back(temp);
    temp.erase(temp.begin(), temp.end());
  }

  // Process
  std::vector<std::vector<int>> orderedPages =
      get_ordered_pages(pagingList, pagingOrder);
  int middle_sum = get_middle_page_sum(orderedPages);
  // Output
  std::cout << "Sum of Middle Pages of ordered pages = " << middle_sum
            << std::endl;
  return 0;
}

std::vector<std::string> replace_comman(const std::vector<std::string> &input) {
  std::vector<std::string> outList{};
  std::string intString{};
  for (auto v : input) {
    auto cstr = v.c_str();
    for (int i = 0; i < v.size(); i++) {
      if (cstr[i] == ',') {
        intString += ' ';
      } else {
        intString += cstr[i];
      }
    }
    outList.push_back(intString);
    intString = " ";
  }
  return outList;
}

std::vector<std::vector<int>>
get_ordered_pages(std::vector<std::vector<int>> &pagingList,
                  std::vector<std::array<int, 2>> &pagingOrder) {
  std::vector<std::vector<int>> orderedPages;
  std::vector<std::array<int, 2>> orderRules;
  for (auto &v : pagingList) {
    orderRules = get_order_rules(v, pagingOrder);

    if (is_ordered(v, orderRules)) {
      orderedPages.push_back(v);
    }
  }
  return orderedPages;
}

std::vector<std::array<int, 2>>
get_order_rules(std::vector<int> &pagingList,
                std::vector<std::array<int, 2>> &pagingOrder) {
  std::vector<std::array<int, 2>> orderRules{};
  for (const auto &v : pagingOrder) {
    if (vector_has(pagingList, v[0]) && vector_has(pagingList, v[1])) {
      orderRules.push_back(v);
    }
  }
  return orderRules;
}

bool is_ordered(std::vector<int> &update,
                std::vector<std::array<int, 2>> &rules) {
  for (const auto &rule : rules) {
    int x = rule[0], y = rule[1];
    auto posX = std::find(update.begin(), update.end(), x);
    auto posY = std::find(update.begin(), update.end(), y);
    if (posX != update.end() && posY != update.end() && posX > posY) {
      return false;
    }
  }
  return true;
}

bool vector_has(const std::vector<int> &v, const int &x) {
  for (const auto &c : v) {
    if (c == x) {
      return true;
    }
  }
  return false;
}

int get_middle_page_sum(std::vector<std::vector<int>> &orderedPages) {
  int middle_sum{};
  for (const auto &v : orderedPages) {
    middle_sum += v[v.size() / 2];
  }
  return middle_sum;
}
