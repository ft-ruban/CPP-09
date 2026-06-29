#include <iostream>
#include <map>
#include <sstream>
#include <fstream>

class BitcoinExchange{
    public:
        BitcoinExchange();
        BitcoinExchange(BitcoinExchange& other);
        BitcoinExchange& operator=(const BitcoinExchange& other);
        ~BitcoinExchange();

        void FillData();
        void FileOpener(int argc, char *argv[]);
        std::string GetContent();
        std::map<std::string, int> GetData_(); 

    private:
        std::map<std::string, int> data_;
        std::ostringstream content_;

};