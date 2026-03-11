#ifndef BITCOINEXCHANGE_HPP
# define BITCOINEXCHANGE_HPP

#include <iostream>
#include <fstream>
#include <sstream>
# include <map>

class Btc
{
	public :

	Btc();
	~Btc();
	Btc(const Btc &copy);
	Btc& operator=(const Btc &copy);
	
	std::map<std::string , double> db;

	int read_db(const std::string& db_name);
	int read_input(const std::string& input_name);


};


#endif