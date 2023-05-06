#include <iostream>
#include "BitcoinExchange.hpp"

int main(int ac, char *av[])
{
	BitcoinExchange bitcoin;

	if (ac != 2)
	{
		std::cout << "Error!" << std::endl;
		return (1);
	}
	bitcoin.printFile(av[1]);
	// std::cout << "hello bitcoin" << std::endl;
	return (0);
}