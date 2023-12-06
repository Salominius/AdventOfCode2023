#include "../helpers/inputHelpers.hpp"
#include "../helpers/lists.hpp"
#include <sstream>
#include <math.h>

int getNumberOfWaysToWin(double totalTime, double highscore) {
  // distance = speed * time   | speed = wait and time = totalTime - wait
  // distance = wait * (totalTime - wait)
  // distance = wait*totalTime - wait^2   | - distance
  // 0 = - wait^2 + wait*totalTime - distance   | * -1
  // 0 = wait^2 - wait*totalTime + distance   | solve for wait (pq-formula) to know how long one has to wait to reach the given distance
  // wait = totalTime/2 +- sqrt((totalTime/2)^2 - distance)   (pq-formula)
  double distance = highscore + 0.001; // + 0.001 to make sure that the distance is higher than the highscore
  int minWait = std::ceil(totalTime/2 - sqrt((totalTime/2)*(totalTime/2) - distance));
  int maxWait = std::floor(totalTime/2 + sqrt((totalTime/2)*(totalTime/2) - distance));
  return maxWait - minWait + 1;
}

int main() {
  int part1 = 1;
  int part2 = 0;

  std::vector<std::string> input = getInput("../inputs/day6.txt");
  
  //Get input for Part 1:
  std::vector<int> times;
  std::vector<int> highscores;
  int number;
  
  std::istringstream iss(input[0].substr(5));
  while (iss >> number)
    times.push_back(number);

  iss = std::istringstream(input[1].substr(9));
  while (iss >> number)
    highscores.push_back(number);

  //Part 1:
  for (int i = 0; i < times.size(); i++)
    part1 *= getNumberOfWaysToWin(times[i], highscores[i]);

  //Get input for Part 2:
  double totalTime = std::stod(join(times, ""));
  double highscore = std::stod(join(highscores, ""));

  //Part 2:
  part2 = getNumberOfWaysToWin(totalTime, highscore);

  std::cout << "Part 1: " << part1 << std::endl; //741000
  std::cout << "Part 2: " << part2 << std::endl; //38220708
}