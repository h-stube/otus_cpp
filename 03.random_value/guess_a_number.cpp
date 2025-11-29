#include <cstdlib>
#include <ctime> 
#include <fstream>
#include <string>
#include <iostream>

#include "high_scores.hpp"



int main(int argc, char** argv) {
	int number;
	int tries;
	const int max_value = 100;
	std::string name;

	if (argc <= 2) {
		std::cout << "Guess a number" << std::endl;
		return 0;
	}

	if (argc > 2){
		std::cout << "Only one number allowed" << std::endl;
		return 0;
	}

	std::cout << "Hello! This is a guess_number game! Enter your name to start: " << std::endl;
	std::cin >> name;

	std::srand(std::time(nullptr));
	const int random_value = std::rand() % 100;

	while(1){
		std::cout << "Guess your number from 0 to " << max_value << std::endl;
		std::cin >> number;
		tries++;
		
		if (number < random_value){
			std::cout << "bigger than " << number << std::endl;
			continue;
		}

		else if (number > random_value){
			std::cout << "less than " << number << std::endl;
			continue;
		}

		else {
			std::cout << "Congratulations " << name;
			std::cout <<  "! You won!" << std::endl;

			write_score(name, tries);
			print_score();
			break;
		}
	}


	return 0;

}