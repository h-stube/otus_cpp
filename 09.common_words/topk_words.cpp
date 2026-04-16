// Read files and prints top k word by frequency

#include <algorithm>
#include <cctype>
#include <cstdlib>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <iterator>
#include <map>
#include <unordered_map>
#include <vector>
#include <chrono>
#include <filesystem>
#include <thread>
#include <shared_mutex>

const size_t TOPK = 10;

using Counter = std::map<std::string, size_t>;
using Filemap = std::map<size_t, std::string>;

std::string tolower(const std::string &str);
void count_words(std::istream& stream, Counter&);
void print_topk(std::ostream& stream, const Counter&, const size_t k);


std::string tolower(const std::string &str) {
    std::string lower_str;
    std::transform(std::cbegin(str), std::cend(str),
                   std::back_inserter(lower_str),
                   [](unsigned char ch) { return std::tolower(ch); });
    return lower_str;
};


void process_text(std::mutex &mtx, const Filemap &filemap, Counter &counter, size_t start_byte, size_t end_byte) {
    auto it = filemap.upper_bound(start_byte); // Находим в каком файле начинаем читать, по start_byte
    --it;
    size_t file_size = std::filesystem::file_size(it->second);
    size_t file_start = it->first;
    size_t offset = start_byte - file_start;
    size_t can_read = std::min(end_byte - start_byte, file_size - offset);
    std::ifstream file{it->second};

    file.seekg(offset);

    std::string word;

    while (file >> word) {

        size_t current_byte = file.tellg();
        if (current_byte == -1 || (current_byte >= offset + can_read)) {
            break;
        }
        std::lock_guard<std::mutex> guard(mtx);
        ++counter[tolower(word)];
    }
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        std::cerr << "Usage: topk_words [FILES...]\n";
        return EXIT_FAILURE;
    }

    auto start = std::chrono::high_resolution_clock::now();
    Counter freq_dict;

    // Evaluate work
    Filemap filemap;
    size_t total_size{0};

    for (int i = 1; i < argc; ++i) {

        size_t size = std::filesystem::file_size(argv[i]);
        filemap[total_size] = argv[i];
        total_size += size;

    }

    // Create threads
    uint8_t num_threads = std::thread::hardware_concurrency();
    std::vector<std::thread> threads;
    std::mutex dict_mutex;

    uint32_t chunk_size = total_size / num_threads;

    for (uint8_t i = 0; i < num_threads; i++) {
        size_t start = i * chunk_size;
        size_t end{0};
        if (i == num_threads - 1){
            end = total_size;
        } else {
            end = start + chunk_size; // последний поток читает до конца чанка
        }
        threads.emplace_back(process_text,
                            std::ref(dict_mutex),
                            std::ref(filemap),
                            std::ref(freq_dict),
                            start,
                            end);
    }
    
    for (size_t i = 0; i < threads.size(); i++) {
        threads[i].join();
    }

    print_topk(std::cout, freq_dict, TOPK);
    auto end = std::chrono::high_resolution_clock::now();
    auto elapsed_ms = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    std::cout << "Elapsed time is " << elapsed_ms.count() << " us\n";
}

void count_words(std::istream& stream, Counter& counter) {
    std::for_each(std::istream_iterator<std::string>(stream),
                  std::istream_iterator<std::string>(),
                  [&counter](const std::string &s) { ++counter[tolower(s)]; });    
}

void print_topk(std::ostream& stream, const Counter& counter, const size_t k) {
    std::vector<Counter::const_iterator> words;
    words.reserve(counter.size());
    for (auto it = std::cbegin(counter); it != std::cend(counter); ++it) {
        words.push_back(it);
    }

    std::partial_sort(
        std::begin(words), std::begin(words) + k, std::end(words),
        [](auto lhs, auto &rhs) { return lhs->second > rhs->second; });

    std::for_each(
        std::begin(words), std::begin(words) + k,
        [&stream](const Counter::const_iterator &pair) {
            stream << std::setw(4) << pair->second << " " << pair->first
                      << '\n';
        });
}