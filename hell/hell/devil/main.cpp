//#include "Inspector.hpp"
//
//struct test{};
//
//struct lol{};
//std::ostream& operator<<(std::ostream& out, const lol&)
//{
//	out << "Lol instance given";
//	return out;
//}
//
//int main(int, char**)
//{
//	test t;
//	lol l;
//	std::string str = "salut";
//	inspect(t);
//	inspect(str);
//	inspect(l);
//	return (0);
//}

#include "bind\bind.hpp"
#include "../charon/etape2/Function.hpp"

#include <iostream>

struct tot
{
	tot(void) {}
int f(char c)
{
	std::cout << c << std::endl;
	return (1);
}
private:
	tot(tot const &copy);
	tot &operator=(tot const &copy);
};

#include <functional>

int main()
{
	tot toto;
	auto to = std::bind(&tot::f, &toto, std::placeholders::_1);
	to('&');
	Function<int(char)>	func = bind(&tot::f, &toto, Placeholder::_1);
	std::cout << func('&') << std::endl;

	Function<int(void)>	fnc = bind(&tot::f, &toto, 'a');
	std::cout << fnc() << std::endl;
	return (0);
}
