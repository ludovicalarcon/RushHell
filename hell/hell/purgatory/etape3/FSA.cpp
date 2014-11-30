#include "FSA.h"

FSA::FSA()
{
	_init = "";
}

FSA::~FSA() {}

State				&FSA::operator[](std::string const &name)
{
	return (_state[name]);
}

void				FSA::displayState()
{
	for (std::map<std::string, State>::iterator it = _state.begin(); it != _state.end(); ++it)
		std::cout <<  "State: " << it->first << " Key : " << it->second.getKey() << std::endl;
}

void				FSA::addState(const State &state)
{
	_state[state.getName()] = state;
}

void				FSA::setInitialState(std::string const &name)
{
	_init = name;
}

bool				FSA::isInitialSate(std::string const &name) const { return (_init == name); }