#include "Data.hpp"
Data::Data():s1("EMPTY"), n(0), s2("EMPTY"){}
Data::Data(std::string s1, int n, std::string s2)
{
	this->s1 = s1;
	this->n = n;
	this->s2 = s2;
}
Data::~Data() {}
Data::Data(const Data &other):s1(other.s1), n(other.n), s2(other.s2){}
Data &Data::operator=(const Data &other)
{
	if(this != &other)
	{
		this->s1 = other.s1;
		this->s2 = other.s2;
		this->n = other.n;
	}
	return(*this);
}
