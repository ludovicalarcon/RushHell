#include "Inspector.hpp"

struct test{};

struct lol{};
std::ostream& operator<<(std::ostream& out, const lol&)
{
	out << "Lol instance given";
	return out;
}

int main(int, char**)
{
	test t;
	lol l;
	std::string str = "salut";
	inspect(t);
	inspect(str);
	inspect(l);
	return (0);
}

//#include "bind\bind.hpp"
//#include "../charon/etape2/Function.hpp"
//
//#include <iostream>
//#include <string>
//
//struct tot
//{
//	tot(void) {}
//int f(char c, std::string const &titi)
//{
//	std::cout << c << " " << titi << std::endl;
//	return (1);
//}
//private:
//	tot(tot const &copy);
//	tot &operator=(tot const &copy);
//};
//
//#include <functional>
//
//int main()
//{
//	tot toto;
//
//	Function<int(char)>	func = bind(&tot::f, &toto, Placeholder::_1, "toto");
//	std::cout << func('&') << std::endl;
//
//	Function<int(std::string const &)>	fnc = bind(&tot::f, &toto, 'a', Placeholder::_1);
//	std::cout << fnc("titi") << std::endl;
//
//	Function<int(char, std::string const &)>	fc = bind(&tot::f, &toto, Placeholder::_1, Placeholder::_2);
//	std::cout << fc('z', "tutu") << std::endl;
//	return (0);
//}
