#include <algorithm>
#include <iostream>
#include <limits>
#include <vector>
#include <thread>
#include <atomic>

#include "CRC32.hpp"
#include "IO.hpp"

/// @brief Переписывает последние 4 байта значением value
void replaceLastFourBytes(std::vector<char> &data, uint32_t value) {
  std::copy_n(reinterpret_cast<const char *>(&value), 4, data.end() - 4);
}



void bruteforce(std::vector<char> data, 
                std::atomic<bool> &done,
                std::atomic<uint32_t> &foundValue,
                const uint32_t originalCrc32,
                const uint32_t prefixCrc32,
                uint32_t begin,
                uint32_t end) {

  for (uint32_t i = begin; i < end; i++){
    if (done || foundValue.load() != 0) return;

   replaceLastFourBytes(data, uint32_t(i));
    // Вычисляем CRC32 текущего вектора result
    uint32_t currentCrc32 = crc32(data.data() + data.size() - 4, 4, ~prefixCrc32);
    if (currentCrc32 == originalCrc32) {
      done = true;
      foundValue = i;
      std::cout << "Success\n";
    }
  }
}


/**
 * @brief Формирует новый вектор с тем же CRC32, добавляя в конец оригинального
 * строку injection и дополнительные 4 байта
 * @details При формировании нового вектора последние 4 байта не несут полезной
 * нагрузки и подбираются таким образом, чтобы CRC32 нового и оригинального
 * вектора совпадали
 * @param original оригинальный вектор
 * @param injection произвольная строка, которая будет добавлена после данных
 * оригинального вектора
 * @return новый вектор
 */
std::vector<char> hack(const std::vector<char> &original,
                       const std::string &injection) {
  const uint32_t originalCrc32 = crc32(original.data(), original.size());

  std::vector<char> result(original.size() + injection.size() + 4);
  auto it = std::copy(original.begin(), original.end(), result.begin());
  std::copy(injection.begin(), injection.end(), it);

  uint32_t prefixCrc32 = crc32(result.data(), result.size() -4);
  
  const size_t maxVal = std::numeric_limits<uint32_t>::max();

  std::atomic<bool> done = false;
  std::atomic<uint32_t> foundValue{0};

  int num_threads = std::thread::hardware_concurrency();
  std::vector<std::thread> threads;
  
  uint32_t chunk = maxVal / num_threads;
  
  for (uint32_t i = 0; i < num_threads; i++){
    uint32_t begin = i * chunk;
    uint32_t end{0};

    if (i == num_threads - 1){
      end = maxVal;
    } else {
      end = begin + chunk;
    }

    threads.emplace_back(bruteforce,
                        result,
                        std::ref(done),
                        std::ref(foundValue),
                        originalCrc32, 
                        prefixCrc32,
                        begin, 
                        end);
  }

  for (auto& t : threads){
    t.join();
  }
  replaceLastFourBytes(result, foundValue.load());
  return result;
}


int main(int argc, char **argv) {
  if (argc != 3) {
    std::cerr << "Call with two args: " << argv[0]
              << " <input file> <output file>\n";
    return 1;
  }

  try {
    const std::vector<char> data = readFromFile(argv[1]);
    const std::vector<char> badData = hack(data, "He-he-he");
    writeToFile(argv[2], badData);
  } catch (std::exception &ex) {
    std::cerr << ex.what() << '\n';
    return 2;
  }
  return 0;
}
