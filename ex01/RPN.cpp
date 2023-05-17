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
	try
	{

		while (str[i] != '\0')
		{
			while (std::isspace(str[i]))
				i++;

			if (!std::isdigit(str[i]) && !this->isAllowedOperation(str[i]))
				throw(RPN::Errors("Error"));
			if (std::isdigit(str[i]))
			{
				this->parseNumber(str + i);
				i++;
			}
			if (this->isAllowedOperation(str[i]))
			{
				if (this->stack.size() < 2)
					throw(RPN::Errors("Error"));
				else
					this->calcule(str[i]);
			}
			if (str[i] != '\0')
				i++;
		}
		if (this->stack.size() != 1)
			throw(RPN::Errors("Error: stack size != 1"));

		this->printStack();
	}
	catch (const std::exception &e)
	{
		std::cerr << e.what() << '\n';
	}
}

void RPN::parseNumber(const char *str)
{
	char *endPtr;
	int number;

	number = std::strtol(str, &endPtr, 10);

	if (number >= 10)
		throw(RPN::Errors("Error: number >= 10"));
	if (endPtr == NULL || *endPtr == '\0' || *endPtr != ' ')
		throw(RPN::Errors("Error: invalid number"));
	if (std::isdigit(*endPtr))
		throw(RPN::Errors("Error: invalid number"));
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

bool RPN::isAllowedOperation(char c)
{

	if (c == '+' || c == '-' || c == '/' || c == '*')
		return true;
	return false;
}

void RPN::calcule(char c)
{
	int val1;
	int val2;

	switch (c)
	{
	case '+':
		val1 = this->stack.top();
		this->stack.pop();
		val2 = this->stack.top();
		this->stack.pop();
		this->stack.push(val1 + val2);
		break;

	case '-':
		val1 = this->stack.top();
		this->stack.pop();
		val2 = this->stack.top();
		this->stack.pop();
		this->stack.push(val2 - val1);
		break;

	case '*':
		val1 = this->stack.top();
		this->stack.pop();
		val2 = this->stack.top();
		this->stack.pop();
		this->stack.push(val1 * val2);
		break;

	case '/':
		val1 = this->stack.top();
		this->stack.pop();
		val2 = this->stack.top();
		this->stack.pop();
		if (val1 == 0)
			throw(RPN::Errors("Error: cannot divide by zero!"));
		this->stack.push(val2 / val1);
		break;
	}
}

RPN::~RPN()
{
}

RPN::Errors::Errors(const char *message)
{
	this->ErrorMessage = message;
}

RPN::Errors::~Errors() throw()
{
}

const char *RPN::Errors::what() const throw()
{
	return (this->ErrorMessage);
}
