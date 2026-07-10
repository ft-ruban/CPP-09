#include <iostream>

#include "../includes/RPN.hpp"
//from ./bin/RPN "7 7 * 7 - c c a o"
//to 7 7 * 7 - c c a o%

int main(int argc, char* argv[]){
    if (argc < 2){
        std::cerr<<"No arguments provided."<<std::endl;
        return(1);
    }
    if(argc > 2){
        std::cerr<<"too much arguments provided."<<std::endl;
        return(1);
    }

    RPN foo(argv[1]);
    std::cout<<"Test"<<std::endl; //TODL
    foo.getRPN();

    try{
        // function transfer argv into private string?
        foo.calculusTreatment();
        // print result?
    }   catch(const std::exception & e){
            std::cout<<"Error: "<<e.what()<<std::endl;
            return(2);
    }
    //step 1 put in string so the treatment would be easier in theory?
    //step 2 make sure the 2 first char are numbers then third is an allowed token
    
    //argv[1] = "5 6 + 2 + 5 - 5"
    //allowed tokens are "+ - / *"

    //TOASK imo I do not need to parse what the user send me, but I wanna be sure firsthand

    //TODO process part here (would use the class probably)
        // Would require to make an error handler thing that show on the standard error
        // need to handle operations with the following tokens: "+-/*".
        // Find a container that is about stacks I guess
    return(0);
}


/*
personal note: require the first two char to be a number, then we keep in mind the result then take a new number do the sign bla bla bla, should not be that tough.

1 = num
2 = num
3 = symbol
4 = num
5 = symbol
6 = num
7 = symbol
[...]
*/