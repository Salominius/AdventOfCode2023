#include "../helpers/inputHelpers.hpp"

//std::abs does not work with uint32_t so I used int32_t instead
uint32_t manhattanDistance(std::pair<int32_t, int32_t> a, std::pair<int32_t, int32_t> b) {
  return std::abs(a.first - b.first) + std::abs(a.second - b.second);
}

int main() {
  uint32_t part1 = 0;
  uint64_t part2 = 0;

  std::vector<std::vector<char>> grid = getInputGrid("../inputs/day11.txt");
  uint8_t expandedXSpace[grid[0].size()] = {0};
  uint8_t expandedYSpace[grid.size()] = {0};

  // scan input columns for empty columns
  for (uint8_t x = 0; x < grid[0].size(); x++) {
    bool emptyColumn = true;
    for (uint8_t y = 0; y < grid.size(); y++) {
      if (grid[y][x] == '#') {
        emptyColumn = false;
        break;
      }
    }
    
    if (emptyColumn)
      expandedXSpace[x+1] = expandedXSpace[x] + 1;
    else 
      expandedXSpace[x+1] = expandedXSpace[x];
  }

  // scan input rows for empty rows
  for (uint8_t y = 0; y < grid.size() - 1; y++) {
    bool emptyRow = true;
    for (uint8_t x = 0; x < grid[y].size(); x++) {
      if (grid[y][x] == '#') {
        emptyRow = false;
        break;
      }
    }

    if (emptyRow)
      expandedYSpace[y+1] = expandedYSpace[y] + 1;
    else
      expandedYSpace[y+1] = expandedYSpace[y];
  }

  // get galaxies (Part 1)
  std::vector<std::pair<uint16_t, uint16_t>> galaxies;
  for (uint16_t x = 0; x < grid[0].size(); x++)
    for (uint16_t y = 0; y < grid.size(); y++)
      if (grid[y][x] == '#')
        galaxies.push_back(std::make_pair(x + expandedXSpace[x], y + expandedYSpace[y]));

  // Part 1
  for (uint16_t i = 0; i < galaxies.size(); i++)
    for (uint16_t j = i + 1; j < galaxies.size(); j++)
      part1 += manhattanDistance(galaxies[i], galaxies[j]);

  // get galaxies (Part 2)
  std::vector<std::pair<uint64_t, uint64_t>> galaxies2;
  for (uint16_t x = 0; x < grid[0].size(); x++)
    for (uint16_t y = 0; y < grid.size(); y++)
      if (grid[y][x] == '#')
        galaxies2.push_back(std::make_pair(x + expandedXSpace[x]*999'999, y + expandedYSpace[y]*999'999));

  // Part 2
  for (uint16_t i = 0; i < galaxies2.size(); i++)
    for (uint16_t j = i + 1; j < galaxies2.size(); j++)
      part2 += manhattanDistance(galaxies2[i], galaxies2[j]);

  std::cout << "Part 1: " << part1 << std::endl; //9545480
  std::cout << "Part 2: " << part2 << std::endl; //406725732046
}