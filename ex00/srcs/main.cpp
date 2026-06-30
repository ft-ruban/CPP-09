// 1) take file as an argument and open it.
//   1.1) if no file send error "Error: no file provided."
//   1.2) if file could not be opened send "Error: Could not open file."
// DONE
// 2) FillData map
// 3) (obsolete) treat line x (x being the iteration, starting at 1 as line 1 until 
//    we reach end of input.txt)
//   3.1) line must use the format "date | value" else : "Error: bad date format"
//   3.2) line must be a valid date format: "Year-Month-Day" else : "Error: bad input => 
//   3.3) line must possess a valid value
//       3.3.1) so either a float or int else      "Error: invalid value type (neither an float or an int)."
//       3.3.2) need to be a pos value else        "Error: not a positive number."
//       3.3.3) need to be between 0 and 1000 else "Error: too large a number." 
//   3.4) check the DB to find the date, if the date cannot be found find the closest contained.
//   3.5) once date is found convert exchange rate (todo how to?) then print the result in the following format
//          "yyyy-mm-dd => <bitcoin> = <convert_result>\n"
//   3.6) x = x + 1 until we reach the EOF of our input.txt
//
// 4) cleanup part close / free wathever need to be closed/free then end of program.

//https://codesignal.com/learn/courses/fundamentals-of-text-data-manipulation-in-cpp/lessons/reading-text-files-in-cpp
//en.cppreference.com/cpp/error/exception
#include <fstream>
#include <iostream>
#include <sstream>
#include "../includes/BitcoinExchange.hpp"

//2009-01-02,0
int main (int argc, char *argv[]){
    try{
        if(argc != 2)
            throw std::invalid_argument("no path provided at launch.");
    } catch(const std::exception & e){
        std::cout<<"Error: "<<e.what()<<std::endl;
        return(1);
    }
    BitcoinExchange foo(argv[1], "./data.csv");
    try{
            foo.FileOpener();
            foo.TransferFilesContents();
            foo.Convertor();
    }   catch(const std::exception & e){
            std::cout<<"Error: "<<e.what()<<std::endl;
            return(1);
    }


    // std::cout<<"full file content:\n" <<foo.GetInput()<<std::endl;
    // std::cout<<"full data content:\n" <<foo.GetData()<<std::endl;
    return(0);
}