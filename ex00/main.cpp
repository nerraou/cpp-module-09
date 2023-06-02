#include <iostream>
#include "BitcoinExchange.hpp"

int main(int ac, char *av[])
{
	BitcoinExchange bitcoin;

	if (ac != 2)
	{
		std::cerr << "usage: " << av[0] << " input.csv" << std::endl;
		return (1);
	}
	try
	{
		bitcoin.getExchangeRate(av[1]);	
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << '\n';
	}
	
	return (0);
}
