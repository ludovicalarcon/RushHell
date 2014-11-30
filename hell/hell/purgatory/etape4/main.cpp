#include <string>
#include <string.h>
#include <iostream>

#include "Matcher.h"

int main(int ac, char **av)
{
	FSA fsa;
	Matcher matcher(fsa);

	if (ac < 3)
	{
		std::cerr << "Usage : [./ test_dynamic_fsa] [str] [alpha [alpha [...]]]" << std::endl;
		return (1);
	}
	for (int i = 2; i < ac; ++i)
		matcher.init(av[i]);
	matcher.find(av[1]);
	return (0);
}