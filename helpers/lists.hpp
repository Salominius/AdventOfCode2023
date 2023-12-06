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