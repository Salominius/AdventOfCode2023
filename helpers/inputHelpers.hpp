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
    infile.close();
  } else {
    std::cout << "Unable to open file" << std::endl;
  }

  return data;
}

vector<string> getInput(string inputPath) {
  vector<string> data;
  ifstream infile(inputPath);
  string line;

  if(infile.is_open()) {
    while(getline(infile, line)) {
      data.push_back(line);
    }
    infile.close();
  } else {
    std::cout << "Unable to open file" << std::endl;
  }

  return data;
}

vector<vector<char>> getInputGrid(string inputPath) {
  vector<vector<char>> data;
  ifstream infile(inputPath);
  string line;

  if(infile.is_open()) {
    while(getline(infile, line)) {
      vector<char> row(line.begin(), line.end());
      data.push_back(row);
    }
    infile.close();
  } else {
    std::cout << "Unable to open file" << std::endl;
  }

  return data;
}