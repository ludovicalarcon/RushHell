#pragma once

#include "FSA.h"

class					Matcher
{
public:
	Matcher(FSA &fsa);
	~Matcher();

	bool				find(std::string const &);
	bool				find(std::string const &, int &);
	void				init(std::string const &);
private:
	FSA					_fsa;
};