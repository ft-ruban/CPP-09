#include "../includes/BitcoinExchange.hpp"

BitcoinExchange::BitcoinExchange(){

}

BitcoinExchange::BitcoinExchange(BitcoinExchange& other){
    this->data_ = other.data_;
}

BitcoinExchange& BitcoinExchange::operator=(const BitcoinExchange& other){
    if(this!= &other)
        data_ = other.data_;
    return (*this);
}

BitcoinExchange::~BitcoinExchange(){

}

void BitcoinExchange::FillData(){
    //while loop until csv file at EOF
        //for each lines we data_.insert(std::make_pair"date", num);
}

void BitcoinExchange::FileOpener(int argc, char *argv[]){
    if(argc != 2)
        throw std::invalid_argument( "No path provided at launch.");
    std::string file_path = argv[1];
    std::ifstream file(file_path.c_str());
    if(!file.is_open())
        throw std::invalid_argument("Failed to open file \'" + file_path + "\'");
    content_ << file.rdbuf();
}

std::string BitcoinExchange::GetContent(){
    return(content_.str());
}

//still have to test it.
std::string BitcoinExchange::GetData(){
    std::ostringstream foo;
    std::string return_value;
for(std::map<std::string, int>::const_iterator it = data_.begin();
    it != data_.end(); ++it)
{
    foo << it->first << "\n";
}
    return_value = foo.str();
    return(return_value);
}