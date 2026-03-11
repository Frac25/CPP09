# include "BitcoinExchange.hpp"

int main (int argc, char** argv)
{
	if(argc != 2)
	{
		std::cerr << "argc != 2" << std::endl;
		return(-1);
	}

	std::string file_name = argv[1];

	Btc wallet;
	wallet.read_db("data.csv");
	wallet.read_input(file_name);
	
//	wallet.print();
	
	return(0);
}