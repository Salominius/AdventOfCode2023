#include "../helpers/inputHelpers.hpp"
#include "../helpers/lists.hpp"

bool isPatternValid(const std::string& input, const std::vector<int>& pattern) {
  uint8_t counterOutside;
  uint8_t counterWithin;
  for (char c : input + ".") {
    if (c == '#') {
      counterWithin++;
    } else if (c == '.') {
      if (counterWithin == 0)
        continue;
      
      if (counterWithin != pattern[counterOutside])
        return false;
      
      counterOutside++;
      counterWithin = 0;
    }
  }
  
  if (counterOutside != pattern.size())
    return false;

  return true;
}

//ugly brute force:
uint16_t getCombinations (string input, const std::vector<int>& pattern) {
  size_t damagePos = input.find("?");
  if (damagePos != string::npos)
    return getCombinations(input.replace(damagePos, 1, "#"), pattern) + getCombinations(input.replace(damagePos, 1, "."), pattern);

  return isPatternValid(input, pattern);
}

int main() {
  uint16_t part1 = 0;
  uint16_t part2 = 0;

  for (const string& line : getInput("../inputs/day12.txt")) {
    string springs = line.substr(0, line.find(" "));
    std::vector<int> pattern = split(line.substr(line.find(" ") + 1), ',');
    part1 += getCombinations(springs, pattern);
  }

  std::cout << "Part 1: " << part1 << std::endl; //7251
  std::cout << "Part 2: " << part2 << std::endl; //
}