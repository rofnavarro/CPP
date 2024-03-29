/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AForm.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rferrero <rferrero@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 15:54:56 by rferrero          #+#    #+#             */
/*   Updated: 2024/03/24 20:45:35 by rferrero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Bureaucrat.hpp"
#include "AForm.hpp"

AForm::AForm(void)
:_name("Default"), _gradeToSign(150), _gradeToExecute(150), _isSigned(false), _target("root")
{
	// std::cout << this->_name << " Aform constructor called." << std::endl;
	return ;
}

AForm::AForm(std::string name, int gradeToSign, int gradeToExecute, std::string target)
:_name(name), _gradeToSign(gradeToSign), _gradeToExecute(gradeToExecute), _isSigned(false), _target(target)
{
	try
	{
		if (this->_gradeToSign > 150 || this->_gradeToExecute > 150)
			throw AForm::GradetooLowToCreateException();
		else if (gradeToSign < 1 || gradeToExecute < 1)
			throw AForm::GradetooHighToCreateException();
		// else
		// 	std::cout << this->_name << " Aform constructor called." << std::endl;
	}
	catch(const std::exception& e)
	{
		// std::cout << e.what() << std::endl;
		std::cerr << e.what() << std::endl;
	}
	return ;
}

AForm::AForm(const AForm &aform)
:_name(aform._name + " Copy"), _gradeToSign(aform._gradeToSign), _gradeToExecute(aform._gradeToExecute), _target(aform._target)
{
	// std::cout << "AForm copy constructor called." << std::endl;
	*this = aform;
	return ;
}

AForm::~AForm(void)
{
	// std::cout << this->_name << " aform has expired." << std::endl;
	return ;
}

AForm	&AForm::operator=(const AForm &rhs)
{
	// std::cout << "AForm assignment operator called." << std::endl;
	if (this != &rhs)
	{
		const_cast	<std::string &>(this->_name) = rhs.getName() + " Assigned";
		const_cast	<int &>(this->_gradeToSign) = rhs.getGradeToSign();
		const_cast	<int &>(this->_gradeToExecute) = rhs.getGradeToExecute();
		this->_isSigned = rhs.getIsSigned();
		this->_target = rhs._target;
	}
	return (*this);
}

const std::string	&AForm::getName(void) const
{
	return (this->_name);
}

const int	&AForm::getGradeToSign(void) const
{
	return (this->_gradeToSign);
}

const int	&AForm::getGradeToExecute(void) const
{
	return (this->_gradeToExecute);
}

const bool	&AForm::getIsSigned(void) const
{
	return (this->_isSigned);
}

void	AForm::beSigned(Bureaucrat &bureaucrat)
{
	try
	{
		if (this->getIsSigned())
			throw AForm::AlreadySignedException();
		if (bureaucrat.getGrade() > this->_gradeToSign)
			throw AForm::GradetooLowToSignException();
		else
		{
			this->_isSigned = true;
			// std::cout << bureaucrat.getName() << " signed " << this->_name << "." <<std::endl;
		}
	}
	catch(const std::exception& e)
	{
		// std::cout << e.what() << std::endl;
		std::cerr << e.what() << std::endl;
	}
	return ;
}

void	AForm::execute(Bureaucrat const &executor) const
{
	try
	{
		if (this->getIsSigned() == false)
			throw AForm::NotSignedException();
		else if (executor.getGrade() > this->getGradeToExecute())
			throw AForm::GradetooLowToSignException();
		// else
		// 	std::cout << executor.getName() << " executed " << this->getName() << std::endl;
	}
	catch(const std::exception& e)
	{
		// std::cout << e.what() << std::endl;
		std::cerr << e.what() << std::endl;
	}
	return ;
}

std::ostream	&operator<<(std::ostream &lhs, const AForm &rhs)
{
	if (rhs.getIsSigned() == true)
		lhs << "AForm " << rhs.getName() << " IS signed." << std::endl;
	else
		lhs << "AForm " << rhs.getName() << " IS NOT signed." << std::endl;
	lhs << "Grade to sign: " << rhs.getGradeToSign() << "." << std::endl;
	lhs << "Grade to execute: " << rhs.getGradeToExecute() << "." << std::endl;
	return (lhs);
}

const char	*AForm::GradetooLowToCreateException::what() const throw()
{
	return ("Grade to sign or to execute the aform is too low!");
}

const char	*AForm::GradetooHighToCreateException::what() const throw()
{
	return ("Grade to sign or to execute the aform is too high!");
}

const char	*AForm::GradetooLowToSignException::what() const throw()
{
	return ("Grade of the bureaucrat is too low to sign the aform!");
}

const char	*AForm::AlreadySignedException::what() const throw()
{
	return ("AForm is already signed!");
}

const char	*AForm::NotSignedException::what() const throw()
{
	return ("Aform is not signed!");
}

const char	*AForm::FileNotCreatedException::what() const throw()
{
	return ("File not created by aform!");
}
