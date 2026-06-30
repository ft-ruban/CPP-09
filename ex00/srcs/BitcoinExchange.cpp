#include "../includes/BitcoinExchange.hpp"

BitcoinExchange::BitcoinExchange(){

}

BitcoinExchange::BitcoinExchange(std::string provided_path_txt, std::string provided_path_csv){
    path_txt_ = provided_path_txt;
    path_csv_ = provided_path_csv;
}

BitcoinExchange::BitcoinExchange(BitcoinExchange& other){
    this->data_ = other.data_;
    // TODO : this->content_ = other.content_;
}

BitcoinExchange& BitcoinExchange::operator=(const BitcoinExchange& other){
    if(this!= &other){
        data_ = other.data_;
        //TODO : this->content_ = other.content_;
    }
    return (*this);
}

BitcoinExchange::~BitcoinExchange(){
}

void BitcoinExchange::TransferFilesContents(){
    std::string line;
    std::size_t pos;
    std::string date;
    std::string rate;

    input_ << textfile_.rdbuf();
    std::getline(csvfile_, line);
    if(line != "date,exchange_rate")
        throw BitcoinException::invalid_csv("Invalid .csv's first line.");
    while(std::getline(csvfile_, line)){
        pos = line.find(',');
        date = line.substr(0,pos);
        rate = line.substr(pos + 1);
        data_.insert(std::make_pair(date, std::atof(rate.c_str())));
    }
}

void BitcoinExchange::FileOpener(){

    textfile_.open(path_txt_.c_str());
    if(!textfile_.is_open())
        throw std::invalid_argument("Failed to open file \'" + path_txt_ + "\'");
    csvfile_.open(path_csv_.c_str());
    if(!csvfile_.is_open())
        throw std::invalid_argument("failed to open .csv file \'" + path_csv_ + "\'");
}

void Convertor(){
    
}

const std::string BitcoinExchange::GetInput(){
    return(input_.str());
}

//still have to test it.
std::string BitcoinExchange::GetData() const{
    std::ostringstream foo;
    std::string return_value;

for(std::map<std::string, float>::const_iterator it = data_.begin();
    it != data_.end(); ++it)
        foo << "date: "<< it->first << " rate: "<<std::fixed<< std::setprecision(2)<<it->second<<std::endl;
    return_value = foo.str();
    return(return_value);
}