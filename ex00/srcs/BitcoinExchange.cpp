#include "../includes/BitcoinExchange.hpp"

BitcoinExchange::BitcoinExchange(){

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

void BitcoinExchange::FillData(){
    std::string line;
    std::string file_path = "./data.csv";
    std::ifstream file(file_path.c_str());
    
    if(!file.is_open())
        throw BitcoinException::FillDataError("Couldn't open our .csv file, make sure \'"+ file_path +"\' does exist.");
    std::getline(file, line);
    if(line != "date,exchange_rate")
        throw BitcoinException::invalid_csv("Invalid .csv's first line.");

    while(std::getline(file, line)){
        std::size_t pos = line.find(',');
        std::string date = line.substr(0,pos);
        std::string rate = line.substr(pos + 1);

        data_.insert(std::make_pair(date, std::atof(rate.c_str())));
    }
}

void BitcoinExchange::FileOpener(int& argc, char* path_argv){
    if(argc != 2)
        throw std::invalid_argument( "No path provided at launch.");
    std::string file_path = path_argv;
    std::ifstream file(file_path.c_str());
    if(!file.is_open())
        throw std::invalid_argument("Failed to open file \'" + file_path + "\'");
    content_ << file.rdbuf();
}

const std::string BitcoinExchange::GetContent(){
    return(content_.str());
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