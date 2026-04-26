#include <gtest/gtest.h>
#include <vector>
#include "array.hpp"




// Создание
TEST(ArrayTest, SilmpleConstructor) {
        Array<int> arr;
        EXPECT_EQ(arr.size(), 0);
}

TEST(ArrayTest, SizeConstructo) {
        Array<int> arr(55);
        EXPECT_EQ(arr.size(), 55);
}


TEST(ArrayTest, InitializerListConstructor) {
        Array<int> arr{0, 1, 2, 3};

        EXPECT_EQ(arr.size(), 4);
        EXPECT_EQ(arr[0], 0);
        EXPECT_EQ(arr[1], 1);
        EXPECT_EQ(arr[2], 2);
        EXPECT_EQ(arr[3], 3);
}

TEST(ArrayTest, EmptyInitializerListConstructo) {
        Array<int> arr{};
        EXPECT_EQ(arr.size(), 0);
}

// Вставка в конец
TEST(ArrayTest, InsertToEndEmpty) {
    Array<int> arr;
    arr.push_back(7744);
    EXPECT_EQ(arr.size(), 1);
    EXPECT_EQ(arr[0], 7744);

    arr.push_back(8888);
    EXPECT_EQ(arr.size(), 2);
    EXPECT_EQ(arr[1], 8888);
}

TEST(ArrayTest, InsertToEndNotEmpty) {
    Array<int> arr{1, 2, 3, 4, 5};
    size_t start_size = arr.size();
    int last_value = arr[start_size - 1];

    arr.push_back(8888);

    EXPECT_NE(arr.size(), start_size);
    EXPECT_EQ(arr[arr.size() - 2], last_value);
}

// Вставка в начало
TEST(ArrayTest, InsertToBeginningEmpty) {
    Array<int> arr;
    arr.insert(7744, 0);
    EXPECT_EQ(7744, arr[0]);
    EXPECT_NE(arr.size(), 0);
}

TEST(ArrayTest, InsertToBeginnigNotEmpty) {
    Array<int> arr{0,1,2};
    size_t start_size = arr.size();

    arr.insert(7744, 0);
    EXPECT_EQ(arr.size(), start_size + 1);
    EXPECT_EQ(arr[0], 7744);

}

// Вставка в середину
TEST(ArrayTest, InsertToMiddleEmpty) {
    Array<int> arr;
    arr.insert(7744, 0);
    EXPECT_EQ(7744, arr[0]);
    EXPECT_NE(arr.size(), 0);
}

TEST(ArrayTest, InsertToMiddleNotEmpty) {
    Array<int> arr{0,1,2};
    size_t start_size = arr.size();
    int first_value = arr[0];

    arr.insert(7744, 0);
    EXPECT_EQ(arr.size(), start_size + 1);
    EXPECT_EQ(arr[1], first_value);
}

// Удаление элементов из конца
TEST(ArrayTest, DeleteFromEnd) {
    Array<int> arr{0,1,2};
    size_t start_size = arr.size();
    int penult_value = arr[start_size - 2];

    arr.erase(start_size -1);

    EXPECT_EQ(arr[arr.size() -1], penult_value);
    EXPECT_EQ(arr.size(), start_size -1);
}

// Удаление элементов из начала
TEST(ArrayTest, DeleteFromBeginning) {
    Array<int> arr{0,1,2};
    size_t start_size = arr.size();
    int second_value = arr[1];

    arr.erase(0);
    
    EXPECT_EQ(arr[0], second_value);
    EXPECT_EQ(arr.size(), start_size -1);
}

// Удаление элементов из середины
TEST(ArrayTest, DeleteFromMidle) {
    Array<int> arr{0,1,2};
    size_t start_size = arr.size();
    size_t middle = static_cast<size_t>(start_size / 2);
    int next_to_middle = arr[middle + 1];

    arr.erase(middle);
    
    EXPECT_EQ(arr[middle], next_to_middle);
    EXPECT_EQ(arr.size(), start_size -1);
}

// Получение элементов из контейнера
TEST(ArrayTest, GetElements) {
    Array<int> arr{7, 8, 9};

    EXPECT_EQ(arr[0], 7);
    EXPECT_EQ(arr[1], 8);
    EXPECT_EQ(arr[2], 9);
}

// Размер 
TEST(Array, SizeOperations) {
    Array<int> arr{};
    EXPECT_EQ(arr.size(), 0);

    arr.push_back(7744);
    EXPECT_EQ(arr.size(), 1);

    arr.push_back(8888);
    arr.push_back(6666);

    EXPECT_EQ(arr.size(), 3);

    arr.erase(0);

    EXPECT_EQ(arr.size(), 2);
}


