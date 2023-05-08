#include "RPN.hpp"

RPN::RPN()
{
}

RPN::RPN(RPN const &other)
{
	*this = other;
}

RPN &RPN::operator=(RPN const &other)
{
	this->stack = other.stack;
	return (*this);
}

void RPN::executeRPN(const std::string &expression)
{
	const char *str = expression.c_str();
	int i;

	i = 0;
	while (str[i] != '\0')
	{
		while (std::isspace(str[i]))
		{
			i++;
		}
		if (std::isdigit(str[i]))
		{
			this->parseNumber(str + i);
			i++;
		}

		if (str[i] != '\0')
			i++;
	}
	this->printStack();

	// skip spaces
	// if isdigit insert in stack
	//    if number > 10 throw
	// if is operator check for stack size
	// 		if stack size > 2
	// 			calculate
	// 		else throw
	// else throw
	// check for stack size
	// 	if size != 1 throw
	// 	else print
}

void RPN::parseNumber(const char *str)
{
	char *endPtr;
	int number;

	number = std::strtol(str, &endPtr, 10);

	if (number >= 10)
		throw "invalid number";
	if (endPtr == NULL || *endPtr == '\0' || *endPtr != ' ')
		throw "invalid number";
	std::cout << "num: " << number << std::endl;
	this->stack.push(number);
}

void RPN::printStack()
{
	while (!this->stack.empty())
	{
		std::cout << "[ " << this->stack.top() << " ]" << std::endl;
		this->stack.pop();
	}
}

RPN::~RPN()
{
}
