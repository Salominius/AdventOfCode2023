#include "../helpers/inputHelpers.hpp"
#include "../helpers/lists.hpp"
#include "../helpers/math.hpp"

enum Direction { UP, RIGHT, DOWN, LEFT };

std::pair<int, int> getNextPosition(int x, int y, Direction direction) {
  switch (direction) {
    case UP:
      return {x, y - 1};
    case RIGHT:
      return {x + 1, y};
    case DOWN:
      return {x, y + 1};
    case LEFT:
      return {x - 1, y};
  }
  return {x, y}; // Should never happen but compiler is crying about it
}

Direction getNextDirection(char pipe, Direction direction) {
  switch (pipe) {
    case '|':
    case '-':
      return direction;
    case 'L':
      return direction == DOWN ? RIGHT : UP;
    case 'J':
      return direction == DOWN ? LEFT : UP;
    case '7':
      return direction == UP ? LEFT : DOWN;
    case 'F':
      return direction == UP ? RIGHT : DOWN;
  }
  return direction; // Should never happen but compiler is crying about it
}

int main() {
  int part1 = 0;
  int part2 = 0;

  std::vector<std::vector<char>> grid = getInputGrid("../inputs/day10.txt");

  size_t startX, startY;
  for (size_t y = 0; y < grid.size(); y++)
    for (size_t x = 0; x < grid[y].size(); x++)
      if (grid[y][x] == 'S') {
        startX = x;
        startY = y;
        goto start_found; // I'm sorry
      }

  start_found:
  // find out where (next to S) the pipes start
  char pipe;
  Direction direction;
  if (startY > 0) {
    pipe = grid[startY - 1][startX];
    if (pipe == '|' || pipe == '7' || pipe == 'F')
      direction = UP;
  }
  if (startX < grid[0].size() - 1) {
    pipe = grid[startY][startX + 1];
    if (pipe == '-' || pipe == '7' || pipe == 'J')
      direction = RIGHT;
  }
  if (startY < grid.size() - 1) {
    pipe = grid[startY + 1][startX];
    if (pipe == '|' || pipe == 'J' || pipe == 'F')
      direction = DOWN;
  }
  // At least 2 pipes have to end in S, so by checking 3/4 directions we can be certain to have found 1 valid pipe
  size_t steps = 1;
  auto[x, y] = getNextPosition(startX, startY, direction);
  while (pipe != 'S') {
    steps++;
    pipe = grid[y][x];
    direction = getNextDirection(pipe, direction);
    auto newPos = getNextPosition(x, y, direction);
    x = newPos.first;
    y = newPos.second;
  }
  steps++; // We have to count the last step to S

  part1 = steps/2;
  
  std::cout << "Part 1: " << part1 << std::endl; //
  std::cout << "Part 2: " << part2 << std::endl; //
}