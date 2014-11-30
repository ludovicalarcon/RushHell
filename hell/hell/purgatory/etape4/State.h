#pragma once

#include <string>
#include <map>
#include <sstream>

#include "Edge.h"

class				State
{
public:
	State();
	State(const State &);
	~State();

	State			&operator=(const State &);
	bool			operator==(const State &) const;
	bool			operator!=(const State &) const;
	bool			operator>(const State &) const;
	bool			operator>=(const State &) const;
	bool			operator<(const State &) const;
	bool			operator<=(const State &) const;

	static State	*create(bool isFinal = false);
	void			setIsFinal();
	void			addLink(const State &, const Edge &);

	bool				isFinal() const;
	const std::string	&getName() const;
	const char			getKey();
	bool				isOk(char c) const;

	std::map<std::string, Edge> const &getLinks(void) const;

private:
	State(std::string const &, bool);

	bool			_isFinal;
	std::string		_id;

	std::map<std::string, Edge>	_link;
};