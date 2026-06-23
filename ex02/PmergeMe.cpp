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

static size_t jacobsthal(size_t n)
{
	if (n == 0)
		return 0;
	if (n == 1)
		return 1;

	size_t a = 0;
	size_t b = 1;

	for (size_t i = 2; i <= n; ++i)
	{
		size_t tmp = b + 2 * a;
		a = b;
		b = tmp;
	}
	return b;
}

std::vector<size_t> buildJacobOrder(size_t size)
{
	std::vector<size_t> order;

	if (size == 0)
		return order;

	order.push_back(0);

	size_t prev = 1;
	size_t k = 3;

	while (true)
	{
		size_t curr = jacobsthal(k);

		if (curr >= size)
			curr = size;

		for (size_t i = curr; i > prev; --i)
			order.push_back(i - 1);

		if (curr == size)
			break;

		prev = curr;
		++k;
	}

	return order;
}


void PmergeMe::sort(std::vector<int>& vec)
{
	//recursive end condition
	if(vec.size() <=1)
		return;

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

	//split_pairs
	std::vector<int> vecb;
	std::vector<int> vecl;
	for(size_t i = 0; i < pairs.size(); i++)
	{
		vecb.push_back(pairs[i].second);
		vecl.push_back(pairs[i].first);
	}

	//Recursiv sort
	sort(vecb);

	//insert little in big whith jacobstal
	std::vector<size_t> order = buildJacobOrder(vecl.size());

	for (size_t i = 0; i < order.size(); ++i)
	{
		size_t idx = order[i];

		if (vecl[idx] == -1)
			continue;

		std::vector<int>::iterator pos =
			std::lower_bound(
				vecb.begin(),
				vecb.end(),
				vecl[idx]);

		vecb.insert(pos, vecl[idx]);
	}

/*	//insert little in big
	for(size_t i = 0; i < vecl.size(); i++)
	{
		std::vector<int>::iterator pos = std::lower_bound(vecb.begin(), vecb.end(), vecl[i]);
		if(vecl[i] != -1)
			vecb.insert(pos, vecl[i]);
	}
*/
	//register vecb
	vec = vecb;
}

void PmergeMe::sort(std::deque<int>& deq)
{
	//Start sort deq
	if(deq.size() <=1)
		return;

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

	//split_pairs
	std::deque<int> deqb;
	std::deque<int> deql;
	for(size_t i = 0; i < pairs.size(); i++)
	{
		deqb.push_back(pairs[i].second);
		deql.push_back(pairs[i].first);
	}

	//Recursiv sort
	sort(deqb);

	//insert little in big whith jacostal
	std::vector<size_t> order = buildJacobOrder(deql.size());

	for (size_t i = 0; i < order.size(); ++i)
	{
		size_t idx = order[i];

		if (deql[idx] == -1)
			continue;

		std::deque<int>::iterator pos =
			std::lower_bound(
				deqb.begin(),
				deqb.end(),
				deql[idx]);

		deqb.insert(pos, deql[idx]);
	}

	//insert little in big
/*	for(size_t i = 0; i < deql.size(); i++)
	{
		std::deque<int>::iterator pos = std::lower_bound(deqb.begin(), deqb.end(), deql[i]);
		if(deql[i] != -1)
			deqb.insert(pos, deql[i]);
	}
*/
	//register deqb
	deq = deqb;

}













