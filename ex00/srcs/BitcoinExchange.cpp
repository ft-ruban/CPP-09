#include "../includes/BitcoinExchange.hpp"

BitcoinExchange::BitcoinExchange(){

}

BitcoinExchange::BitcoinExchange(const std::string provided_path_txt, const std::string provided_path_csv){
    path_txt_ = provided_path_txt;
    path_csv_ = provided_path_csv;
}

BitcoinExchange::BitcoinExchange(const BitcoinExchange& other){
    this->data_ = other.data_;
    this->input_ << other.input_.str();
    this->input_.clear();
    this->path_txt_ = other.path_txt_ ;
    this->path_csv_ = other.path_csv_;
    this->textfile_.open(this->path_txt_.c_str());
    this->csvfile_.open(this->path_csv_.c_str());
}

BitcoinExchange& BitcoinExchange::operator=(const BitcoinExchange& other){
    if(this!= &other){
        this->data_ = other.data_;
        this->input_ << other.input_.str();
        this->input_.clear();
        this->path_txt_ = other.path_txt_ ;
        this->path_csv_ = other.path_csv_;
        if (this->textfile_.is_open())
            this->textfile_.close();
        if (this->csvfile_.is_open())
            this->csvfile_.close();
        this->textfile_.open(this->path_txt_.c_str());
        this->csvfile_.open(this->path_csv_.c_str());
    }
    return (*this);
}

BitcoinExchange::~BitcoinExchange(){
    if (this->textfile_.is_open())
        this->textfile_.close();
    if (this->csvfile_.is_open())
        this->csvfile_.close();
}

static bool isNumber(const std::string& s){
    std::string::const_iterator it = s.begin();

    while(it != s.end() && std::isdigit(*it)) 
        ++it;
    return(!s.empty() && it == s.end());
}

static bool convertIntoInteger(const std::string& date, int& to_convert
                                , const std::size_t& pos, const std::size_t& len){
    std::string buff = date.substr(pos, len);

    if(!isNumber(buff))
        return(false);
    to_convert = std::atoi(buff.c_str());
    return(to_convert != 0);
}

static bool isLeapYear(const int year){
    return((year % 4 == 0) &&
        ((year % 100 != 0) || (year % 400 == 0)));
}

static bool isDateFormatValid(const std::string& date){
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

static bool isZero(const std::string& s){
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

static float valueConvertor(const std::string& value){
    bool is_value_zero = isZero(value);
    float converted_value = atof(value.c_str());

    if((converted_value == 0 && is_value_zero == false) || std::isnan(converted_value)){
        std::cout<<"Error: value \""<<value<<"\" is currently not a floating or integer value."<<std::endl;
        return(INVALID_VALUE);
    }
    else if(converted_value > MAX_VALUE_ALLOWED){
        std::cout<<"Error: too large a number."<<std::endl;
        return(INVALID_VALUE);
    }
    else if(converted_value < LESSER_VALUE_ALLOWED){
        std::cout<<"Error: not a positive number."<<std::endl;
        return(INVALID_VALUE);
    }
    return(converted_value);
}

void BitcoinExchange::convertor(){
    std::string line;

    std::getline(textfile_, line);
    if(line != "date | value")
        throw BitcoinException::invalid_txt("Invalid .txt's first line");
    while(std::getline(textfile_, line)){
        std::size_t pos_of_separator = line.find(SEPARATOR_CHAR);
        if(pos_of_separator == std::string::npos){
            std::cout<<"Error: bad input => "<<line<<std::endl;
        }
        else{
            std::string date = line.substr(0, pos_of_separator - 1);
            if(!isDateFormatValid(date)){
                std::cout<<"Error: bad input => "<< date<<std::endl;
            }
            else{
                float converted_value = valueConvertor(line.substr(pos_of_separator + 2));
                if(converted_value != INVALID_VALUE){
                    exchangeRateFinder(date,converted_value);
                }
            }
        }
    }
} 

void BitcoinExchange::exchangeRateFinder(const std::string& date, const float& converted_value)const{
    std::map<std::string, float>::const_iterator it = data_.lower_bound(date);

    if(it == data_.end() || it->first > date)
        it--;
    std::cout<<date<< " => "<<converted_value<< " = "<< it->second * converted_value<<std::endl;
}

void BitcoinExchange::transferContentscsv(){
    std::string line;

    std::getline(csvfile_, line);
    if(line != "date,exchange_rate")
        throw BitcoinException::invalid_csv("Invalid .csv's first line.");
    while(std::getline(csvfile_, line)){
        std::size_t pos = line.find(',');
        std::string date = line.substr(0,pos);
        std::string rate = line.substr(pos + 1);
        data_.insert(std::make_pair(date, std::atof(rate.c_str())));
    }
}

void BitcoinExchange::fileOpener(){
    textfile_.open(path_txt_.c_str());
    if(!textfile_.is_open())
        throw std::invalid_argument("Failed to open file \'" + path_txt_ + "\'");
    csvfile_.open(path_csv_.c_str());
    if(!csvfile_.is_open())
        throw std::invalid_argument("failed to open .csv file \'" + path_csv_ + "\'");
}

const std::string BitcoinExchange::getInput()const{
    return(input_.str());
}

std::string BitcoinExchange::getData() const{
    std::ostringstream foo;
    std::string return_value;

    for(std::map<std::string, float>::const_iterator it = data_.begin();
        it != data_.end(); ++it)
            foo << "date: "<< it->first << " rate: "<<std::fixed<< std::setprecision(2)<<it->second<<std::endl;
    return_value = foo.str();
    return(return_value);
}