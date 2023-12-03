//
// Created by elisabeth on 03.12.23.
//
#include <fstream>
#include <iostream>
#include <map>
#include <sstream>
#include <vector>
#include <algorithm>

bool is_number(char input) {
    if (input < 48 || input > 57) {
        return false;
    }
    return true;
}

int string_to_number(std::string &input) {
    int output = 0;
    for (auto &element: input) {
        output *= 10;
        output += element - 48;
    }
    return output;
}

int get_complete_num(std::string &input, int index) {
    std::string num;
    num.append(1, input[index]);
    int l = 1;
    while (index + 1 < input.size() && is_number(input[index + l])) {
        num.append(1, input[index + l]);
        l++;
    }
    reverse(num.begin(), num.end());
    l = - 1;
    while (index >= 0 && is_number(input[index + l])) {
        num.append(1, input[index + l]);
        l--;
    }
    reverse(num.begin(), num.end());
    return string_to_number(num);
}

int main() {
    //Read in the input file
    std::string path = "/home/elisabeth/CLionProjects/Advent-of-Code-2023/";
    std::vector<std::string> input;
    std::fstream input_file(path + "input_day03.txt");
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
    std::vector<std::vector<bool>> calc(input.size() + 2, std::vector<bool>(input[0].size() + 2, false));
    int sum = 0;
    for (int i = 0; i < input.size(); i++) {
        for (int j = 0; j < input[i].size(); j++) {
            if (input[i][j] != '.' && !is_number(input[i][j])) {
                //check if a potential number needs to be added
                int index1 = i + 1;
                int index2 = j + 1;
                calc[index1 - 1][index2] = true;
                calc[index1 + 1][index2] = true;
                calc[index1][index2 - 1] = true;
                calc[index1][index2 + 1] = true;
                calc[index1 + 1][index2 + 1] = true;
                calc[index1 - 1][index2 - 1] = true;
                calc[index1 + 1][index2 - 1] = true;
                calc[index1 - 1][index2 + 1] = true;
            }
        }
    }
    for (int index1 = 1; index1 < calc.size()-1; index1++) {
        for (int index2 = 1; index2 < calc[index1].size()-1; index2++) {
            if (calc[index1][index2]) {
                int i = index1 - 1;
                int j = index2 - 1;
                if (is_number(input[i][j])) {
                    std::string num;
                    num.append(1, input[i][j]);
                    int l = 1;
                    while (j + 1 < calc[index1].size() && is_number(input[i][j + l])) {
                        num.append(1, input[i][j + l]);
                        calc[index1][index2 + l] = false;
                        l++;
                    }
                    reverse(num.begin(), num.end());
                    l = - 1;
                    while (j +l >= 0 && is_number(input[i][j + l])) {
                        num.append(1, input[i][j + l]);
                        calc[index1][index2 + l] = false;
                        l--;
                    }
                    reverse(num.begin(), num.end());
                    sum += string_to_number(num);
                }
            }
        }
    }
    std::cout << "Solution for part 1: " << sum << std::endl;

    // Solution for part 2
    sum = 0;
    for (int i = 0; i < input.size(); i++){
        for (int j = 0; j < input[i].size(); j++){
            if (input[i][j] == '*'){
                int counter = 0;
                std::vector<std::pair<int, int>> neighbours;
                if (i > 0 && is_number(input[i-1][j])){
                    neighbours.push_back(std::make_pair(i-1, j));
                    counter++;
                }
                else{
                    if (i > 0 && j > 0 && is_number(input[i-1][j-1])){
                        neighbours.push_back(std::make_pair(i-1, j-1));
                        counter++;
                    }
                    if (i > 0 && j < input[i].size()-1 && is_number(input[i-1][j+1])){
                        neighbours.push_back(std::make_pair(i-1, j+1));
                        counter++;
                    }
                }
                if (i < input.size()-1 && is_number(input[i+1][j])){
                    neighbours.push_back(std::make_pair(i+1, j));
                    counter++;
                }
                else{
                    if (i < input.size()-1 && j > 0 && is_number(input[i+1][j-1])){
                        neighbours.push_back(std::make_pair(i+1, j-1));
                        counter++;
                    }
                    if (i < input.size()-1 && j < input[i].size()-1 && is_number(input[i+1][j+1])){
                        neighbours.push_back(std::make_pair(i+1, j+1));
                        counter++;
                    }
                }
                if (j > 0 && is_number(input[i][j-1])){
                    neighbours.push_back(std::make_pair(i, j-1));
                    counter++;
                }
                if (j < input[i].size()-1 && is_number(input[i][j+1])){
                    neighbours.push_back(std::make_pair(i, j+1));
                    counter++;
                }
                if (counter == 2){
                    int prod = 0;
                    std::pair<int, int> index1 = neighbours[0];
                    std::pair<int, int> index2 = neighbours[1];
                    prod += get_complete_num(input[index1.first], index1.second);
                    prod *= get_complete_num(input[index2.first], index2.second);
                    sum += prod;
                }
            }
        }
    }
    std::cout << "Solution for part 2: " << sum << std::endl;
}