#include <string>
#include <string.h>
#include <iostream>

#include "Machine.hpp"

int						main(int ac, char **av)
{
	eState				currentState = S0;
	std::string			token;
	char				*str;
	char				curr[256];
	int					i = 0;

	if (ac < 2)
	{
		std::cerr << "Usage : [./test_fsa] [string]" << std::endl;
		return (1);
	}
	memset(curr, 7, sizeof(curr));
	curr['m'] = 0;
	curr['e'] = 1;
	curr['c'] = 2;
	curr['h'] = 3;
	curr['a'] = 4;
	curr['n'] = 5;
	curr['t'] = 6;
	for (;;)
	{
		switch (gActionTable[currentState][curr[av[1][i]]])
		{
		case ACTION_ERROR:
			if (av[1][i] == 0)
				return (0);
			std::cerr << "Action error: " << av[1][i] << std::endl;
			token.clear();
			if (currentState == S0)
				++i;
			currentState = S0;
			break;
		case MA:
			currentState = gStateTable[currentState][curr[av[1][i]]];
			token += av[1][i];
			++i;
			break;
		case HR:
			currentState = S0;
			std::cout << token << std::endl;
			token.clear();
			break;
		}
	}
	return (0);
}