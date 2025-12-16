#include <fstream>
#include <string>
#include <iostream>
#include <unordered_map>

#include "high_scores.hpp"

const std::string high_scores_filename = "high_scores.txt";

void write_score(std::string name, int score) {
	{
		std::ofstream out_file{high_scores_filename, std::ios_base::app};
		if (!out_file.is_open()) {
			std::cout << "Fail to write score" << std::endl;
		}

		out_file << name << ' ';
		out_file << score;
		out_file << std::endl;
	}

}

void print_score(){
	std::ifstream in_file{high_scores_filename};
	if (!in_file.is_open()) {
		std::cout << "Failed to get score!" << std::endl;
	}

	int count = 0;

	std::string line;	
	while (std::getline(in_file, line)) {
        count++;
    }

	in_file.clear();
	in_file.seekg(0);
	Record* records = new Record[count];

	for (int i = 0; i < count; i++){
		in_file >> records[i].name;
		in_file >> records[i].score;
		in_file.ignore();
	}

	Record* best_records = new Record[count];
	int best_count = 0;

	for (int i = 0; i < count; i++){
		bool found = false;

		for (int j = 0; j < best_count; j++){
			if (best_records[j].name == records[i].name){
				found = true;
				if (records[i].score > best_records[j].score){
					best_records[j].score = records[i].score;
				}
			}
		}

		if (!found){
			best_records[best_count].name = records[i].name;
			best_records[best_count].score = records[i].score;
			best_count++;
		}
	
	}
	
	std::cout << "High scores table:" << std::endl;
    for (int i = 0; i < best_count; i++) {
        std::cout << best_records[i].name << '\t' << best_records[i].score << std::endl;
    }
    
    delete[] records;
    delete[] best_records;
}
