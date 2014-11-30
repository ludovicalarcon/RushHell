#include "State.h"

State::State(std::string const &name, bool isFinal)
{
	_id = name;
	_isFinal = isFinal;
}

State::State() {}

State::State(const State &state)
{
	this->operator=(state);
}

State::~State() {}

State				&State::operator=(const State &state)
{
	_isFinal = state._isFinal;
	_id = state._id;
	_link.insert(state._link.begin(), state._link.end());
	return (*this);
}

bool				State::operator==(const State &state) const
{
	return (_id == state._id);
}

bool				State::operator!=(const State &state) const
{
	return (_id != state._id);
}

bool				State::operator>(const State &state) const
{
	return (_id > state._id);
}

bool				State::operator>=(const State &state) const
{
	return (_id >= state._id);
}

bool				State::operator<(const State &state) const
{
	return (_id < state._id);
}

bool				State::operator<=(const State &state) const
{
	return (_id <= state._id);
}

State				*State::create(bool isFinal)
{
	static int		i = 0;
	std::stringstream ss;

	ss << i;
	++i;
	return (new State(std::string("S" + ss.str()), isFinal));
}

void				State::setIsFinal() { _isFinal = true; }

void				State::move(const State &state, const Edge &edge)
{
	_link[state._id] = edge;
}

bool				State::isFinal() const { return (_isFinal); }

const std::string	&State::getName() const { return (_id); }

const char			State::getKey() { return(_link[_id].getKey()); }

bool				State::isOk(char c) const
{
	std::map<std::string, Edge>::const_iterator it = _link.find(_id);
	return (it->second.operator()(c));
}

std::map<std::string, Edge> const &State::getLinks(void) const { return (_link); }