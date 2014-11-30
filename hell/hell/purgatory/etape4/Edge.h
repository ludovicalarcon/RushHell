#pragma once

class					Edge
{
public:
	Edge(const char);
	Edge();
	Edge(const Edge &);

	~Edge();

	Edge				&operator=(const Edge &);
	bool				operator==(const Edge &) const;
	bool				operator!=(const Edge &) const;
	bool				operator>(const Edge &) const;
	bool				operator>=(const Edge &) const;
	bool				operator<(const Edge &) const;
	bool				operator<=(const Edge &) const;
	bool				operator()(const char) const;

	char				getKey() const;

private:
	char				_c;
};
