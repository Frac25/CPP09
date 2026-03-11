#ifndef BITCOINEXCHANGE_HPP
# define BITCOINEXCHANGE_HPP

#include <iostream>
#include <fstream>
#include <sstream>
#include <map>
#include <cstdlib>

class Btc
{
	public :

	Btc();
	~Btc();
	Btc(const Btc &copy);
	Btc& operator=(const Btc &copy);
	
	std::map<std::string , double> db;
	double result_d;
	double rate;

	void	print(void) const;

	int		read_db(const std::string& db_name);
	int		read_input(const std::string& input_name);
	bool	check_date(const std::string& date);
	bool	check_value(const std::string& value);
	bool	check_line_input(const std::string& line);
	bool	get_rate(const std::string& date);

};


#endif