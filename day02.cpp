//
// Created by elisabeth on 02.12.23.
//
#include <fstream>
#include <iostream>
#include <map>
#include <sstream>
#include <vector>

struct Set {
    int green = 0;
    int red = 0;
    int blue = 0;
};

void split_string(std::string &input, std::vector<std::string> &output, char delimiter) {
    std::string token;
    std::stringstream input_stream(input);
    while (std::getline(input_stream, token, delimiter)) {
        if (token[0] == ' '){
            token.erase(0, 1);
        }
        output.push_back(token);
    }
}

std::string find_first_number(std::string &input) {
    std::string output;
    for (auto &element: input) {
        if (element >= 48 && element <= 57) {
            output += element;
        } else {
            break;
        }
    }
    return output;
}

Set get_set(std::string &input) {
    Set output;
    std::vector<std::string> input_split;
    split_string(input, input_split, ',');
    for (auto &element: input_split) {
        std::string num = find_first_number(element);
        switch (element[num.size() +1]) {
            case 'g':
                output.green = std::atoi(num.c_str());
                break;
            case 'r':
                output.red = std::atoi(num.c_str());
                break;
            case 'b':
                output.blue = std::atoi(num.c_str());
                break;
        }
    }
    return output;
}

int main() {
    //Read in the input file
    std::string path = "/home/elisabeth/CLionProjects/Advent-of-Code-2023/";
    std::vector<std::string> input;
    std::fstream input_file(path + "input_day02.txt");
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
    std::vector<std::vector<Set>> games;
    for (auto &line: input) {
        // description not needed
        line.erase(0, line.find(':') + 2);
        // read in sets for this game
        std::vector<std::string> line_split;
        split_string(line, line_split, ';');
        std::vector<Set> sets;
        for (auto &element: line_split) {
            Set set = get_set(element);
            sets.push_back(set);
        }
        games.push_back(sets);
    }
    // get valid games and sum up ids
    int sum = 0;
    for (int i = 0; i < games.size(); i++) {
        bool valid = true;
        for (int j = 0; j < games[i].size(); j++) {
            if (games[i][j].green > 13 || games[i][j].red > 12 || games[i][j].blue > 14) {
                valid = false;
                break;
            }
        }
        if (valid) {
            sum += i + 1;
        }
    }
    std::cout << "Solution for part 1: " << sum << std::endl;

    // Solution for part 2
    sum = 0;
    for (int i = 0; i < games.size(); i++) {
        int max_green = 0;
        int max_red = 0;
        int max_blue = 0;
        for (int j = 0; j < games[i].size(); j++) {
            if (games[i][j].green > max_green) {
                max_green = games[i][j].green;
            }
            if (games[i][j].red > max_red) {
                max_red = games[i][j].red;
            }
            if (games[i][j].blue > max_blue) {
                max_blue = games[i][j].blue;
            }
        }
        sum += max_green * max_red * max_blue;
    }
    std::cout << "Solution for part 2: " << sum << std::endl;
}