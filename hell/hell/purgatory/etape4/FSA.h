#pragma once

#include <map>
#include <list>
#include <iostream>

#include "State.h"

class				FSA
{
public:
	FSA();
	~FSA();

	State 					&begin(void);
	State					&end(void);
	State					&operator[](std::string const &);

	void					displayState();

	void					addState(State &state);
	void					setInitialState(std::string const &);

	bool					isInitialSate(std::string const &) const;

	std::list<State const*>	closure(State const &);

private:
	State 	*_begin;
	State 	*_end;

	std::map<std::string, State *>	_state;
	std::string						_init;
};