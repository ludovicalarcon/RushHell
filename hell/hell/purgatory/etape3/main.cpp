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
		std::cerr << "Usage : [./ test_dynamic_fsa] [alpha] [str]" << std::endl;
		return (1);
	}
	matcher.init(av[1]);
	matcher.find(av[2]);
	return (0);
}