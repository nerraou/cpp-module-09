#include "BitcoinExchange.hpp"

void BitcoinExchange::parseCSVFile(const std::string &path)
{
	std::ifstream data(path);
	std::string line;
	std::size_t pos;

	if (data.is_open() && data.good())
	{
		getline(data, line);
		while (getline(data, line))
		{
			pos = line.find(",");
			this->map.insert(std::pair<std::string, std::string>(line.substr(0, pos), line.substr(pos + 1)));
		}
	}
	else
		throw std::runtime_error("can not open file!");
}

void BitcoinExchange::parseInputFile(const std::string &path)
{
	std::ifstream data(path);
	std::string line;
	std::size_t pos;
	float price;
	float exchangeRate;

	if (!data.is_open() || !data.good())
		throw std::runtime_error("can not open file!");

	getline(data, line);
	while (getline(data, line))
	{
		pos = line.find(" | ");
		std::string date = line.substr(0, pos);
		std::string priceString = line.substr(pos + 3);

		try
		{
			this->parseDate(date);
			this->parsePrice(priceString.c_str(), &price);
			std::map<std::string, std::string>::iterator it = map.lower_bound(date);
			if (it != map.begin())
			{
				if (it->first.compare(date) != 0)
					--it;
			}
			exchangeRate = std::strtof(it->second.c_str(), NULL);
			std::cout << date << " => " << price << " = " << price * exchangeRate << std::endl;
		}
		catch (const std::exception &e)
		{
			std::cerr << e.what() << '\n';
		}
	}
}

void BitcoinExchange::parsePrice(const char *priceString, float *price)
{
	char *pEnd;

	*price = std::strtof(priceString, &pEnd);
	if (*pEnd == '\0')
	{
		if (*price < 0.0f)
			throw(BitcoinExchange::NotPositive());
		if (*price > 1000)
			throw(BitcoinExchange::PriceTooHigh());
	}
}

void BitcoinExchange::parseDate(std::string &date)
{
	struct tm tm;

	if (date.length() < 10)
	{
		throw(BitcoinExchange::BadDateFormat(date));
	}
	const char *check = strptime(date.c_str(), "%Y-%m-%d", &tm);
	if (!check || *check != '\0')
		throw(BitcoinExchange::BadDateFormat(date));
}

BitcoinExchange::BitcoinExchange()
{
}

BitcoinExchange::BitcoinExchange(BitcoinExchange const &other)
{
	*this = other;
}

void BitcoinExchange::getExchangeRate(const std::string &path)
{
	this->parseCSVFile(DATA_PATH);
	this->parseInputFile(path);
}

BitcoinExchange &BitcoinExchange::operator=(BitcoinExchange const &other)
{
	this->map = other.map;
	return *this;
}

BitcoinExchange::~BitcoinExchange()
{
}

BitcoinExchange::NotPositive::NotPositive()
{
}

BitcoinExchange::NotPositive::~NotPositive() throw()
{
}

const char *BitcoinExchange::NotPositive::what() const throw()
{
	return ("Error: not a positive number.");
}

BitcoinExchange::BadDateFormat::BadDateFormat(std::string &date)
{
	this->date = date;
	this->message = "Error: bad input => " + this->date;
}

BitcoinExchange::BadDateFormat::~BadDateFormat() throw()
{
}

const char *BitcoinExchange::BadDateFormat::what() const throw()
{
	return (this->message.c_str());
}

BitcoinExchange::PriceTooHigh::PriceTooHigh()
{
}

BitcoinExchange::PriceTooHigh::~PriceTooHigh() throw()
{
}

const char *BitcoinExchange::PriceTooHigh::what() const throw()
{
	return ("Error: too large a number.");
}
