#include "Base.hpp"
#include "A.hpp"
#include "B.hpp"
#include "C.hpp"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <exception>

Base *generate()
{
	int choice = rand() % 3;

	switch (choice)
	{
		case 0:
			std::cout << "Generating: A" << std::endl;
			return new A();
		case 1:
			std::cout << "Generating: B" << std::endl;
			return new B();
		case 2:
			std::cout << "Generating: C" << std::endl;
			return new C();
	}
	return(NULL);
}
void identify(Base *p)
{
	std::cout << "Identifying (pointer): ";

	if(dynamic_cast<A*>(p))
		std::cout << "A" << std::endl;
	else if(dynamic_cast<B*>(p))
		std::cout << "B" << std::endl;
	else if(dynamic_cast<C*>(p))
		std::cout << "C" << std::endl;
	else
		std::cout << "Unknown type" << std::endl;
}

void identify(Base &p)
{
	std::cout << "Identifying (reference): ";

	try
	{
		(void)dynamic_cast<A&>(p);
		std::cout << "A" << std::endl;
		return;
	}
	catch(const std::exception& e){}

	try
	{
		(void)dynamic_cast<B&>(p);
		std::cout << "B" << std::endl;
		return;
	}
	catch(const std::exception& e){}

	try
	{
		(void)dynamic_cast<C&>(p);
		std::cout << "C" << std::endl;
		return;
	}
	catch(const std::exception& e){}

	std::cout << "Unknown type" << std::endl;
}
int main()
{
    srand(time(NULL));

    for (int i = 0; i < 10; ++i)
    {
        std::cout << "--- Test " << i + 1 << " ---" << std::endl;

        Base *ptr = generate();

        identify(ptr);
        identify(*ptr);

        delete ptr;

        std::cout << std::endl;
    }

    return 0;
}
