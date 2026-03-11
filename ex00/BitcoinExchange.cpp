#include"BitcoinExchange.hpp"

Btc::Btc() : result_d(0)
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
		std::string rate_string;

		std::stringstream ss(line);
		std::getline(ss, date, ',');
		std::getline(ss, rate_string);
		db[date] = std::strtod(rate_string.c_str(),NULL);
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
		if(!check_line_input(line))
			std::cout << "error: line format KO => " << line << std::endl;
		else
		{
			std::string date;
			std::string value;
			std::string dust;

			std::stringstream ss(line);
			std::getline(ss, date, ' ');
			std::getline(ss, dust, ' ');
			std::getline(ss, value);
			if(!check_date(date))
				std::cout << "error: bad input => " << date << std::endl;
			else
			{
				if(check_value(value))
				{
					if(!get_rate(date))
						std::cout << "error: no earlier data available " << date << std::endl;
					else
						std::cout << date << " => " << value << " = " << rate * result_d << std::endl;
				}
			}
		}
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
			return (false);
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
	char * end;

	result_d = std::strtod(value.c_str(), &end);

	if(*end != '\0')
	{
		std::cout << "error: rate KO " << std::endl;
		result_d = 0;
		return(false);
	}
	if(result_d < 0)
	{
		std::cout << "error: not a positive number " << std::endl;
		result_d = 0;
		return(false);
	}
	if(result_d > 1000)
	{
		std::cout << "error: too large number " << std::endl;
		result_d = 0;
		return(false);
	}
	return(true);
}

bool Btc::check_line_input(const std::string& line)
{
	if(line[10] != ' ' || line[11] != '|' || line[12] != ' ')
		return (false);
	if (!(std::isdigit(line[13]) || line[13] == '-'))
		return (false);
	return(true);
}

bool	Btc::get_rate(const std::string& date)
{
	std::map<std::string, double>::iterator it;

	it = db.lower_bound(date);

	if(it != db.begin() && (it == db.end() || it->first != date))
		--it;

	if(it == db.begin() && date < it->first)
	{
		rate = 0;
		return(false);
	}

	rate = it->second;
	return(true);
}