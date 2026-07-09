#include <fstream>
#include <iostream>
#include <sstream>
#include "../includes/BitcoinExchange.hpp"

int main (int argc, char *argv[]){
    try{
        if(argc != 2)
            throw std::invalid_argument("no path provided at launch.");
    } catch(const std::exception & e){
        std::cout<<"Error: "<<e.what()<<std::endl;
        return(EXIT_FAILURE);
    }
    BitcoinExchange foo(argv[1], "./data.csv");
    try{
            foo.fileOpener();
            foo.transferContentscsv();
            foo.convertor();
    }   catch(const std::exception & e){
            std::cout<<"Error: "<<e.what()<<std::endl;
            return(EXIT_FAILURE);
    }
    return(EXIT_SUCCESS);
}