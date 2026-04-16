#include "ScalarConverter.hpp"
#include<iostream>
#include <limits>
#include <iomanip>
#include<cstdlib>

enum Type
{
	CHAR,
	INT,
	FLOAT,
	DOUBLE,
	PSEUDO,
	UNKNOWN
};

ScalarConverter::ScalarConverter(){}
ScalarConverter::ScalarConverter(const ScalarConverter &other)
{
	(void)other;
}
ScalarConverter &ScalarConverter::operator=(const ScalarConverter &other)
{
	(void)other;
	return(*this);
}
ScalarConverter::~ScalarConverter(){}

static bool isPseudo(const std::string &s)
{
	return(s == "nan" || s == "nanf" || s == "+inf" || s == "-inf" || s == "+inff" || s == "-infff");
}

static bool isChar(const std::string &s)
{
	return(s.length() == 3 && s[0] == '\'' && s[2] == '\'');
}
static bool isInt(const std::string &s)
{
	size_t i = 0;
	if(s[i] == '+' || s[i] == '-')
		i++;
	if(i == s.length())
		return(0);
	for(; i < s.length();i++)
	{
		if(!isdigit(s[i]))
			return(0);
	}
	return(1);
}
static bool isFloat(const std::string &s)
{
	if(s.find('f') == std::string::npos || s[s.length() -1] != 'f')
		return(0);
	if(s.find('.') == std::string::npos)
		return(0);
	bool dot = 0;
	size_t i = 0;
	if(s[i] == '+' || s[i] == '-')
		i++;
	for(;i < s.length() - 1;i++)
	{
		if(s[i] == '.')
		{
			if(dot)
				return(0);
			dot = 1;
		}
		else if(!isdigit(s[i]))
			return(0);
	}
	return(dot);

}
static bool isDouble(const std::string &s)
{
    if (s.find('.') == std::string::npos)
        return (false);

    bool dot = false;
    size_t i = 0;
    if (s[i] == '+' || s[i] == '-')
        i++;
    for (; i < s.length(); i++)
    {
        if (s[i] == '.')
        {
            if (dot) return (false);
            dot = true;
        }
        else if (!isdigit(s[i]))
            return (false);
    }
    return (dot);
}
static Type detectType(const std::string &s)
{
	if(isPseudo(s))
		return(PSEUDO);
	if(isChar(s))
		return(CHAR);
	if(isFloat(s))
		return(FLOAT);
	if(isDouble(s))
		return(DOUBLE);
	if(isInt(s))
		return(INT);
	return(UNKNOWN);
}
static void printValues(double n)
{
	std::cout << "char: ";
	if(n != n || n < 0 || n > 255 || n == 1.0/0.0 || n == -1.0/0.0)
		std::cout << "impossible" << std::endl;
	else if(!isprint(static_cast<char>(n)))
		std::cout << "Non displayable" << std::endl;
	else
		std::cout << "'" << static_cast<char>(n) << "'" << std::endl;

	std::cout << "int: ";
	if(n != n || n < std::numeric_limits<int>::min() || n > std::numeric_limits<int>::max())
		std::cout << "impossible" << std::endl;
	else
		std::cout << static_cast<int>(n) << std::endl;

	float f = static_cast<float>(n);
	std::cout << std::fixed << std::setprecision(1);
	std::cout << "float: " << f << "f" << std::endl;
	std::cout << "double: " << n << std::endl;
}

static void printPseudo(const std::string &literal)
{
	std::cout << "char: impossible" << std::endl;
	std::cout << "int: impossible" << std::endl;
	if(literal == "nan" || literal == "nanf")
	{
		std::cout << "float: nanf" << std::endl;
		std::cout << "double: nan" << std::endl;
	}
	else if(literal == "+inf" || literal == "+inff")
	{
		std::cout << "float: +inff" << std::endl;
		std::cout << "double: +inf" << std::endl;
	}
	else if(literal == "-inf" || literal == "-inff")
	{
		std::cout << "float: -inff" << std::endl;
		std::cout << "double: -inf" << std::endl;
	}
}
void ScalarConverter::convert(const std::string &literal)
{
	Type type = detectType(literal);
	double value = 0.0;
	switch (type)
	{
		case CHAR:
			value = static_cast<double>(literal[1]);
			printValues(value);
			break;
		case INT:
			value = std::strtod(literal.c_str(), NULL);
			printValues(value);
			break;
		case FLOAT:
			value = std::strtod(literal.c_str(), NULL);
			printValues(value);
			break;
		case DOUBLE:
			value = std::strtod(literal.c_str(), NULL);
			printValues(value);
			break;
		case PSEUDO:
			printPseudo(literal);
			break;
		case UNKNOWN:
            if (literal.length() == 1 && !isdigit(literal[0]))
            {
                value = static_cast<double>(literal[0]);
                printValues(value);
            }
            else
            {
                std::cout << "char: impossible\nint: impossible\nfloat: impossible\ndouble: impossible" << std::endl;
            }
            break;
	}
}
