#include <string.h>
#include <iostream>
#include <string>

#include "Machine.hpp"

int	main(int argc, unsigned char *argv[])
{
	unsigned char	*str = (unsigned char*)"mechant";
	char	trans[256];

	if (argc > 1)
		str = argv[1];
	memset(trans, 7, sizeof(trans));
	trans['m'] = 0;
	trans['e'] = 1;
	trans['c'] = 2;
	trans['h'] = 3;
	trans['a'] = 4;
	trans['n'] = 5;
	trans['t'] = 6;

	eState current = S0;
	std::string token;

	int i = 0;
	while (1)
	{
		switch (gActionTable[current][trans[str[i]]])
		{
		case ACTION_ERROR:
			std::cout << str[i] << ": ACTION_ERROR" << std::endl;
			return (!str[i]);
			break;
		case MA:
			current = gStateTable[current][trans[str[i]]];
			token += str[i];
			++i;
			break;
		case HR:
			std::cout << token << std::endl;
			token.clear();
			current = S0;
		}
	}
	return (0);
}