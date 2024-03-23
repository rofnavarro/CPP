/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AForm.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rferrero <rferrero@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 15:54:56 by rferrero          #+#    #+#             */
/*   Updated: 2024/03/20 20:33:55 by rferrero         ###   ########.fr       */
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
{
	try
	{
		if (gradeToSign > 150 || gradeToExecute > 150 || \
			gradeToSign < 1 || gradeToExecute < 1)
		{
			this->_name = "Invalid";
			this->_gradeToSign = 0;
			this->_gradeToExecute = 0;
			this->_isSigned = false;
			this->_target = "invalid";
			if (this->_gradeToSign > 150 || this->_gradeToExecute > 150)
				throw AForm::GradetooLowToCreateException();
			else
				throw AForm::GradetooHighToCreateException();
		}
		else
		{
			this->_name = name;
			this->_gradeToSign = gradeToSign;
			this->_gradeToExecute = gradeToExecute;
			this->_isSigned = false;
			this->_target = target;
			// std::cout << this->_name << " Aform constructor called." << std::endl;
		}
	}
	catch(const std::exception& e)
	{
		std::cout << e.what() << std::endl;
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
	// std::cout << this->_name << " Aform has expired." << std::endl;
	return ;
}

AForm	&AForm::operator=(const AForm &rhs)
{
	// std::cout << "AForm assignment operator called." << std::endl;
	if (this != &rhs)
	{
		this->_name = rhs._name;
		this->_gradeToSign = rhs._gradeToSign;
		this->_gradeToExecute = rhs._gradeToExecute;
		this->_isSigned = rhs._isSigned;
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
		if (bureaucrat.getGrade() > this->getGradeToSign())
			throw AForm::GradetooLowToSignException();
		else
		{
			this->_isSigned = true;
			std::cout << bureaucrat.getName() << " signed " << this->_name << "." <<std::endl;
		}
	}
	catch(const std::exception& e)
	{
		std::cout << e.what() << std::endl;
		std::cerr << e.what() << std::endl;
	}
	return ;
}

void	AForm::execute(Bureaucrat const &executor) const
{
	try
	{
		if (this->_isSigned == false)
			throw AForm::NotSignedException();
		if (executor.getGrade() > this->_gradeToExecute)
			throw AForm::GradetooLowToSignException();
		else
			std::cout << executor.getName() << " executed " << this->_name << std::endl;
	}
	catch(const std::exception& e)
	{
		std::cout << e.what() << std::endl;
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
	return ("Grade of the form to sign or to execute is too low!");
}

const char	*AForm::GradetooHighToCreateException::what() const throw()
{
	return ("Grade of the form to sign or to execute is too high!");
}

const char	*AForm::GradetooLowToSignException::what() const throw()
{
	return ("Grade of the bureaucrat is too low to sign or to execute!");
}

const char	*AForm::NotSignedException::what() const throw()
{
	return ("Need signature to execute the form!");
}

const char	*AForm::FileNotCreatedException::what() const throw()
{
	return ("Target not created!");
}