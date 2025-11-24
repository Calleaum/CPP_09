/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: calleaum <calleaum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/14 09:10:18 by calleaum          #+#    #+#             */
/*   Updated: 2025/11/24 10:00:13 by calleaum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"
#include "DataParser.hpp"

const char *BitcoinExchange::FileException::what() const throw()
{
	return ("Error: could not open file.");
}

BitcoinExchange::BitcoinExchange()
{
}

BitcoinExchange::BitcoinExchange(const BitcoinExchange &other) : data(other.data)
{
}

BitcoinExchange::~BitcoinExchange()
{
}

BitcoinExchange &BitcoinExchange::operator=(const BitcoinExchange &other)
{
	if (this != &other)
		this->data = other.data;
	return (*this);
}

void BitcoinExchange::setData(const std::string &filename)
{
	// Open data.csv and throw an exception if the file can't be opened
	std::ifstream file(filename.c_str());
	if (!file)
		throw FileException();

	// Read and ignore the first line
	std::string line;
	std::getline(file, line);

	// Read each line of the CSV, parse the date and value and insert into the map
	// Invalid lines are skipped with a warning
	while (std::getline(file, line))
	{
		std::istringstream ss(line);
		std::string dateStr, valueStr;

		if (std::getline(ss, dateStr, ',') && std::getline(ss, valueStr))
		{
			try
			{
				char	*end;
				time_t date = DataParser::strtot(dateStr);
				float value = std::strtof(valueStr.c_str(), &end);
				this->data[date] = value;
			}
			catch (std::exception &e)
			{
				std::cerr << "Warning: " << e.what() << " (" << line << ")" << std::endl;
			}
		}
	}
}

void BitcoinExchange::exchange(const std::string &filename) const
{
	// Open the input file
	std::ifstream file(filename.c_str());
	if (!file)
		throw FileException();

	// Read and ignore the first line
	std::string line;
	std::getline(file, line);

	// Read each line of the input file
	while (std::getline(file, line))
	{
		std::istringstream ss(line);
		std::string dateStr, valueStr;

		// Split the line into date and value
		if (std::getline(ss, dateStr, '|') && std::getline(ss, valueStr)) {
			dateStr.erase(dateStr.find_last_not_of(" \t") + 1);
			dateStr.erase(0, dateStr.find_first_not_of(" \t"));
			valueStr.erase(valueStr.find_last_not_of(" \t") + 1);
			valueStr.erase(0, valueStr.find_first_not_of(" \t"));

			try
			{
				// Convert inputs
				time_t date = DataParser::strtot(dateStr);
				float value = DataParser::strtof(valueStr);

				// Find the closest previous rate
				std::map<time_t, float>::const_iterator it = data.upper_bound(date);
				if (it != data.begin())
					--it;
				else
				{
					std::cerr << "Error: no rate available before " << dateStr << std::endl;
					continue;
				}
				// Apply rate and print result
				float rate = it->second;
				std::cout << dateStr << " => " << value << " = " << value * rate << std::endl;
			}
			catch (std::exception &e)
			{
				std::cerr << e.what() << std::endl;
			}
		}
		else
			std::cerr << "Error: bad input => " << line << std::endl;
	}
}