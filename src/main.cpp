#include <format>
#include <iostream>
#include <random>
#include <sstream>
#include <unordered_map>
#include <vector>

using namespace std;

class RandomizedSet {
 public:
  RandomizedSet() { mt = mt19937(rd()); }

  bool insert(int val) {
    if (elementIndices.contains(val)) {
      return false;
    }
    elementIndices[val] = elements.size();
    elements.push_back(val);
    return true;
  }

  bool remove(int val) {
    if (!elementIndices.contains(val)) {
      return false;
    }

    auto ind = elementIndices[val];
    elements[ind] = elements[elements.size() - 1];
    elementIndices[elements[ind]] = ind;
    elementIndices.erase(val);
    elements.pop_back();

    return true;
  }

  int getRandom() {
    auto ud = std::uniform_int_distribution<>(0, elements.size() - 1);
    auto randIndex = ud(mt);
    return elements.at(randIndex);
  }

 private:
  std::unordered_map<int, int> elementIndices;
  std::vector<int> elements;

  std::random_device rd;
  std::mt19937 mt;
};

template <typename T>
string to_string(const std::vector<T>& vec) {
  auto oss = std::ostringstream();

  if (vec.empty()) {
    oss << "[]";
    return oss.str();
  }
  oss << format("[ {}", vec[0]);

  bool dotes = false;
  for (size_t i = 1; i < vec.size(); ++i) {
    if (vec.size() > 10 && i >= 5 && i < vec.size() - 5) {
      if (!dotes) {
        oss << ", ...";
        dotes = true;
      }
      continue;
    }
    oss << format(", {}", vec[i]);
  }
  oss << " ]";

  return oss.str();
}

int main() {
  auto rs = RandomizedSet();
  std::cout << rs.insert(1) << ' ';
  std::cout << rs.remove(2) << ' ';
  std::cout << rs.insert(2) << ' ';
  std::cout << rs.getRandom() << ' ';
  std::cout << rs.getRandom() << ' ';
  std::cout << rs.getRandom() << ' ';
  std::cout << rs.remove(1) << ' ';
  std::cout << rs.insert(2) << ' ';
  std::cout << rs.getRandom() << '\n';

  return 0;
}
