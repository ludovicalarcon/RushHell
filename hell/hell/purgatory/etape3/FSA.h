#pragma once

#include <map>
#include <iostream>

#include "State.h"

class				FSA
{
public:
	FSA();
	~FSA();

	State			&operator[](std::string const &);

	void			displayState();

	void			addState(const State &state);
	void			setInitialState(std::string const &);

	bool			isInitialSate(std::string const &) const;

private:
	std::map<std::string, State>	_state;
	std::string						_init;
};