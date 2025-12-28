
#include "statistics.hpp"


enum StatIndex {
    STAT_MIN = 0,
    STAT_MAX = 1,
    STAT_MEAN = 2,
    STAT_STD = 3,
    STAT_PCT90 = 4,
	STAT_PCT95 = 5,
};

int main() {

	// Count of statistics
	const size_t statistics_count = 6;
	IStatistics *statistics[statistics_count];


	statistics[STAT_MIN] = new Min{};
	statistics[STAT_MAX] = new Max{};
	statistics[STAT_MEAN] = new Mean{};
	statistics[STAT_STD] = new Std{};
	statistics[STAT_PCT90] = new Pct<90>{};
	statistics[STAT_PCT95] = new Pct<95>{};


	double val = 0;

	while (std::cin >> val) {
		for (size_t i = 0; i < statistics_count; ++i) {
			statistics[i]->update(val);
		}
	}

	// Handle invalid input data
	if (!std::cin.eof() && !std::cin.good()) {
		std::cerr << "Invalid input data\n";
		return 1;
	}

	// Print results if any
	for (size_t i = 0; i < statistics_count; ++i) {
		std::cout << statistics[i]->name() << " = " << statistics[i]->eval() << std::endl;
	}

	// Clear memory - delete all objects created by new
	for (size_t i = 0; i < statistics_count; ++i) {
		delete statistics[i];
	}

	return 0;
}