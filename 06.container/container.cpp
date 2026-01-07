#include <iostream>
#include "array.hpp"
#include "list.hpp"



int main(){
    // List
    std::cout << "### LIST ###" << std::endl;
    List<int> my_list = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    std::cout << "After initialization: " << std::endl;
    std::cout << "Data: " <<  my_list << std::endl;
    std::cout << "Size: " << my_list.size() << std::endl;

    my_list.erase(2);
    my_list.erase(5);
    my_list.erase(3);
    std::cout << "After erase: "  << std::endl;
    std::cout << "Data: " <<  my_list << std::endl;
    std::cout << "Size: " << my_list.size() << std::endl;

    my_list.insert(10, 0);
    std::cout << "After insert: " << std::endl;
    std::cout << "Data: " <<  my_list << std::endl;
    std::cout << "Size: " << my_list.size() << std::endl;

    my_list.insert(20, static_cast<int>(my_list.size() / 2));
    std::cout << "After middle insert: " << std::endl;
    std::cout << "Data: " <<  my_list << std::endl;
    std::cout << "Size: " << my_list.size() << std::endl;

    my_list.push_back(30);
    std::cout << "After push_back: " << std::endl;
    std::cout << "Data: " <<  my_list << std::endl;
    std::cout << "Size: " << my_list.size() << std::endl;
    std::cout << std::endl;

    // Array
    std::cout << "### ARRAY ###" << std::endl;
    List<int> my_array = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    std::cout << "After initialization: " << std::endl;
    std::cout << "Data: " <<  my_array << std::endl;
    std::cout << "Size: " << my_array.size() << std::endl;


    my_array.erase(2);
    my_array.erase(5);
    my_array.erase(3);
    std::cout << "After erase: "  << std::endl;
    std::cout << "Data: " <<  my_array << std::endl;
    std::cout << "Size: " << my_array.size() << std::endl;

    my_array.insert(10, 0);
    std::cout << "After insert: " << std::endl;
    std::cout << "Data: " <<  my_array << std::endl;
    std::cout << "Size: " << my_array.size() << std::endl ;

    my_array.insert(20, static_cast<int>(my_array.size() / 2));
    std::cout << "After middle insert: " << std::endl;
    std::cout << "Data: " <<  my_array << std::endl;
    std::cout << "Size: " << my_array.size() << std::endl;

    my_array.push_back(30);
    std::cout << "After push_back: " << std::endl;
    std::cout << "Data: " <<  my_array << std::endl;
    std::cout << "Size: " << my_array.size() << std::endl;
    std::cout << std::endl;

    return 0 ;
}

