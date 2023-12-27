//
// Created by elisabeth on 27.12.23.
//
#include <algorithm>
#include <fstream>
#include <iostream>
#include <map>
#include <sstream>
#include <vector>


void remove_weird_characters(std::string &input) {
    auto it = std::remove_if(input.begin(), input.end(), [](char c) { return !std::isalnum(c) && !std::isspace(c); });
    input.erase(it, input.end());
}

int main() {
    //Read in the input file
    std::string path = "/home/elisabeth/CLionProjects/Advent-of-Code-2023/";
    std::vector<std::string> input;
    std::fstream input_file(path + "input_day08.txt");
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
    std::string directions = input[0];
    std::map<std::string, std::pair<std::string, std::string>> nodes;
    for (int i = 2; i < input.size(); i++) {
        remove_weird_characters(input[i]);
        std::string from, to1, to2;
        std::stringstream ss(input[i]);
        ss >> from >> to1 >> to2;
        nodes[from] = std::make_pair(to1, to2);
    }
    int counter = 0;
    int i = 0;
    /*std::string current = "AAA";
    while(current != "ZZZ"){
        if (directions[i % directions.size()] == 'L'){
            current = nodes[current].first;
        } else {
            current = nodes[current].second;
        }
        counter++;
        i++;
    }
    std::cout << "Solution for part 1: " << counter << std::endl;*/

    // Solution for part 1
    std::vector<long long> nums;
    for (const auto& element : nodes){
        if (element.first[2] == 'A'){
            auto current = element.first;
            counter = 0;
            i = 0;
            while(current[2] != 'Z'){
                if (directions[i % directions.size()] == 'L'){
                    current = nodes[current].first;
                } else {
                    current = nodes[current].second;
                }
                counter++;
                i++;
            }
            nums.push_back(counter);
        }
    }
    // compute the least common multiple of integers in nums
    long long lcm = 1;
    for (int i = 0; i < nums.size(); i++) {
        lcm = (nums[i] * lcm) / std::__gcd(nums[i], lcm);
    }
    std::cout << "Solution for part 2: " << lcm << std::endl;

}