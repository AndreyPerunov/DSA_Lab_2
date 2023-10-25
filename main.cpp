#include <iostream>
#include <fstream>
#include <string>
#include <vector>  

void readData(std::string filename, std::vector<std::string>& arr) {
  std::ifstream file(filename);

  if (!file.is_open()) {
    std::cerr << "Error opening file" << std::endl;
    return;
  }

  std::string line;

  while (getline(file, line)) {
    try {
      arr.push_back(line);
    } catch (const std::invalid_argument& e) {
      std::cerr << "Error reading line number." << std::endl;
    }
  }

  file.close();
}

void print(std::vector<std::string> vec) {
  for (std::string str : vec) {
    std::cout << str << std::endl;
  }
}

int main() {
  std::vector<std::string> programm;
  readData("programm_text.data", programm);

  print(programm);

  std::cin.get();

  return 0;
}