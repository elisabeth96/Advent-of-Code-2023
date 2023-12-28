//
// Created by elisabeth on 28.12.23.
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

std::vector<int> string_vector_to_int (std::vector<std::string> &input){
    std::vector<int> output;
    for (auto &element: input){
        output.push_back(std::stoi(element));
    }
    return output;
}

int predict_number(std::vector<int> &input){
    std::vector<std::vector<int>> differences;
    differences.push_back(input);
    while (std::any_of(differences.back().begin(), differences.back().end(), [](int i){return i != 0;})){
        std::vector<int> current;
        for (int i = 0; i < differences.back().size() - 1; i++){
            current.push_back(differences.back()[i+1] - differences.back()[i]);
        }
        differences.push_back(current);
    }
    for (int i = differences.size() - 1; i >= 1; i--){
        differences[i-1].push_back(differences[i-1].back() + differences[i].back());
    }
    return differences[0].back();
}

int predict_prev_number(std::vector<int> &input){
    std::reverse(input.begin(), input.end());
    std::vector<std::vector<int>> differences;
    differences.push_back(input);
    while (std::any_of(differences.back().begin(), differences.back().end(), [](int i){return i != 0;})){
        std::vector<int> current;
        for (int i = 0; i < differences.back().size() - 1; i++){
            current.push_back(differences.back()[i] - differences.back()[i+1]);
        }
        differences.push_back(current);
    }
    for (int i = differences.size() - 1; i >= 1; i--){
        differences[i-1].push_back(differences[i-1].back() - differences[i].back());
    }
    return differences[0].back();
}

int main() {
    //Read in the input file
    std::string path = "/home/elisabeth/CLionProjects/Advent-of-Code-2023/";
    std::vector<std::string> input;
    std::fstream input_file(path + "input_day09.txt");
    if (!input_file.is_open()) {
        std::cout << "Could not open file" << std::endl;
        return 1;
    }
    while (!input_file.eof()) {
        std::string line;
        std::getline(input_file, line);
        input.push_back(line);
    }

    // Solution for part 1
    std::vector<std::vector<int>> input_numbers;
    int value = 0;
    for (int i = 0; i < input.size(); i++) {
        std::vector<std::string> current;
        split_string(input[i], current, ' ');
        input_numbers.push_back(string_vector_to_int(current));
    }
    for (int i = 0; i < input_numbers.size(); i++){
        value += predict_number(input_numbers[i]);
    }
    std::cout << "Solution for part 1: " << value << std::endl;

    // Solution for part 2
    value = 0;
    for (int i = 0; i < input_numbers.size(); i++){
        value += predict_prev_number(input_numbers[i]);
    }
    std::cout << "Solution for part 2: " << value << std::endl;

}