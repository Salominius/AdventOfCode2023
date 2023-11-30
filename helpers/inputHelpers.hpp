#include <vector>
#include <cstdint>
#include <sstream>
#include <fstream>
#include <iostream>

using std::vector, std::string, std::stringstream, std::ifstream;

template<typename T>
vector<T> getInput(string inputPath) {
  vector<T> data;
  ifstream infile(inputPath);
  string line;

  if(infile.is_open()) {
    while(getline(infile, line)) {
      T element;
      stringstream input(line);
      while(input >> element)
        data.push_back(element);
    }
  } else {
    std::cout << "Unable to open file" << std::endl;
  }

  return data;
}