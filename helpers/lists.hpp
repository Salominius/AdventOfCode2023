#include <vector>
#include <string>
#include <sstream>

template <typename T>
std::string join(const std::vector<T>& vec, const std::string& delimiter) {
  if (vec.empty())
    return "";

  std::ostringstream oss;
  auto iter = vec.begin();
  oss << *iter++;

  for (; iter != vec.end(); ++iter)
    oss << delimiter << *iter;

  return oss.str();
}

std::vector<int> split(const std::string& str, char delimiter) {
  std::vector<int> result;
  int startIndex = 0, endIndex = 0;
  for (int i = 0; i <= str.size(); i++) {
    if (str[i] == delimiter || i == str.size()) {
      endIndex = i;
      result.push_back(stoi((str.substr(startIndex, endIndex - startIndex))));
      startIndex = endIndex + 1;
    }
  }

  return result;
}