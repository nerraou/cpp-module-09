#pragma once

#include <map>
#include <iostream>
#include <fstream>
#include <ctime>
class BitcoinExchange
{
private:
	std::map<std::string, std::string> map;

private:
	void parseCSVFile(const std::string &path);
	void parseInputFile(const std::string &path);
	bool parsePrice(const char *priceString, float *price);

public:
	BitcoinExchange();

	BitcoinExchange(BitcoinExchange const &other);

	void printFile(const std::string &path);

	BitcoinExchange &operator=(BitcoinExchange const &other);

	~BitcoinExchange();
};
