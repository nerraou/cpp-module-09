#pragma once

#include <iostream>
#include <stack>
#include <exception>

class RPN
{
private:
	std::stack<int> stack;
	void parseNumber(const char *str);
	void printStack();
	bool isAllowedOperation(char c);
	void calcule(char c);

public:
	RPN();

	RPN(RPN const &other);

	RPN &operator=(RPN const &other);

	void executeRPN(const std::string &expression);

	~RPN();

	class Errors : public std::exception
	{
	protected:
		const char *ErrorMessage;

	public:
		Errors(const char *message);
		virtual ~Errors() throw();
		virtual const char *what() const throw();
	};
};
