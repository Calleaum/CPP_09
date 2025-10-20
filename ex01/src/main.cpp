/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: calleaum <calleaum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 10:37:19 by calleaum          #+#    #+#             */
/*   Updated: 2025/10/20 10:39:23 by calleaum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "RPN.hpp"

int	main(int argc, char *argv[])
{
	RPN	rpn;

	if (argc < 2)
	{
		std::cerr << "Usage: " << argv[0] << " <expression>" << std::endl;
		return (EXIT_FAILURE);
	}
	if (argc > 2)
	{
		std::cerr << argv[0] << ": too many arguments" << std::endl;
		return (EXIT_FAILURE);
	}
	try
	{
		std::cout << rpn.compute(argv[1]) << std::endl;
	}
	catch (std::exception &e)
	{
		std::cerr << argv[0] << ": " << e.what() << std::endl;
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}