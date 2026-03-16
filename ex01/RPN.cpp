#include "RPN.hpp"


RPN::RPN()
{

}

RPN::~RPN()
{

}

RPN::RPN(const RPN& copy) : stack(copy.stack)
{

}

RPN& RPN::operator=(const RPN& copy)
{
	stack = copy.stack;
	return(*this);
}

RPN::RPN(const std::string& exp)
{
	check_exp(exp);

	for(std::string::const_iterator i = exp.begin(); i!= exp.end(); i++)
	{
		if(*i == ' ')
			continue;
		else
			modif_stack(*i);
	}
    if (this->stack.size() != 1)
        throw(std::invalid_argument("Invalid expression"));
    std::cout << this->stack.top() <<std::endl;
}

void RPN::check_exp(const std::string& exp)
{
	//cherche le premier caractère de la string qui n’appartient PAS à la liste donnée.
	if(exp.find_first_not_of("123456789+-*/ ") != std::string::npos)
		throw(std::invalid_argument("Error : Invalid argument"));
}

void RPN::modif_stack(char c)
{
	std::string ope = "+-*/";
	if(ope.find(c) != std::string::npos)
	{
		if(this->stack.size() < 2)
			throw(std::invalid_argument("error : invalid operation"));
		double first = this->stack.top();
		this->stack.pop();
		double second = this->stack.top();
		this->stack.pop();
		this->stack.push(operation(c, first, second));
	}
	else
		this->stack.push(c - '0');
}

double RPN::operation(const char& c, const double& first, const double &second)
{
	switch (c)
	{
		case '+':
			return(first + second);
		case '-':
			return(second - first);
		case '*':
			return(first * second);
		case '/':
			if(first == 0)
				throw(std::invalid_argument("Error : Division by 0"));
			return(second/first);
		default :
			throw(std::invalid_argument("Error : Invalid operator"));
	}
}