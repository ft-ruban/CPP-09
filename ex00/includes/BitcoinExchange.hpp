#include <iostream>
#include <map>
#include <sstream>
#include <fstream>

class BitcoinException : public std::runtime_error{
    public:
        explicit BitcoinException(const std::string& msg)
            : std::runtime_error("BitcoinException: " + msg){}
        
        static BitcoinException FillDataError(const std::string& details){
            return BitcoinException("FillDataError: " + details);
        }

        static BitcoinException invalid_csv(const std::string& details){
            return BitcoinException("FillDataError: " + details);
        }
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
        std::string GetData() const; 

    private:
        std::map<std::string, int> data_;
        std::ostringstream content_;

};