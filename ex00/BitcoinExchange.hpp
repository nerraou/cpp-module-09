#pragma once

#include <map>
#include <iostream>
#include <fstream>
#include <exception>
#include <ctime>

#define DATA_PATH "../cpp_09/data.csv"
class BitcoinExchange
{
private:
	std::map<std::string, std::string> map;

private:
	void parseCSVFile(const std::string &path);
	void parseInputFile(const std::string &path);
	void parsePrice(const char *priceString, float *price);
	void parseDate(std::string &date);

public:
	BitcoinExchange();

	BitcoinExchange(BitcoinExchange const &other);

	void getExchangeRate(const std::string &path);

	BitcoinExchange &operator=(BitcoinExchange const &other);

	~BitcoinExchange();

	class NotPositive : public std::exception
	{
	public:
		NotPositive();
		virtual ~NotPositive() throw();
		virtual const char *what() const throw();
	};

	class PriceTooHigh : public std::exception
	{
	public:
		PriceTooHigh();
		virtual ~PriceTooHigh() throw();
		virtual const char *what() const throw();
	};
	class BadDateFormat : public std::exception
	{
	protected:
		std::string date;
		std::string message;

	public:
		BadDateFormat(std::string &date);
		virtual ~BadDateFormat() throw();
		virtual const char *what() const throw();
	};
};
