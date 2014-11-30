#include "Matcher.h"
#include "ExpressionParser.h"

Matcher::Matcher(FSA &fsa) : _fsa(fsa) {}

Matcher::~Matcher() {}

bool			Matcher::find(std::string const &str)
{
	int			i = 0;
	return (find(str, i));
}

bool			Matcher::find(std::string const &str, int &rec)
{
	std::string token;
	State const	*current = &_fsa["S0"];

	rec = 0;
	unsigned int i = 0;
	while (i < str.size())
	{
		Edge edge(str[i]);
		std::list<State const *> const				&dests = _fsa.closure(*current);
		std::list<State const *>::const_iterator	itd = dests.begin();
		std::map<std::string, Edge>					edges = current->getLinks();
		std::map<std::string, Edge>::const_iterator	ite = edges.begin();

		while (ite != edges.end())
		{
			if (ite->second.getKey() == edge.getKey())
			{
				token += edge.getKey();
				current = *itd;
				++i;
				break;
			}
			++itd;
			++ite;
		}
		if (current->isFinal())
		{
			std::cout << "Token : " << token << std::endl;
			current = &_fsa["S0"];
			token.clear();
			++rec;
		}
		if (itd == dests.end())
		{
			std::cerr << "Action error: " << edge.getKey() << std::endl;
			if (*current == _fsa["S0"])
				++i;
			current = &_fsa["S0"];
			token.clear();

		}
	}
	if (rec == 0)
		return (false);
	return (true);
}

void			Matcher::init(std::string const &str)
{
	ExpressionParser::setFSA(_fsa, str);
	//State *state = &_fsa.begin();
	//State *newState = (str.size() == 1 ? &_fsa.end() : State::create(false));
	//for (unsigned int i = 0; i < str.size(); ++i)
	//{
	//	std::map<std::string, Edge> const	*list = &state->getLinks();
	//	std::map<std::string, Edge>::const_iterator it = list->begin(); 
	//	while (it != list->end())
	//	{
	//		if (it->second.getKey() == str[i])
	//		{
	//			state = &_fsa[it->first];
	//			list = &state->getLinks();
	//			it = list->begin();
	//			++i;
	//			continue;
	//		}
	//		++it;
	//	}

	//	Edge edge(str[i]);
	//	state->move(*newState, edge);
	//	if (i != str.size() - 1)
	//	{
	//		_fsa.addState(*newState);
	//		state = newState;
	//		if (i == str.size() - 2)
	//			newState = &_fsa.end();
	//		else
	//			newState = State::create(false);
	//	}
	//}
}