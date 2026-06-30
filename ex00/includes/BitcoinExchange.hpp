#include <iostream>
#include <map>
#include <sstream>
#include <fstream>

class BitcoinException : public std::runtime_error{
    public:
        BitcoinException(const std::string& msg)
            : std::runtime_error("FillData: " + msg){}
};

class BitcoinExchange{
    public:
        BitcoinExchange();
        BitcoinExchange(BitcoinExchange& other);
        BitcoinExchange& operator=(const BitcoinExchange& other);
        ~BitcoinExchange();

        void FillData();
        void FileOpener(int& argc, char* path_argv);
        const std::string GetContent();
        const std::string GetData(); 

    private:
        std::map<std::string, int> data_;
        std::ostringstream content_;

};