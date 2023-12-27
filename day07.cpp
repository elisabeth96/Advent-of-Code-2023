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

void change_string(std::string& cards){
    for (int i = 0; i < cards.size(); i++){
        // sort according to order A, K, Q, J, T, 9, 8, 7, 6, 5, 4, 3, or 2
        switch (cards[i]){
            case 'A':
                cards[i] = 'A';
                break;
            case 'K':
                cards[i] = 'B';
                break;
            case 'Q':
                cards[i] = 'C';
                break;
            case 'J':
                cards[i] = 'D';
                break;
            case 'T':
                cards[i] = 'E';
                break;
            case '9':
                cards[i] = 'F';
                break;
            case '8':
                cards[i] = 'G';
                break;
            case '7':
                cards[i] = 'H';
                break;
            case '6':
                cards[i] = 'I';
                break;
            case '5':
                cards[i] = 'J';
                break;
            case '4':
                cards[i] = 'K';
                break;
            case '3':
                cards[i] = 'L';
                break;
            case '2':
                cards[i] = 'M';
                break;
        }
    }
}

void change_string_incl_j(std::string& cards){
    for (int i = 0; i < cards.size(); i++){
        // sort according to order A, K, Q, T, 9, 8, 7, 6, 5, 4, 3, 2, or J
        switch (cards[i]){
            case 'A':
                cards[i] = 'A';
                break;
            case 'K':
                cards[i] = 'B';
                break;
            case 'Q':
                cards[i] = 'C';
                break;
            case 'T':
                cards[i] = 'E';
                break;
            case '9':
                cards[i] = 'F';
                break;
            case '8':
                cards[i] = 'G';
                break;
            case '7':
                cards[i] = 'H';
                break;
            case '6':
                cards[i] = 'I';
                break;
            case '5':
                cards[i] = 'J';
                break;
            case '4':
                cards[i] = 'K';
                break;
            case '3':
                cards[i] = 'L';
                break;
            case '2':
                cards[i] = 'M';
                break;
            case 'J':
                cards[i] = 'N';
                break;
        }
    }
}

