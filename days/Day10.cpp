#include "../helpers/inputHelpers.hpp"
#include "../helpers/lists.hpp"
#include "../helpers/math.hpp"
#include <tuple>
#include <set>

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
    if (pipe == '|' || pipe == 'J' || pipe == 'L')
      direction = DOWN;
  }
  // At least 2 pipes have to end in S, so by checking 3/4 directions we can be certain to have found a valid pipe

  Direction startDirection = direction; // Save start direction for part 2

  size_t steps = 1;
  auto[x, y] = getNextPosition(startX, startY, direction); // x, y are now the position of the first pipe
  pipe = grid[y][x];

  std::set<std::pair<int, int>> mainLoop = {std::make_pair(x, y)}; // Find positions of main loop for part 2

  // Follow the pipe until we reach the end
  while (pipe != 'S') {
    steps++;
    direction = getNextDirection(pipe, direction);
    std::tie(x, y) = getNextPosition(x, y, direction);
    mainLoop.insert(std::make_pair(x, y)); // Find positions of main loop for part 2
    pipe = grid[y][x];
  }

  Direction endDirection = direction; // Save end direction for part 2

  part1 = steps/2;

  // A bit messy, but we need to know what kind of pipe S is for the following algorithm to work
  if ((startDirection == RIGHT && endDirection == DOWN) || (startDirection == UP && endDirection == LEFT))
    grid[startY][startX] = 'L';
  else if ((startDirection == RIGHT && endDirection == UP) || (startDirection == DOWN && endDirection == LEFT))
    grid[startY][startX] = 'F';
  else if ((startDirection == LEFT && endDirection == DOWN) || (startDirection == UP && endDirection == RIGHT))
    grid[startY][startX] = 'J';
  else if ((startDirection == LEFT && endDirection == UP) || (startDirection == DOWN && endDirection == RIGHT))
    grid[startY][startX] = '7';
  else if (startDirection == RIGHT)
    grid[startY][startX] = '-';
  else
    grid[startY][startX] = '|';

  // Part 2
  for (size_t y = 0; y < grid.size(); y++) {
    bool inLoop = false; // Left border can't be enclosed by loop
    char previous = ' '; // Track L-7 and F-J which should count as |  (just one toggle of inLoop)
    for (size_t x = 0; x < grid[y].size(); x++) {
      if (!mainLoop.count(std::make_pair(x, y))) {
        if (inLoop)
          part2++; // count tile if inLoop and not part of the loop itself
        continue;
      }

      char tile = grid[y][x];
      if (tile == '|')
        inLoop = !inLoop;
      else if (tile == 'L' || tile == 'F')
        previous = tile;
      else if (tile == '7' || tile == 'J')
        if (previous + tile == 'L' + '7' || previous + tile == 'F' + 'J') // L-7 and F-J should count as |
          inLoop = !inLoop;
        else
          previous = ' '; // Reset previous if not L-7 or F-J
    }
  }
  
  std::cout << "Part 1: " << part1 << std::endl; //6725
  std::cout << "Part 2: " << part2 << std::endl; //383
}