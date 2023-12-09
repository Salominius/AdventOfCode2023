#include "../helpers/inputHelpers.hpp"
#include "../helpers/lists.hpp"
#include "../helpers/math.hpp"

int main() {
  int part1 = 0;
  int part2 = 0;

  std::vector<std::vector<int>> sequences = {};
  for (const string& line : getInput("../inputs/day9.txt"))
    sequences.push_back(split(line, ' '));

  for (vector<int>& sequence : sequences) {
    bool allZero = false;
    int sign = 1;
    while (!allZero) {
      //Calculate new first/last
      part1 += sequence.back();
      part2 += sequence.front() * sign;
      sign *= -1;

      //Calculate new sequence
      allZero = true;
      for (int i = 0; i < sequence.size() - 1; i++) {
        sequence[i] = sequence[i+1] - sequence[i];
        if (sequence[i] != 0)
          allZero = false;
      }
      sequence.pop_back();
    }
  }

  std::cout << "Part 1: " << part1 << std::endl; //1969958987
  std::cout << "Part 2: " << part2 << std::endl; //1068
}