#include "helpers/inputHelpers.hpp"
#include <sstream>

int main() {
  int part1 = 0;
  const int maxRed = 12;
  const int maxGreen = 13;
  const int maxBlue = 14;

  int part2 = 0;

  for (const std::string& line : getInput("inputs/day2.txt")) {
    int fewestPossibleRed = 0;
    int fewestPossibleGreen = 0;
    int fewestPossibleBlue = 0;

    std::istringstream iss(line);
    std::string game;
    std::string colon = ":";
    int id;
    iss >> game >> id >> colon;

    int amount;
    std::string color;
    while (iss >> amount >> color) {
      switch(color[0]) {
        case 'r':
          if (amount > maxRed)
            id = 0;
          fewestPossibleRed = std::max(fewestPossibleRed, amount);
          break;
        case 'g':
          if (amount > maxGreen)
            id = 0;
          fewestPossibleGreen = std::max(fewestPossibleGreen, amount);
          break;
        case 'b':
          if (amount > maxBlue)
            id = 0;
          fewestPossibleBlue = std::max(fewestPossibleBlue, amount);
          break;
      }
    }
    part1 += id;
    part2 += fewestPossibleRed * fewestPossibleGreen * fewestPossibleBlue;
  }

  std::cout << "Part 1: " << part1 << std::endl; //2162
  std::cout << "Part 2: " << part2 << std::endl; //72513
}