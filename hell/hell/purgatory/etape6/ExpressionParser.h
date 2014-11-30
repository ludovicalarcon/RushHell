#pragma once

#include <string>
#include "FSA.h"

class ExpressionParser
{
	static std::list<State *>	parse(FSA &, std::string const &, State *, bool = false);
	static std::list<State *>	parseIn(FSA &, std::string const &, State *, bool = false);

	static unsigned long	findParenth(std::string const &);
	static unsigned long	findPipe(std::string const &);
	
public:
	static FSA	&setFSA(FSA &fsa, std::string const &);
};