#include "../helpers/inputHelpers.hpp"
#include <sstream>
#include <algorithm>

std::vector<int64_t> getSeedsPart1(const std::string& line) {
  std::vector<int64_t> seeds;
  std::istringstream iss(line.substr(7));

  int64_t number;
  while (iss >> number)
    seeds.push_back(number);
  
  return seeds;
}

struct Map {
  int64_t destinationStart;
  int64_t sourceStart;
  int64_t length;

  Map(int64_t destinationStart, int64_t sourceStart, int64_t length) : destinationStart(destinationStart), sourceStart(sourceStart), length(length) {}
};

struct SeedRange {
  int64_t start;
  int64_t length;

  SeedRange(int64_t start, int64_t length) : start(start), length(length) {}
};

std::vector<SeedRange> getSeedsPart2(const std::string& line) {
  std::vector<SeedRange> seeds;
  std::istringstream iss(line.substr(7));

  int64_t start, length;
  while (iss >> start >> length) 
    seeds.push_back({start, length});
  
  return seeds;
}

std::vector<std::vector<Map>> getMaps(const std::vector<std::string>& input) {
  std::vector<std::vector<Map>> maps = {{}}; //level 0

  for (int i = 3; i < input.size(); i ++) { //skip seeds
    //skip empty lines as well as string description after:
    if (input[i].empty()) {
      maps.push_back({});
      i++;
      continue;
    }

    std::istringstream iss(input[i]);
    int64_t destinationStart, sourceStart, length;
    iss >> destinationStart >> sourceStart >> length;
    maps.at(maps.size()-1).push_back({Map(destinationStart, sourceStart, length)});
  }
  return maps;
}

int main() {
  int64_t part1 = 0;
  int64_t part2 = 0;

  std::vector<std::string> input = getInput("../inputs/day5.txt");
  std::vector<std::vector<Map>> maps = getMaps(input);

  //Part 1:
  std::vector<int64_t> seedsPart1 = getSeedsPart1(input[0]);
  for (auto level : maps) {
    for (auto& seed : seedsPart1) {
      for (auto map : level) {
        if (seed >= map.sourceStart && seed < map.sourceStart + map.length) {
          seed = map.destinationStart + (seed - map.sourceStart);
          break;
        }
      }
    }
  }
  part1 = *std::min_element(seedsPart1.begin(), seedsPart1.end());

  //Part 2:
  std::vector<SeedRange> seedsPart2 = getSeedsPart2(input[0]);
  for (auto level : maps) {
    for (int i = 0; i < seedsPart2.size(); i++) {
      for (auto map : level) {
        int64_t seedStart = seedsPart2[i].start;
        int64_t seedEnd = seedsPart2[i].start + seedsPart2[i].length;
        //If seedStart is in range, map part or whole:
        if (seedStart >= map.sourceStart && seedStart < map.sourceStart + map.length) {
          //If whole range can be mapped, do so:
          if (seedEnd <= map.sourceStart + map.length)
            seedsPart2[i].start = map.destinationStart + (seedsPart2[i].start - map.sourceStart);
          //If only first half can be mapped, map first half and add second half as new seedRange:
          else {
            int64_t firstHalfLength = map.sourceStart + map.length - seedsPart2[i].start;
            int64_t secondHalfLength = seedsPart2[i].length - firstHalfLength;
            //Add second half as new seedRange
            seedsPart2.push_back({seedsPart2[i].start + firstHalfLength, secondHalfLength});
            //Map first half:
            seedsPart2[i].start = map.destinationStart + (seedStart - map.sourceStart);
            seedsPart2[i].length = firstHalfLength;
          }
          break;
        }
        //If seedEnd is in range, map part or whole:
        else if (seedEnd > map.sourceStart && seedEnd < map.sourceStart + map.length) {
          //Split the range:
          int64_t firstHalfLength = map.sourceStart - seedStart;
          int64_t secondHalfLength = seedsPart2[i].length - firstHalfLength;
          //Add first half as new seedRange:
          seedsPart2.push_back({seedStart, firstHalfLength});
          //Map second half:
          seedsPart2[i].start = map.destinationStart;
          seedsPart2[i].length = secondHalfLength;
          break;
        }
        //if range is between seedStart and seedEnd, map middle:
        else if (seedStart < map.sourceStart && seedEnd > map.sourceStart + map.length) {
          //Split the range:
          int64_t leftSideLength = map.sourceStart - seedStart;
          int64_t rightSideLength = seedEnd - (map.sourceStart + map.length);
          //Add first half as new seedRange:
          seedsPart2.push_back({seedStart, leftSideLength});
          //Add second half as new seedRange:
          seedsPart2.push_back({map.sourceStart + map.length, rightSideLength});
          //Map middle:
          seedsPart2[i].start = map.destinationStart;
          seedsPart2[i].length = map.length;
          break;
        }
      }
    }
  }
  part2 = (*std::min_element(seedsPart2.begin(), seedsPart2.end(), [](const SeedRange& a, const SeedRange& b) {return a.start < b.start;})).start;

  std::cout << "Part 1: " << part1 << std::endl; //600279879
  std::cout << "Part 2: " << part2 << std::endl; //20191102
}
