#include <string>
#include <iostream>
#include <functional>

#include "Function.hpp"

int	function(char c)
{
	std::cout << c << std::endl;
	return ((int)c);
}

int	main(void)
{
	Function<int(char)> f = &function;
	f('f');

	Function<void(void)>	q = []{ std::cout << 'q' << std::endl; };
	q();

	Function<int(char)>		i = std::bind(&function, std::placeholders::_1);
	i('i');

	Function<int(char)> t = std::bind(f, std::placeholders::_1);
	t('t');

	std::function<int(char)>	stdf = &function;

	Function<int(char)> a = stdf;
	a('a');

	Function<int(char)> z = a;
	z('z');

	Function<int(char)>	y = std::function<int(char)>(std::bind(&function, std::placeholders::_1));
	y('y');

	return (0);
}