/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: calleaum <calleaum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/14 09:10:15 by calleaum          #+#    #+#             */
/*   Updated: 2025/11/24 10:00:07 by calleaum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <iostream>
#include <string>
#include <map>
#include <fstream>
#include <cstdlib>

class	BitcoinExchange
{
	class	FileException : public std::exception
	{
		public:
			const char	*what() const throw();
	};

	protected:
		std::map<time_t, float>	data;
	public:
		BitcoinExchange();
		BitcoinExchange(const BitcoinExchange &other);
		~BitcoinExchange();
		BitcoinExchange	&operator=(const BitcoinExchange &other);

		void	setData(const std::string	&filename);
		void	exchange(const std::string	&filename) const;
};