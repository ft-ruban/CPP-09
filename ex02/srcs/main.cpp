#include <climits>
#include <iostream>
#include <vector>
#include <cstdlib>
#include <sys/time.h>

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

template <typename Container>
void print_container(const std::string& label, const Container& c)
{
    std::cout << label;
    for (typename Container::const_iterator it = c.begin(); it != c.end(); ++it)
        std::cout << *it << " ";
    std::cout << std::endl;
}

int main(int argc, char* argv[]){
    std::vector<int> values;

    if(!parse_arguments(argc, argv, values)){
        return (1);
    }

    PmergeMe pmerge(values);
    print_container("Before: ", pmerge.getVector());


    struct timeval start_vec, end_vec;
    gettimeofday(&start_vec, NULL);
    //pmerge.sortVector(); TODO implement algo
    gettimeofday(&end_vec, NULL);
    double time_vec = (end_vec.tv_sec - start_vec.tv_sec) * 1000000.0 + (end_vec.tv_usec - start_vec.tv_usec);
   
    struct timeval start_list, end_list;
    gettimeofday(&start_list, NULL);
    //pmerge.sortList(); TODO implement algo
    gettimeofday(&end_list, NULL);
    double time_list = (end_list.tv_sec - start_list.tv_sec) * 1000000.0 + (end_list.tv_usec - start_list.tv_usec);
    
    print_container("After: ", pmerge.getVector());

    std::cout << "Time to process a range of " << values.size()
              << " elements with std::vector : " << time_vec << " us" << std::endl;
    std::cout << "Time to process a rage of " << values.size()
              << " elements with std::list : " << time_list << " us" << std::endl;

    return(0);
}
