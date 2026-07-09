#include <iostream>
#include <map>
#include <sstream>
#include <fstream>
#include <cstdlib>
#include <iomanip>
#include <cmath>

#define INVALID_VALUE -42
#define SEPARATOR_CHAR '|'
#define MAX_VALUE_ALLOWED 1000
#define LESSER_VALUE_ALLOWED 0
#define JANUARY   2
#define APRIL     4
#define JUNE      6
#define SEPTEMBER 9
#define NOVEMBER  11
#define DATE_SEPARATOR '-'

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
        static BitcoinException invalid_txt(const std::string& details){
            return BitcoinException("ConvertorError: " + details);
        }
};

class BitcoinExchange{
    public:
        BitcoinExchange();
        BitcoinExchange(const std::string provided_path_txt, const std::string provided_path_csv);
        BitcoinExchange(const BitcoinExchange& other);
        BitcoinExchange& operator=(const BitcoinExchange& other);
        ~BitcoinExchange();

        void transferContentscsv();
        void fileOpener();
        void convertor();
        void exchangeRateFinder(const std::string& date, const float& converted_value)const;
        
        const std::string getInput() const;
        std::string getData() const; 

    private:
        std::map<std::string, float> data_;
        std::ostringstream input_;
        std::string path_txt_;
        std::string path_csv_;
        std::ifstream textfile_;
        std::ifstream csvfile_;
};