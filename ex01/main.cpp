#include "RPN.hpp"

int main(int ac, char *av[])
{
	if (ac != 2)
	{
		std::cerr << "usage: " << av[0] << " an inverted Polish mathematical" << std::endl;
		return (1);
	}
	RPN rpn;

	rpn.executeRPN(av[1]);
	return (0);
}
