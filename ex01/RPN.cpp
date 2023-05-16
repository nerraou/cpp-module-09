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
		if (this->isoperation(str[i]))
		{
			if (this->stack.size() < 2)
				throw("error");
			else
			{
				this->calcule(str[i]);
			}
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
	if (std::isdigit(*endPtr))
		throw "number > 10";
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

bool RPN::isoperation(char c)
{

	if (c == '+' || c == '-' || c == '/' || c == '*' || c == '%' || c == '=' || c == '^')
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
		printf("result [%d] \n", val1 + val2);
		this->stack.push(val1 + val2);
		break;

	case '-':
		val1 = this->stack.top();
		this->stack.pop();
		val2 = this->stack.top();
		this->stack.pop();
		printf("[%d]", val2 - val1);
		this->stack.push(val2 - val1);
		break;

	case '*':
		val1 = this->stack.top();
		this->stack.pop();
		val2 = this->stack.top();
		this->stack.pop();
		printf("result : [%d] \n", val1 * val2);
		this->stack.push(val1 * val2);
		break;

	case '/':
		val1 = this->stack.top();
		this->stack.pop();
		val2 = this->stack.top();
		this->stack.pop();
		if (val1 == 0)
			return;
		printf("[%d]", val2 / val1);
		this->stack.push(val2 / val1);
		break;

	// operator doesn't match any case constant +, -, *, /
	default:
		printf("Error! operator is not correct");
	}
}

RPN::~RPN()
{
}
