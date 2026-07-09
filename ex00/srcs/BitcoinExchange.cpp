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

    // input_ << textfile_.rdbuf();
    std::getline(csvfile_, line);
    if(line != "date,exchange_rate")
        throw BitcoinException::invalid_csv("Invalid .csv's first line.");
    while(std::getline(csvfile_, line)){
        pos = line.find(',');
        date = line.substr(0,pos);
        rate = line.substr(pos + 1);
        //std::cout<<"TEST TODL rate is now egal to = "<<rate<<std::endl;
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

//const iterator = only to read
static bool isNumber(const std::string& s){
    std::string::const_iterator it = s.begin();

    while(it != s.end() && std::isdigit(*it)) ++it;
    return(!s.empty() && it == s.end());
}


static bool convertIntoInteger(const std::string& date, int& to_convert
                                , const std::size_t pos, const std::size_t len){
    std::string buff = date.substr(pos, len);

    if(!isNumber(buff))
        return(false);
    to_convert = std::atoi(buff.c_str());
    if(to_convert == 0)
        return(false);
    return(true);
}

static bool isLeapYear(int year){
    return((year % 4 == 0) &&
        ((year % 100 != 0) || (year % 400 == 0)));
}

static bool isDateFormatValid(const std::string date){
    int year = 0;
    int month = 0;
    int day = 0;

    if(date[4] != DATE_SEPARATOR || date[7] != DATE_SEPARATOR || date.length() != 10)
        return(false);
    if  (!convertIntoInteger(date, year, 0, 4) ||
            !convertIntoInteger(date, month, 5, 2) || 
            !convertIntoInteger(date,day, 8, 2))
                return(false);
    switch(month){
        case APRIL: case JUNE: case SEPTEMBER: case NOVEMBER:
            if(day > 30)
                return (false);
            break;
        case JANUARY:
            if(day > 29 || (day == 29 && !isLeapYear(year))){
                return (false);
            }
            break;
        default:
            if(day > 31 || month > 12){
                return(false);
            }
            break;
    }
    return(true);
}

bool isZero(std::string s){
    bool is_float = false;

    for(int i = s.size() - 1; i >= 0; i--){
        if(i == 0 && s[i] == '-')
            break;
        if(is_float == false && s[i] == '.')
            is_float = true;
        else if(s[i] != '0')
            return(false);
    }
    return(true);
}

float valueConvertor(std::string value){
    bool is_value_zero = false;
    float return_value;

    is_value_zero = isZero(value);
    return_value = atof(value.c_str());
    if((return_value == 0 && is_value_zero == false) || std::isnan(return_value)){
        std::cout<<"Error: value \""<<value<<"\" is currently not a floating or integer value."<<std::endl;
        return(INVALID_VALUE);
    }
    else if(return_value > 1000){
        std::cout<<"Error:value \""<<value<<" \" too large a number"<<std::endl; //TODO rm value when product is finished.
        return(INVALID_VALUE);
    }
    else if(return_value < 0){
        std::cout<<"Error: not a positive number."<<std::endl;
        return(INVALID_VALUE);
    }
    return(return_value);
}

void BitcoinExchange::exchangeRateFinder(std::string date, float converted_value){
    std::map<std::string, float>::iterator it;

    it = data_.lower_bound(date);
    if(it == data_.end() || it->first > date)
        it--;
    std::cout<<date<< " => "<<converted_value<< " = "<< it->second * converted_value<<std::endl;
}

void BitcoinExchange::Convertor(){
    std::string line = input_.str();
    std::size_t pos;
    std::string date;
    float converted_value;

    std::getline(textfile_, line);
    if(line != "date | value")
        throw BitcoinException::invalid_csv("Invalid .txt's first line"); //todo change error type here
    while(std::getline(textfile_, line)){
        pos = line.find('|');
        if(pos == std::string::npos){
            std::cout<<"Error: bad input => "<<line<<std::endl;
        }
        else{
            date = line.substr(0, pos - 1); //probably a way to put it in isDateFormatValid
        if(!isDateFormatValid(date)){
            std::cout<<"Error: bad input => "<< date<<std::endl;
        }
        else{
            converted_value = valueConvertor(line.substr(pos + 2));
            if(converted_value != -1){
                exchangeRateFinder(date,converted_value);
           }
        }

        }
    }
}  

const std::string BitcoinExchange::GetInput(){
    return(input_.str());
}

std::string BitcoinExchange::GetData() const{
    std::ostringstream foo;
    std::string return_value;

    for(std::map<std::string, float>::const_iterator it = data_.begin();
        it != data_.end(); ++it)
            foo << "date: "<< it->first << " rate: "<<std::fixed<< std::setprecision(2)<<it->second<<std::endl;
    return_value = foo.str();
    return(return_value);
}
