#include "ExpressionParser.h"

std::list<State *>	ExpressionParser::parse(FSA &fsa, std::string const &s, State *current, bool endded)
{
	std::string	str = s;
	std::string	tmp;

	unsigned long	end;
	bool			firstTurn = true;;

	std::list<State *>	list;

	while (str.size())
	{
		if (!firstTurn)
			if (str[0] == '|')
				str.erase(0, 1);
			else
				throw (std::exception("Parsing error"));
		else
			firstTurn = false;
		end = findParenth(str);
		if (str[0] != '(')
			throw (std::exception("Parsing error"));
		tmp = str.substr(1, end - 2);
		str.erase(0, end);
		list.merge(parseIn(fsa, tmp, current, endded));
	}

	return (list);
}

std::list<State *>	ExpressionParser::parseIn(FSA &fsa, std::string const &s, State *current, bool endded)
{
	std::string	str = s;
	std::string	tmp;

	State *newState;
	std::list<State *> list;
	State *save = current;

	unsigned long	end;

	while (str.size())
	{
		switch (str[0])
		{
		case '|':
			if (current != save)
				list.push_back(current);
			else
				throw (std::exception("Parsing error"));
			current = save;
			str.erase(0, 1);
			end = findPipe(str);
			tmp = str.substr(0, (str[end] ? end - 1 : end));
			str.erase(0, (str[end] ? end - 1 : end));
			list.merge(parseIn(fsa, tmp, current, str[0] != 0 || endded));
			break;
		case '(':
			end = findParenth(str);
			tmp = str.substr(0, end);
			str.erase(0, end);
			 list.merge(parse(fsa, tmp, current, str[0] != 0));
			break;
		default:
			std::map<std::string, Edge> const	*links = &current->getLinks();
			std::map<std::string, Edge>::const_iterator it = links->begin();
			while (it != links->end())
			{
				if (it->second.getKey() == str[0])
				{
					current = &fsa[it->first];
					links = &current->getLinks();
					it = links->begin();
					str.erase(0, 1);
					continue;
				}
				++it;
			}
			newState = ((str.size() && str[1]) || endded ? State::create(false) : &fsa.end());
			if (list.empty())
				current->move(*newState, Edge(str[0]));
			else
			{
				std::list<State *>::iterator it = list.begin();
				while (it != list.end())
				{
					(*it)->move(*newState, Edge(str[0]));
					it = list.erase(it);
				}
			}
			if ((str.size() && str[1]) || endded)
				fsa.addState(*newState);
			current = newState;
			str.erase(0, 1);
		}
	}
	if (list.empty())
		list.push_back(current);
	return (list);
}

unsigned long	ExpressionParser::findParenth(std::string const &str)
{
	unsigned long	it = 0;
	unsigned long	nb = 0;

	while (str[it] && (nb > 0 || it == 0))
	{
		if (str[it] == '(')
			++nb;
		else if (str[it] == ')')
			--nb;
		++it;
	}
	if (nb != 0)
		throw (std::exception("Parsing error"));
	return (it);
}

unsigned long	ExpressionParser::findPipe(std::string const &str)
{
	unsigned long	it = 0;
	unsigned long	nb = 0;

	while (str[it] && (str[it] != '|' || nb != 0))
	{
		if (str[it] == '(')
			++nb;
		else if (str[it] == ')')
			--nb;
		++it;
	}
	if (nb != 0)
		throw (std::exception("Parsing error"));
	return (it);
}

FSA	&ExpressionParser::setFSA(FSA &fsa, std::string const &str)
{
	State *current = &fsa.begin();

	switch (str[0])
	{
	case '(':
		parse(fsa, str, current);
		break;
	default:
		parseIn(fsa, str, current);
	}
	return (fsa);
}