/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cat.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rferrero <rferrero@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/15 12:53:49 by rferrero          #+#    #+#             */
/*   Updated: 2023/12/16 11:07:23 by rferrero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cat.hpp"

Cat::Cat(void)
{
	this->_type = "Cat";
	std::cout << "A " << this->_type << " has been born" << std::endl;
	return ;
}

Cat::Cat(const Cat &cat)
:Animal()
{
	*this = cat;
	std::cout << this->_type << " copy constructor called" << std::endl;
	return ;
}

Cat::~Cat(void)
{
	std::cout << this->_type << " has been killed" << std::endl;
	return ;
}

Cat	&Cat::operator=(const Cat &rhs)
{
	if (this != &rhs)
		this->_type = rhs._type;
	std::cout << this->_type << " assignment operator called" << std::endl;
	return (*this);
}

void	Cat::makeSound(void) const
{
	std::cout << this->_type << ": *miaw*   *miaw*   *miaw" << std::endl;
	return ;
}
