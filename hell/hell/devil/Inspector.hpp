#pragma once

#include <iostream>
#include <string>

template <typename Stream, typename Object> struct IsPrintable
{
	typedef char	Yes[2];
	typedef char	No[1];

	static const bool ISPRINTABLE = (sizeof(*(Stream*)0 << *(Object*)0) != sizeof(No));
};

template<typename a1, typename a2> typename IsPrintable<a1, a2>::No	&operator<<(const a1&, const a2&);

template <bool Cond, typename Stream> struct print_if
{
	template <typename Object>
	static void	print(Stream &ostream, Object const &obj) { ostream << obj << std::endl; }
};
template <typename Stream> struct print_if < 0, Stream >
{
	template <typename Object>
	static void	print(Stream &ostream, Object const &obj)
	{
		std::string	str = typeid(Object).name();
#ifndef __GNUC__
		if (str.find("struct ") == 0)
			str.erase(0, 7);
		if (str.find("class ") == 0)
			str.erase(0, 6);
#endif
		ostream << str.length() << str << std::endl;
	}
};

template <typename Stream> struct Printer
{
	template <typename Object>
	static void	print(Stream &ostream, Object const &obj)
	{
		print_if<IsPrintable<Stream, Object>::ISPRINTABLE, Stream>::print(ostream, obj);
	};
};

template <typename Object> void		inspect(const Object& obj)
{
	Printer<std::ostream>::print(std::cout, obj);
}