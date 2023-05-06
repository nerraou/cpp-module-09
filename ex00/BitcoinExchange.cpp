#include "BitcoinExchange.hpp"

void BitcoinExchange::parseCSVFile(const std::string &path)
{
	std::ifstream data(path);
	std::string line;
	std::size_t pos;

	if (data.is_open())
	{
		while (getline(data, line))
		{
			pos = line.find(",");
			this->map.insert(std::pair<const char *, const char *>(line.substr(0, pos).c_str(), line.substr(pos + 1).c_str()));
		}
	}
}

void BitcoinExchange::parseInputFile(const std::string &path)
{
	std::ifstream data(path);
	std::string line;
	std::size_t pos;
	float price;
	float exchangeRate;

	struct tm tm;

	while (getline(data, line))
	{
		pos = line.find(" | ");
		const char *date = line.substr(0, pos).c_str();
		const char *priceString = line.substr(pos + 3).c_str();

		const char *check = strptime(date, "%Y-%m-%d", &tm);
		if (check && *check == '\0' && this->parsePrice(priceString, &price))
		{
			if (map.count(date) == 0)
			{
			}
			else
			{
				exchangeRate = std::strtof(map.at(date), NULL);
				std::cout << "date : " << date << " price: " << price * exchangeRate << std::endl;
			}
		}
		else
			std::cerr << "Error invalid date or price in line" << line << std::endl;
	}
}

bool BitcoinExchange::parsePrice(const char *priceString, float *price)
{
	char *pEnd;

	*price = std::strtod(priceString, &pEnd);
	if (*pEnd == '\0' && (*price >= 0 && *price <= 1000))
	{
		return (true);
	}
	*price = std::strtof(priceString, &pEnd);
	if (*pEnd == '\0' && (*price >= 0 && *price <= 1000))
	{
		return (true);
	}
	// throw error price not
	return (false);
}

BitcoinExchange::BitcoinExchange()
{
}

BitcoinExchange::BitcoinExchange(BitcoinExchange const &other)
{
	*this = other;
}

void BitcoinExchange::printFile(const std::string &path)
{
	// this->parseCSVFile(path);
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
