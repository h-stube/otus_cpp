#pragma once
#include <string>

struct Record {
    std::string name;
    int score;
};

void write_score(std::string name, int score);
void print_score();