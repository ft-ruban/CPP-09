#include <iostream>
#include <map>
#include <sstream>
#include <fstream>
#include <cstdlib>
#include <iomanip> //precision stdout

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
        BitcoinExchange(std::string provided_path_txt, std::string provided_path_csv);
        BitcoinExchange(BitcoinExchange& other);
        BitcoinExchange& operator=(const BitcoinExchange& other);
        ~BitcoinExchange();

        void TransferFilesContents();
        void FileOpener();
        void Convertor();
        
        const std::string GetInput();
        std::string GetData() const; 

    private:
        std::map<std::string, float> data_;
        std::ostringstream input_;
        std::string path_txt_;
        std::string path_csv_;
        std::ifstream textfile_;
        std::ifstream csvfile_;

};