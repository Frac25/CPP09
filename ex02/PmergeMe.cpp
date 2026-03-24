#include "PmergeMe.hpp"

PmergeMe::PmergeMe()
{

}

PmergeMe::~PmergeMe()
{

}

PmergeMe::PmergeMe(const PmergeMe& copy)
{
	*this = copy;
}

PmergeMe& PmergeMe::operator=(const PmergeMe& copy)
{
	if(this != &copy)
		*this = copy;
	return(*this);
}

std::ostream& operator<<(std::ostream& os, const std::vector<std::pair< int, int > > &pairs)
{
	for(size_t i = 0; i < pairs.size(); i++)
		os << "(" << pairs[i].first << ","<< pairs[i].second << ") ";
	return(os);
}

std::ostream& operator<<(std::ostream& os, const std::vector<int> &vec)
{
	for(size_t i = 0; i < vec.size(); i++)
		std::cout << vec[i] << ", ";
	return(os);
}

std::ostream& operator<<(std::ostream& os, const std::deque<std::pair< int, int > > &pairs)
{
	for(size_t i = 0; i < pairs.size(); i++)
		os << "(" << pairs[i].first << ","<< pairs[i].second << ") ";
	return(os);
}

std::ostream& operator<<(std::ostream& os, const std::deque<int> &deq)
{
	for(size_t i = 0; i < deq.size(); i++)
		std::cout << deq[i] << ", ";
	return(os);
}

void PmergeMe::sort(std::vector<int>& vec)
{
	//Start sort vec
	if(vec.size() <=1)
		return;
//	std::cout << "vec : " << vec << std::endl;

	//make_pairs
	std::vector<std::pair< int, int > > pairs;
	size_t i;
	for(i = 0; i < vec.size() - 1 ; i += 2)
	{
		pairs.push_back(std::make_pair(vec[i], vec[i + 1]));
	}

	if(vec.size() %2 !=0)
		pairs.push_back(std::make_pair(vec[i], -1));

	//"sort_pairs"
	for(size_t i = 0; i < pairs.size(); i++)
	{
		if(pairs[i].second < pairs[i].first)
		{
			int tmp = pairs[i].second;
			pairs[i].second = pairs[i].first;
			pairs[i].first = tmp;
		}
	}
//	std::cout << pairs << std::endl;

	//split_pairs
	std::vector<int> vecb;
	std::vector<int> vecl;
	for(size_t i = 0; i < pairs.size(); i++)
	{
		vecb.push_back(pairs[i].second);
		vecl.push_back(pairs[i].first);
	}
//	std::cout << "vecb :" << vecb << std::endl;
//	std::cout << "vecl :" << vecl << std::endl;

	//Recursiv sort
	sort(vecb);

	//insert little in big
//	std::cout << "Vecb : " << vecb << std::endl;
//	std::cout << "Vecl : " << vecl << std::endl;

	for(size_t i = 0; i < vecl.size(); i++)
	{
		std::vector<int>::iterator pos = std::lower_bound(vecb.begin(), vecb.end(), vecl[i]);
		if(vecl[i] != -1)
			vecb.insert(pos, vecl[i]);
	}
	//register vecb
	vec = vecb;
}

void PmergeMe::sort(std::deque<int>& deq)
{
	//Start sort deq
	if(deq.size() <=1)
		return;
//	std::cout << "deq : " << deq << std::endl;

	//make_pairs
	std::vector<std::pair< int, int > > pairs;
	size_t i;
	for(i = 0; i < deq.size() - 1 ; i += 2)
	{
		pairs.push_back(std::make_pair(deq[i], deq[i + 1]));
	}

	if(deq.size() %2 !=0)
		pairs.push_back(std::make_pair(deq[i], -1));

	//"sort_pairs"
	for(size_t i = 0; i < pairs.size(); i++)
	{
		if(pairs[i].second < pairs[i].first)
			std::swap(pairs[i].second, pairs[i].first);
	}
//	std::cout << pairs << std::endl;

	//split_pairs
	std::deque<int> deqb;
	std::deque<int> deql;
	for(size_t i = 0; i < pairs.size(); i++)
	{
		deqb.push_back(pairs[i].second);
		deql.push_back(pairs[i].first);
	}
//	std::cout << "deqb :" << deqb << std::endl;
//	std::cout << "deql :" << deql << std::endl;

	//Recursiv sort
	sort(deqb);

	//insert little in big
//	std::cout << "Deqb : " << deqb << std::endl;
//	std::cout << "Deql : " << deql << std::endl;

	for(size_t i = 0; i < deql.size(); i++)
	{
		std::deque<int>::iterator pos = std::lower_bound(deqb.begin(), deqb.end(), deql[i]);
		if(deql[i] != -1)
			deqb.insert(pos, deql[i]);
	}
	//register deqb
	deq = deqb;

}













