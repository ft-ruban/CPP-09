// 1) take file as an argument and open it.
//   1.1) if no file send error "Error: no file provided."
//   1.2) if file could not be opened send "Error: Could not open file."
//
// 2) (obsolete) treat line x (x being the iteration, starting at 1 as line 1 until 
//    we reach end of input.txt)
//   2.1) line must use the format "date | value" else : "Error: bad date format"
//   2.2) line must be a valid date format: "Year-Month-Day" else : "Error: bad input => 
//   2.3) line must possess a valid value
//       2.3.1) so either a float or int else      "Error: invalid value type (neither an float or an int)."
//       2.3.2) need to be a pos value else        "Error: not a positive number."
//       2.3.3) need to be between 0 and 1000 else "Error: too large a number." 
//   2.4) check the DB to find the date, if the date cannot be found find the closest contained.
//   2.5) once date is found convert exchange rate (todo how to?) then print the result in the following format
//          "yyyy-mm-dd => <bitcoin> = <convert_result>\n"
//   2.6) x = x + 1 until we reach the EOF of our input.txt
//
// 3) cleanup part close / free wathever need to be closed/free then end of program.

//https://codesignal.com/learn/courses/fundamentals-of-text-data-manipulation-in-cpp/lessons/reading-text-files-in-cpp
//en.cppreference.com/cpp/error/exception
#include <fstream>
#include <iostream>
#include <sstream>
#include "../includes/BitcoinExchange.hpp"

//2009-01-02,0
int main (int argc, char *argv[]){
    BitcoinExchange foo;
    try{
            foo.FileOpener(argc, argv);
            //TODO: start filldata (shall review our steps too)

    }   catch(const std::exception & e){
            std::cout<<"Error: BitcoinOpener: "<<e.what()<<std::endl;
            return(1);
    }
    std::cout<<"full file content:\n" <<foo.GetContent()<<std::endl;
    return(0);
}