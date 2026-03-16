#ifndef RPN_HPP
# define RPN_HPP

#include<iostream>
#include<stack>
#include<cstdlib>

class RPN
{
	public :
		RPN();
		~RPN();
		RPN(const RPN& copy);
		RPN& operator=(const RPN& copy);

		RPN(const std::string& exp);

		void	check_exp(const std::string& exp);
		void	modif_stack(char c);
		double	operation(const char& c, const double& first, const double &second);

		std::stack<double> stack;
};

#endif