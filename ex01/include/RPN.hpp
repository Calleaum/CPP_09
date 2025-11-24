/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: calleaum <calleaum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 10:37:16 by calleaum          #+#    #+#             */
/*   Updated: 2025/11/24 10:00:37 by calleaum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <stack>
#include <cmath>
#include <cerrno>
#include <string>
#include <climits>
#include <cstring>
#include <cstdlib>
#include <stdexcept>
#include <iostream>

class RPN
{
	protected:
		std::stack<double>	stack;

		size_t	parseValue(const std::string &str, size_t start);
		size_t	parseOp(const std::string &str, size_t start);
		void	doOp(char op);

	public:
		RPN();
		RPN(const RPN &other);
		~RPN();
		RPN		&operator=(const RPN &other);
		double	compute(const std::string &str);
};