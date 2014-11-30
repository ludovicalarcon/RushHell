#include "FSA.h"

FSA::FSA()
{
	_init = "";
	_begin = State::create(false);
	_end = State::create(true);
	addState(*_begin);
	addState(*_end);
}

FSA::~FSA() {}

State				&FSA::begin(void) { return (*_begin); }
State 				&FSA::end(void) { return (*_end); }

State				&FSA::operator[](std::string const &name)
{
	return (*_state.find(name)->second);
}

void				FSA::displayState()
{
	for (std::map<std::string, State *>::iterator it = _state.begin(); it != _state.end(); ++it)
		std::cout <<  "State: " << it->first << " Key : " << it->second->getName() << std::endl;
}

void				FSA::addState(State &state)
{
	_state[state.getName()] = &state;
}

void				FSA::setInitialState(std::string const &name)
{
	_init = name;
}

bool				FSA::isInitialSate(std::string const &name) const { return (_init == name); }

std::list<State const*>			FSA::closure(State const &current)
{
	std::list<State const *>			list;
	std::map<std::string, Edge> const	&links = current.getLinks();

	for (std::map<std::string, Edge>::const_iterator it = links.begin(); it != links.end(); ++it)
		list.push_back(&this->operator[](it->first));
	return (list);
}

FSA					*FSA::Subset(std::string const &str) const
{
	FSA				&fsa = *new FSA;
	State *state = &fsa.begin();
	State *newState = (str.size() == 1 ? &fsa.end() : State::create(false));
	for (unsigned int i = 0; i < str.size(); ++i)
	{
		std::map<std::string, Edge> const	*list = &state->getLinks();
		std::map<std::string, Edge>::const_iterator it = list->begin();
		while (it != list->end())
		{
			if (it->second.getKey() == str[i])
			{
				state = &fsa[it->first];
				list = &state->getLinks();
				it = list->begin();
				++i;
				continue;
			}
			++it;
		}

		Edge edge(str[i]);
		state->move(*newState, edge);
		if (i != str.size() - 1)
		{
			fsa.addState(*newState);
			state = newState;
			if (i == str.size() - 2)
				newState = &fsa.end();
			else
				newState = State::create(false);
		}
	}
	return (&fsa);
}
