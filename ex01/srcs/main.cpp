#include <iostream>
#include "../includes/RPN.hpp"

int main(int argc, char* argv[]){
    if (argc < 2 || argc > 2){
        std::cerr<<"Wrong amount of argument provided, RPN is expecting a single one"<<std::endl;
        return(1);
    }
    RPN foo(argv[1]);
    try{
        foo.calculusTreatment();
        foo.printResult();
    }   catch(const std::exception & e){
            std::cout<<"Error"<<e.what()<<std::endl;
            return(2);
    }
    return(0);
}