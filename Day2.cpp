#include "helpers/inputHelpers.hpp"

int main() {
  uint64_t part1 = 0;
  const uint8_t maxRed = 12;
  const uint8_t maxGreen = 13;
  const uint8_t maxBlue = 14; 

  uint64_t part2 = 0;

  std::vector<std::string> input = getInput("inputs/day2.txt");

  for (const std::string& line : input) {
    // Part 2 variables per game:
    uint16_t fewestPossibleRed = 0;
    uint16_t fewestPossibleGreen = 0;
    uint16_t fewestPossibleBlue = 0;

    // start at 5 to skip the "Game " part
    uint8_t i = 5;

    // parse the id
    uint8_t id = 0;
    for (; line[i] >= '0' && line[i] <= '9'; i++) {
      id *= 10;
      id += line[i] - '0';
    }
    
    //skip to the first number
    i += 2;
    while (i < line.length()) {
      // parse the amount drawn
      uint8_t amountDrawn = 0;
      for (;line[i] >= '0' && line[i] <= '9'; i++) {
        amountDrawn *= 10;
        amountDrawn += line[i] - '0';
      }

      // skip the ' ' after the number
      if (line[i] == ' ') {
        i++;
      }

      // parse the color
      switch (line[i]) {
        case 'g':
          //Part 1
          if (amountDrawn > maxGreen) {
            id = 0;
          } else {
            i += 7; //skip to the next number
          }
          //Part 2
          if (amountDrawn > fewestPossibleGreen) {
            fewestPossibleGreen = amountDrawn;
          }
          break;
        case 'r':
          //Part 1
          if (amountDrawn > maxRed) {
            id = 0;
          } else {
            i += 5; //skip to the next number
          }
          //Part 2
          if (amountDrawn > fewestPossibleRed) {
            fewestPossibleRed = amountDrawn;
          }
          break;
        case 'b':
          //Part 1
          if (amountDrawn > maxBlue) {
            id = 0;
          } else {
            i += 6; //skip to the next number
          }
          //Part 2
          if (amountDrawn > fewestPossibleBlue) {
            fewestPossibleBlue = amountDrawn;
          }
          break;
      }
    }
    part1 += id;
    part2 += fewestPossibleRed * fewestPossibleGreen * fewestPossibleBlue;
  }

  std::cout << "Part 1: " << part1 << std::endl; //2162
  std::cout << "Part 2: " << part2 << std::endl; //72513
}