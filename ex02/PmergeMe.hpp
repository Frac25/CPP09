#ifndef PMERGEME_HPP
# define PMERGEME_HPP

#include<iostream>
#include<cstdlib>
#include<cctype>
#include<vector>
#include<deque>
#include<ctime>
#include<utility>
#include<algorithm>


class PmergeMe
{
	public :

	PmergeMe();
	~PmergeMe();
	PmergeMe(const PmergeMe& copy);
	PmergeMe& operator=(const PmergeMe& copy);

	static void sort(std::vector<int>& vec);
	static void sort(std::deque<int>& dec);

};

std::ostream& operator<<(std::ostream& os, const std::vector<std::pair< int, int > > &pairs);
std::ostream& operator<<(std::ostream& os, const std::vector<int> &vec);
std::ostream& operator<<(std::ostream& os, const std::deque<std::pair< int, int > > &pairs);
std::ostream& operator<<(std::ostream& os, const std::deque<int> &dec);

#endif