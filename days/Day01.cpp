#include "../helpers/inputHelpers.hpp"

int main() {
  uint64_t part1 = 0;
  uint64_t part2 = 0;

  std::vector<std::string> input = getInput("../inputs/day01.txt");

  for (const std::string& line : input) {
    //Part 1
    uint8_t firstDigit = 0;
    uint8_t lastDigit = 0;
    for (const char& c : line){
      //check if c is int:
      if (c >= '0' && c <= '9') {
        if (firstDigit == 0) {
          //Set first digit only if not set
          firstDigit = c - '0';
        }
        lastDigit = c - '0';
      }
    }
    part1 += firstDigit * 10 + lastDigit;

    //Part 2
    firstDigit = 0;
    lastDigit = 0;

    // Tried an eternity with regex (complex because of overlapping matches and c++ stuff)
    // Only to find out that c++ regex has terrible performance anyway and is commenly called "broken garbage"
    std::string digitStrings[] = {"one", "two", "three", "four", "five", "six", "seven", "eight", "nine"};
    for (uint8_t i = 0; i < line.length(); i++) {
      if (line[i] >= '0' && line[i] <= '9') {
        if (firstDigit == 0) {
          firstDigit = line[i] - '0';
        }
        lastDigit = line[i] - '0';
      }
      else {
        for (uint8_t d = 0; d < 9; d++) {
          if (line.substr(i, digitStrings[d].size()) == digitStrings[d]) {
            if (firstDigit == 0) {
              firstDigit = d + 1;
            }
            lastDigit = d + 1;
          }
        }
      }
    }

    part2 += firstDigit * 10 + lastDigit;
  }

  std::cout << "Part 1: " << part1 << std::endl; //54667
  std::cout << "Part 2: " << part2 << std::endl; //54203
}