int main() {
    //Read in the input file
    std::string path = "/home/elisabeth/CLionProjects/Advent-of-Code-2023/";
    std::vector<std::string> input;
    std::fstream input_file(path + "input_day07.txt");
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
    // Save the pairs of cards and value ordered by kind of hand
    // index 0 contains to the strongest hand
    std::vector<std::vector<std::pair<std::string, int>>> cards(7);
    for (auto &line: input){
        std::vector<std::string> temp;
        split_string(line, temp, ' ');
        std::map<char, int> card_counter;
        for (int i = 0; i < temp[0].size(); i++){
            card_counter[temp[0][i]]++;
        }
        int max = std::max_element(card_counter.begin(), card_counter.end(), [](const std::pair<char, int> &a, const std::pair<char, int> &b) -> bool { return a.second < b.second; })->second;
        int min = std::min_element(card_counter.begin(), card_counter.end(), [](const std::pair<char, int> &a, const std::pair<char, int> &b) -> bool { return a.second < b.second; })->second;
        int count_2 = 0;
        for (int i = 0; i < card_counter.size(); i++){
            if (card_counter[i] == 2){
                count_2++;
            }
        }
        change_string(temp[0]);
        switch (max) {
            case 5:
                cards[0].emplace_back(temp[0], string_to_number(temp[1]));
                break;
            case 4:
                cards[1].emplace_back(temp[0], string_to_number(temp[1]));
                break;
            case 3:
                if (min == 2){
                    cards[2].emplace_back(temp[0], string_to_number(temp[1]));
                } else {
                    cards[3].emplace_back(temp[0], string_to_number(temp[1]));
                }
                break;
            case 2:
                if (count_2 == 2){
                    cards[4].emplace_back(temp[0], string_to_number(temp[1]));
                } else {
                    cards[5].emplace_back(temp[0], string_to_number(temp[1]));
                }
                break;
            case 1:
                cards[6].emplace_back(temp[0], string_to_number(temp[1]));
                break;
        }
    }
    // sort cards and compute their value
    long value = 0;
    long rank = 1;
    std::reverse(cards.begin(), cards.end());
    for (int i = 0; i < cards.size(); i++){
        std::sort(cards[i].begin(), cards[i].end());
        std::reverse(cards[i].begin(), cards[i].end());
        for (int j = 0; j < cards[i].size(); j++){
            value += cards[i][j].second * rank;
            rank++;
        }
    }
    std::cout << "Solution for part 1: " << value << std::endl;

    // Solution for part 2
    // Save the pairs of cards and value ordered by kind of hand
    // index 0 contains to the strongest hand
    std::vector<std::vector<std::pair<std::string, int>>> cards_incl_j(7);
    for (auto &line: input){
        std::vector<std::string> temp;
        split_string(line, temp, ' ');
        std::map<char, int> card_counter;
        int count_j = 0;
        for (int i = 0; i < temp[0].size(); i++){
            if (temp[0][i] == 'J'){
                count_j++;
                continue;
            }
            card_counter[temp[0][i]]++;
        }
        int max = std::max_element(card_counter.begin(), card_counter.end(), [](const std::pair<char, int> &a, const std::pair<char, int> &b) -> bool { return a.second < b.second; })->second;
        int min = std::min_element(card_counter.begin(), card_counter.end(), [](const std::pair<char, int> &a, const std::pair<char, int> &b) -> bool { return a.second < b.second; })->second;
        int count_2 = 0;
        for (int i = 0; i < card_counter.size(); i++){
            if (card_counter[i] == 2){
                count_2++;
            }
        }
        change_string_incl_j(temp[0]);
        switch (max) {
            case 5:
                cards_incl_j[0].emplace_back(temp[0], string_to_number(temp[1]));
                break;
            case 4:
                if (count_j == 1){
                    cards_incl_j[0].emplace_back(temp[0], string_to_number(temp[1]));
                } else {
                    cards_incl_j[1].emplace_back(temp[0], string_to_number(temp[1]));
                }
                break;
            case 3:
                if (count_j == 2){
                    cards_incl_j[0].emplace_back(temp[0], string_to_number(temp[1]));
                } else if (count_j == 1){
                    cards_incl_j[1].emplace_back(temp[0], string_to_number(temp[1]));
                }
                else if (min == 2){
                    cards_incl_j[2].emplace_back(temp[0], string_to_number(temp[1]));
                } else {
                    cards_incl_j[3].emplace_back(temp[0], string_to_number(temp[1]));
                }
                break;
            case 2:
                if (count_j == 3){
                    cards_incl_j[0].emplace_back(temp[0], string_to_number(temp[1]));
                }
                else if (count_j == 2){
                    cards_incl_j[1].emplace_back(temp[0], string_to_number(temp[1]));
                } else if (count_j == 1){
                    if (count_2 == 2){
                        cards_incl_j[2].emplace_back(temp[0], string_to_number(temp[1]));
                    } else {
                        cards_incl_j[3].emplace_back(temp[0], string_to_number(temp[1]));
                    }
                }
                else if (count_2 == 2){
                    cards_incl_j[4].emplace_back(temp[0], string_to_number(temp[1]));
                } else {
                    cards_incl_j[5].emplace_back(temp[0], string_to_number(temp[1]));
                }
                break;
            case 1:
                if (count_j == 4){
                    cards_incl_j[0].emplace_back(temp[0], string_to_number(temp[1]));
                }
                else if (count_j == 3){
                    cards_incl_j[1].emplace_back(temp[0], string_to_number(temp[1]));
                } else if (count_j == 2){
                    cards_incl_j[3].emplace_back(temp[0], string_to_number(temp[1]));
                }
                else if (count_j == 1){
                    cards_incl_j[5].emplace_back(temp[0], string_to_number(temp[1]));
                }
                else {
                    cards_incl_j[6].emplace_back(temp[0], string_to_number(temp[1]));
                }
                break;
            default:
                cards_incl_j[0].emplace_back(temp[0], string_to_number(temp[1]));
        }
    }
    // sort cards and compute their value
    value = 0;
    rank = 1;
    std::reverse(cards_incl_j.begin(), cards_incl_j.end());
    for (int i = 0; i < cards_incl_j.size(); i++){
        std::sort(cards_incl_j[i].begin(), cards_incl_j[i].end());
        std::reverse(cards_incl_j[i].begin(), cards_incl_j[i].end());
        for (int j = 0; j < cards_incl_j[i].size(); j++){
            value +=cards_incl_j[i][j].second * rank;
            rank++;
        }
    }
    std::cout << "Solution for part 2: " << value << std::endl;

}