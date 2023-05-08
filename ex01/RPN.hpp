#pragma once

#include <iostream>
#include <stack>

class RPN
{
private:
	std::stack<int> stack;
	void parseNumber(const char *str);
	void printStack();

public:
	RPN();

	RPN(RPN const &other);

	RPN &operator=(RPN const &other);

	void executeRPN(const std::string &expression);

	~RPN();
};
