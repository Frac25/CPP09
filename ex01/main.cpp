# include "RPN.hpp"

int main (int argc, char** argv)
{
	if(argc != 2)
	{
		std::cerr << "argc != 2" << std::endl;
		return(-1);
	}

	std::string exp = argv[1];

	try
	{
		RPN result(exp);
	}
	catch(std::exception &e)
	{
		std::cerr << e.what() << std::endl;
		return(-1);
	}
	return(0);
}