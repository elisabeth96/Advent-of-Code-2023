//
// Created by elisabeth on 27.12.23.
//
#include <algorithm>
#include <fstream>
#include <iostream>
#include <map>
#include <sstream>
#include <vector>

void split_string(std::string &input, std::vector<std::string> &output, char delimiter) {
    std::string token;
    std::stringstream input_stream(input);
    while (std::getline(input_stream, token, delimiter)) {
        if (token[0] == ' ') {
            token.erase(0, 1);
            continue;
        }
        output.push_back(token);
    }
}

long string_to_number(std::string &input) {
    long output = 0;
    for (auto &element: input) {
        output *= 10;
        output += element - 48;
    }
    return output;
}

long compute_distance(long race_time, long loading_time){
    return (race_time - loading_time) * loading_time;
}

int main() {
    //Read in the input file
    std::string path = "/home/elisabeth/CLionProjects/Advent-of-Code-2023/";
    std::vector<std::string> input;
    std::fstream input_file(path + "input_day06_part2.txt");
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
    // save the time of the race and the max distance
    std::vector<std::vector<long>> races(2);
    for (int j = 0; j < input.size(); j++) {
        std::vector<std::string> line_split;
        split_string(input[j], line_split, ' ');
        for (int i = 1; i < line_split.size(); i++) {
            races[j].push_back(string_to_number(line_split[i]));
        }
    }
    std::vector<long> min(races[0].size());
    std::vector<long> max(races[0].size());
    for (int i = 0; i < races[0].size(); i++){
        for (int j = 1; j < races[0][i] - 1; j++){
            if (compute_distance(races[0][i], j) > races[1][i]){
                min[i] = j;
                break;
            }
        }
        for (int j = races[0][i] - 1; j > 0; j--){
            if (compute_distance(races[0][i], j) > races[1][i]){
                max[i] = j;
                break;
            }
        }
    }
    long result = 1;
    for (int i = 0; i < races[0].size(); i++){
        result *= (max[i] - min[i] + 1);
    }
    std::cout << "Solution: " << result << std::endl;


}