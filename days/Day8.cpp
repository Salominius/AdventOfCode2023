#include "../helpers/inputHelpers.hpp"
#include "../helpers/lists.hpp"
#include "../helpers/math.hpp"
#include <algorithm>
#include <map>

int main() {
  int part1 = 0;
  uint64_t part2 = 0;

  // Read input
  std::vector<string> input = getInput("../inputs/day8.txt");
  string instructions = input[0];

  std::map<string, std::pair<string, string>> rules;
  std::vector<string> startNodes; // Part 2
  for (int i = 2; i < input.size(); i++) {
    string startNode = input[i].substr(0, 3);
    string leftNode = input[i].substr(7, 3);
    string rightNode = input[i].substr(12, 3);
    rules[startNode] = std::make_pair(leftNode, rightNode);

    if (startNode[2] == 'A')
      startNodes.push_back(startNode);
  }

  // Part 1:
  string currentNode = "AAA";
  while (currentNode != "ZZZ") {
    for (const char& c : instructions) {
      if (c == 'L')
        currentNode = rules[currentNode].first;
      else
        currentNode = rules[currentNode].second;
      
      part1++;
      if (currentNode == "ZZZ")
        break;
    }
  }

  // Part 2:
  std::vector<uint64_t> requiredSteps;
  for (const string& node : startNodes) {
    currentNode = node;
    uint64_t steps = 0;
    while (currentNode[2] != 'Z') {
      for (const char& c : instructions) {
        if (c == 'L')
          currentNode = rules[currentNode].first;
        else
          currentNode = rules[currentNode].second;
        
        steps++;
        if (currentNode[2] == 'Z')
          break;
      }
    }
    requiredSteps.push_back(steps);
  }
  
  part2 = math::lcm(requiredSteps);

  std::cout << "Part 1: " << part1 << std::endl; //12643
  std::cout << "Part 2: " << part2 << std::endl; //13133452426987
}