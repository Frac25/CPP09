#include"BitcoinExchange.hpp"

	Btc::Btc()
	{

	}

	Btc::~Btc()
	{

	}

	Btc::Btc(const Btc &copy)
	{
		*this = copy;
	}

	Btc& Btc::operator=(const Btc &copy)
	{
		(void) copy; //SDU
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
			std::cout << line << std::endl;
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
			std::cout << line << std::endl;
		}
		return(0);
	}