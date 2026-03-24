# include "PmergeMe.hpp"

// ./PmergeMe `shuf -i 1-100000 -n 3000 | tr "\n" " "`

static bool isnumber(char* c)
{
	for(int i = 0; c[i] != '\0' ; i++)
	{
		if(!std::isdigit(c[i]))
			return(false);
	}
	return(true);
}

int main (int argc, char** argv)
{
	if(argc < 2)
	{
		std::cerr << "argc < 2" << std::endl;
		return(-1);
	}

	PmergeMe Pm;
	std::vector<int> vec_init;
	std::deque<int> deq_init;

	for(int i = 1; i < argc; i++)
	{
		if(isnumber(argv[i]))
		{
			vec_init.push_back(std::atoi(argv[i]));
			deq_init.push_back(std::atoi(argv[i]));
		}
		else
		{
			std::cerr << "enterb only positiv integer arguments" << std::endl;
			return(-1);
		}
	}

	try
	{
		std::cout << "Before : " << vec_init << std::endl;
		clock_t start = clock();
		PmergeMe::sort(vec_init);
		clock_t end = clock();
		double time = (double) (end - start) / CLOCKS_PER_SEC * 1e6;
		std::cout << "After = " << vec_init << std::endl;
		std::cout << "Range of " << argc << " elements with vec : " << time << " us" << std::endl;
				
		start = clock();
		PmergeMe::sort(deq_init);
		end = clock();
		time = (double) (end - start) / CLOCKS_PER_SEC * 1e6;
		std::cout << "Range of " << argc << " elements with deq : " << time << " us" << std::endl;
	}
	catch(std::exception &e)
	{
		std::cerr << e.what() << std::endl;
		return(-1);
	}
	return(0);
}