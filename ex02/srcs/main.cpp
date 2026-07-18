#include <climits>
#include <iostream>
#include <vector>
#include <cstdlib>

#include "../includes/PmergeMe.hpp"

bool is_duplicate(const std::vector<int>& values, int value){
    for (std::size_t i = 0; i < values.size(); ++i){
        if (values[i] == value)
            return(true);
    }
    return (false);
}

bool parse_arguments(int argc, char** argv, std::vector<int>& result){
    for(int i = 1; i < argc; ++i){
        std::string arg = argv[i];

        if(arg.empty()){
            std::cout << "Error: empty argument" << std::endl;
            return (false);
        }
        if(arg[0] == '-'){
            std::cout << "Error: negative number not allowed: " << arg << std::endl;
            return (false);
        }
        errno = 0;
        char* endptr = NULL;
        long value = std::strtol(arg.c_str(), &endptr, 10);
        if (*endptr != '\0'){
            std::cout << "Error: invalid characters in: " << arg << std::endl;
            return (false);
        }
        if (errno == ERANGE || value > INT_MAX){
            std::cout << "Error: number out of range: " << arg << std::endl;
            return (false);
        }
        if (is_duplicate(result, static_cast<int>(value))){
            std::cout << "Error: duplicate number: " << arg << std::endl;
            return (false);
        }
        result.push_back(static_cast<int>(value));
    }
    if (result.empty()){
        std::cout << "Error: no arguments given" << std::endl;
        return (false);
    }
    return (true);
}

int main(int argc, char* argv[]){
    std::vector<int> values;

    if(!parse_arguments(argc, argv, values)){
        return (1);
    }

    std::cout<< "Parsed values: ";
    for(std::size_t i = 0; i < values.size(); ++i)
        std::cout << values[i] << " ";
    std::cout << std::endl;

    //TODO parse args

    //TODO validate that we are dealing with 
    //   positive int only, no copy number and the overflow
    
    //TODO fill our std:vector<int> and a std::list<int> with the same verified values

    //TODO show the before:...

    //TODO launch the sorting part on both containers, I shall use std::chrono for that end

    //TODO display "After..." + the time for both
    return(0);
}
