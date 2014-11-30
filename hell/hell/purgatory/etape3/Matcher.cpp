#include "Matcher.h"

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
	int			current = 0;

	rec = 0;
	unsigned int i = 0;
	while (i < str.size())
	{
		Edge edge(str[i]);
		std::stringstream ss;

		ss << current;
		if (_fsa[std::string("S" + ss.str())].isOk(edge.getKey()))
		{
			token += edge.getKey();
			if (_fsa[std::string("S" + ss.str())].isFinal())
			{
				std::cout << "Token : " << token << std::endl;
				current = 0;
				token.clear();
				++rec;
			}
			else
				++current;
			++i;
		}
		else
		{
			std::cerr << "Action error: " << edge.getKey() << std::endl;
			if (current == 0)
				++i;
			current = 0;
			token.clear();
		}
	}
	if (rec == 0)
		return (false);
	return (true);
}

void			Matcher::init(std::string const &str)
{
	State state = State::create(false);
	_fsa.addState(state);
	for (unsigned int i = 0; i < str.size(); ++i)
	{
		if (i == str.size() - 1)
			state.setIsFinal();
		Edge edge(str[i]);
		state.addLink(state, edge);
		_fsa.addState(state);
		if (i != str.size() - 1)
			state = State::create(false);
	}
}