#include <string>
#include <iostream>

#include "FunctionSignature.hpp"

int	onefunction(std::string const &str)
{
	std::cout << str << std::endl;
	return (str.length());
}

int	main(void)
{
	FunctionSignature<int(const std::string& str)>::type f = &onefunction;
	f("coucou");
	
	FunctionSignature<int(const std::string& str)>::type q = f;
	FunctionSignature<int(const std::string& str)>::type s;
	s = q;
	if (s != f)
		return (1);
	return (0);
}