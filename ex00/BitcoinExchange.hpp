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
	
	int		read_db(const std::string& db_name);
	int		read_input(const std::string& input_name);

	private :

	bool	check_date(const std::string& date);
	bool	check_value(const std::string& value);
	bool	check_line_input(const std::string& line);
	bool	get_rate(const std::string& date);
	void	print(void) const;

	std::map<std::string , double> db;
	double value_d;
	double rate;	


};


#endif