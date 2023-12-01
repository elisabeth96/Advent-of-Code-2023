//
// Created by elisabeth on 01.12.23.
//
#include <fstream>
#include <iostream>
#include <map>
#include <vector>

int main() {
    //Read in the input file
    std::string path = "/home/elisabeth/CLionProjects/Advent-of-Code-2023/";
    std::vector<std::string> input;
    std::fstream input_file(path + "input_day01.txt");
    if (!input_file.is_open()) {
        std::cout << "Could not open file" << std::endl;
        return 1;
    }
    while (!input_file.eof()) {
        std::string line;
        std::getline(input_file, line);
        input.push_back(line);
    }
    input_file.close();

    // Solution for part 1
    int sum = 0;
    for (auto &line: input) {
        int index = 0;
        // check for first number
        while (index < line.size() && (line[index] < 47 || line[index] > 57)) {
            index++;
        }
        sum += 10 * (line[index] - 48);
        // check for last number
        index = line.size() - 1;
        while (index >= 0 && (line[index] < 47 || line[index] > 57)) {
            index--;
        }
        sum += line[index] - 48;
    }
    std::cout << "Solution for part 1: " << sum << std::endl;

    // Solution for part 2
    std::map<std::string, int> numbers;
    numbers["one"] = 1;
    numbers["two"] = 2;
    numbers["three"] = 3;
    numbers["four"] = 4;
    numbers["five"] = 5;
    numbers["six"] = 6;
    numbers["seven"] = 7;
    numbers["eight"] = 8;
    numbers["nine"] = 9;

    sum = 0;
    for (auto &line: input) {
        // check for first number
        for (int i = 0; i < line.size(); i++) {
            // check for written numbers
            if (line[i] < 47 || line[i] > 57) {
                if (i + 3 < line.size()) {
                    auto word1 = numbers.find(line.substr(i, 3));
                    if (word1 != numbers.end()) {
                        sum += 10 * word1->second;
                        i = line.size();
                    }
                }
                if (i + 4 < line.size()) {
                    auto word2 = numbers.find(line.substr(i, 4));
                    if (word2 != numbers.end()) {
                        sum += 10 * word2->second;
                        i = line.size();
                    }
                }
                if (i + 5 < line.size()) {
                    auto word3 = numbers.find(line.substr(i, 5));
                    if (word3 != numbers.end()) {
                        sum += 10 * word3->second;
                        i = line.size();
                    }
                }
            } else {
                sum += 10 * (line[i] - 48);
                i = line.size();
            }
        }
        // check for last number
        for (int i = line.size() - 1; i >= 0; i--) {
            // check for written numbers
            if (line[i] < 47 || line[i] > 57) {
                if (i - 2 >= 0) {
                    auto word1 = numbers.find(line.substr(i  - 2, 3));
                    if (word1 != numbers.end()) {
                        sum += word1->second;
                        i = -1;
                    }
                }
                if (i - 3 >= 0) {
                    auto word2 = numbers.find(line.substr(i -3, 4));
                    if (word2 != numbers.end()) {
                        sum += word2->second;
                        i = -1;
                    }
                }
                if (i - 4 >= 0) {
                    auto word3 = numbers.find(line.substr(i - 4, 5));
                    if (word3 != numbers.end()) {
                        sum += word3->second;
                        i = -1;
                    }
                }
            } else {
                sum += line[i] - 48;
                i = -1;
            }
        }
    }
    std::cout << "Solution for part 2: " << sum << std::endl;

    return 0;
}