#include"BitcoinExchange.hpp"

Btc::Btc()
{
}

Btc::~Btc()
{
}

Btc::Btc(const Btc &copy) : db(copy.db)
{
}

Btc& Btc::operator=(const Btc &copy)
{
	db = copy.db;
	return(*this);
}

int Btc::read_db(const std::string& db_name)
{
	std::ifstream file(db_name.c_str());
	if(!file.is_open())
	{
		std::cerr << "error opening file" << std::endl;
		return(-1);
	}
	std::string line;
	std::getline(file, line);
	while (std::getline(file, line))
	{
		std::string date;
		std::string rate;

		std::stringstream ss(line);
		std::getline(ss, date, ',');
		std::getline(ss, rate);
		double rate_double = std::strtod(rate.c_str(),NULL);
		db[date] = rate_double;
	//	std::cout << line << " | " << date << " | " << db[date] << std::endl;
	}
	return(0);
}

int Btc::read_input(const std::string& input_name)
{
	std::ifstream file(input_name.c_str());
	if(!file.is_open())
	{
		std::cerr << "error opening file" << std::endl;
		return(-1);
	}
	std::string line;
	std::getline(file, line);
	while (std::getline(file, line))
	{
		std::string date;
		std::string value;

		std::stringstream ss(line);
		std::getline(ss, date, '|');
		std::getline(ss, value);
		if(check_date(date))
			std::cout << "date error" << std::endl;
		else
			std::cout << date << std::endl;
	}
	return(0);
}

void Btc::print(void) const
{
	for (std::map<std::string, double>::const_iterator it = db.begin(); it != db.end(); ++it)
	{
		std::cout << it->first << " , " << it->second << std::endl;
	}
}

bool Btc::check_date(const std::string& date)
{
	if(date.length() != 10 || date[4] != '-' || date[7] != '-')
		return (false);
	
	for (int i = 0; i < 4; i++)
	{
		if (!std::isdigit(date[i]))
			return(false);
	}

	for (int i = 5; i < 7; i++)
	{
		if (!std::isdigit(date[i]))
			return(false);
	}
	int month = std::atoi(date.substr(5,2).c_str());
	if(month < 1 || month > 12 )
		return(false);
	
	for (int i = 8; i < 10; i++)
	{
		if (!std::isdigit(date[i]))
			return(false);
	}
	int day = std::atoi(date.substr(8,2).c_str());
	if(day < 1 || day > 31 )
		return(false);

	return(true);
}

bool Btc::check_value(const std::string& value)
{
	(void)value;

	return(0);
}