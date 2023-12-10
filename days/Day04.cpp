#include "../helpers/inputHelpers.hpp"
#include <sstream>
#include <set>
#include <algorithm>

int main() {
  int part1 = 0;
  int part2 = 0;

  std::vector<std::string> input = getInput("../inputs/day04.txt");

  const int amountOfCards = input.size();
  int copies[amountOfCards];
  std::fill_n(copies, amountOfCards, 1);

  for (const std::string& line : input) {
    // Parsing "|" separated string doesn't work with std::stringstream
    std::string separator = "|";
    std::istringstream firstHalf(line.substr(0, line.find(separator)));
    std::istringstream secondHalf(line.substr(line.find(separator) + 1));
    
    std::string card;
    int cardID;
    std::string colon = ":";
    firstHalf >> card >> cardID >> colon;

    std::set<int> winningNumbers;
    int number;
    while (firstHalf >> number)
      winningNumbers.insert(number);

    //Part 1:
    int amountWinning = 0;
    while (secondHalf >> number)
      amountWinning += winningNumbers.count(number);

    part1 += amountWinning == 0 ? 0 : 1 << amountWinning-1; // 2^(amountWinning-1) if amountWinning > 0   (Bitwise shift operator << is faster than pow())

    //Part 2:
    cardID--; // 0-indexed
    for (int i = 1; i <= amountWinning; i++)
      copies[cardID + i] += copies[cardID];
    
    part2 += copies[cardID];
  }

  std::cout << "Part 1: " << part1 << std::endl; //23750
  std::cout << "Part 2: " << part2 << std::endl; //13261850
}
