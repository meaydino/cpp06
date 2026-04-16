#ifndef DATA_HPP
#define DATA_HPP

#include<iostream>

class Data
{
	public:
		std::string s1;
		int n;
		std::string s2;
		Data();
		Data(std::string s1, int n, std::string s2);
		Data(const Data &other);
		Data &operator=(const Data &other);
		~Data();
};

#endif
