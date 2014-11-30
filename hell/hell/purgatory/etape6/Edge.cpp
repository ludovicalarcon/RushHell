#include "Edge.h"

Edge::Edge(const char c) : _c(c) {}

Edge::Edge() {}

Edge::Edge(const Edge &edge)
{
	this->operator=(edge);
}

Edge::~Edge() {}

Edge			&Edge::operator=(const Edge &edge)
{
	_c = edge._c;
	return (*this);
}

bool			Edge::operator==(const Edge &edge) const
{
	return (_c == edge._c);
}

bool			Edge::operator!=(const Edge &edge) const
{
	return (_c != edge._c);
}

bool			Edge::operator>(const Edge &edge) const
{
	return (_c > edge._c);
}

bool			Edge::operator>=(const Edge &edge) const
{
	return (_c >= edge._c);
}

bool			Edge::operator<(const Edge &edge) const
{
	return (_c < edge._c);
}

bool			Edge::operator<=(const Edge &edge) const
{
	return (_c <= edge._c);
}

bool			Edge::operator()(const char c) const
{
	return (_c == c);
}

char			Edge::getKey() const { return (_c); }