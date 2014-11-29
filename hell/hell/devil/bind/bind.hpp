#pragma once

struct Storage0
{
	Storage0() {}
};

template <typename T1>
struct Storage1 : public Storage0
{
	typedef T1	T1;
	Storage1(T1& t1) : Storage0(), _t1(t1) {}
	T1	_t1;
};

template <typename T1, typename T2>
struct Storage2 : public Storage1<T1>
{
	typedef T1	T1;
	typedef T2	T2;
	Storage2(T1& t1, T2& t2) : Storage1<T1>(t1), _t2(t2) {}
	T2	_t2;
};

template <typename T1, typename T2, typename T3>
struct Storage3 : public Storage2<T1, T2>
{
	Storage3(T1& t1, T2& t2, T3& t3) : Storage2<T1, T2>(t1, t2), _t3(t3) {}
	T3	_t3;
};

template <typename T1, typename T2, typename T3, typename T4>
struct Storage4 : public Storage3<T1, T2, T3>
{
	Storage4(T1& t1, T2& t2, T3& t3, T4& t4) : Storage3<T1, T2, T3>(t1, t2, t3), _t4(t4) {}
	T4	_t4;
};

template <typename T1, typename T2, typename T3, typename T4, typename T5>
struct Storage5 : public Storage4<T1, T2, T3, T4>
{
	Storage5(T1& t1, T2& t2, T3& t3, T4& t4, T5& t5) : Storage4<T1, T2, T3, T4>(t1, t2, t3, t4), _t5(t5) {}
	T5	_t5;
};

template <typename T1, typename T2, typename T3, typename T4, typename T5, typename T6>
struct Storage6 : public Storage5<T1, T2, T3, T4, T5>
{
	Storage6(T1& t1, T2& t2, T3& t3, T4& t4, T5& t5, T6& t6) : Storage5<T1, T2, T3, T4, T5>(t1, t2, t3, t4, t5), _t6(t6) {}
	T6	_t6;
};

template <typename _Type> class Value
{
	_Type	&_value;

public:
	Value(_Type &value) : _value(value) {}

	_Type		&get(void) { return (_value); }
	_Type const	&get(void) const { return (_value); }

	typedef _Type	type;
};

template <typename _Type> class GetType
{
public:
	typedef Value<_Type>	Type;
};

template <typename _Type> class TypeTraits {};

namespace Placeholder
{
	template <int value> struct _Ph {};
	_Ph<1>	_1;
	_Ph<2>	_2;
	_Ph<3>	_3;
}

template <typename ReturnType, typename Callable, typename List> class Caller
{
	Callable	_callable;
	List		_list;

public:
	Caller(Callable callable, List list) : _callable(callable), _list(list) {}

	ReturnType	operator()(void) { return (_list(TypeTraits<ReturnType>(), _callable, _list)); }
	template <typename T1>
	ReturnType	operator()(T1 &&t1)
	{
		typedef typename GetType<T1>::Type	P1;
		typedef TypeList1<P1>				ListType;
		ListType							args(t1);
		return (_list(TypeTraits<ReturnType>(), _callable, _list, args));
	}
};

template <typename Callable, typename List> class Caller<void, Callable, List>
{
	Callable	_callable;
	List		_list;

public:
	Caller(Callable callable, List list) : _callable(callable), _list(list) {}

	void	operator()(void) { _list(TypeTraits<void>(), _callable, _list); }
};


struct TypeList0 : private Storage0
{
	typedef Storage0	BaseClass;

	TypeList0() : BaseClass(){}

	template <typename T>
	T	&operator[](Value<T> &value) { return (value.get()); }

	template <typename ReturnType, typename Caller, typename List>
	ReturnType operator()(TypeTraits<ReturnType>, Caller& caller, List& list)
	{
		return (caller());
	}
};

template <typename P1> struct TypeList1;
template <typename P1> struct TypeList1<Value<P1>> : private Storage1<Value<P1>>
{
	typedef Storage1<Value<P1>> BaseClass;

	TypeList1(Value<P1> p1) : BaseClass(p1){}

	template <typename T> T	&operator[](T &value) { return (value); }
	P1	&operator[](Placeholder::_Ph<1>) { return (BaseClass::_t1.get()); }
	template <typename T>
	T	&operator[](Value<T> &value) { return (value.get()); }

	template <typename ReturnType, typename Caller, typename List>
	ReturnType operator()(TypeTraits<ReturnType>, Caller& caller, List& list)
	{
		return (caller(list[BaseClass::_t1]));
	}
	template <typename ReturnType, typename Caller, typename List, typename Args>
	ReturnType operator()(TypeTraits<ReturnType>, Caller& caller, List& list, Args &args)
	{
		return (caller(args[list[BaseClass::_t1]]));
	}
};

template <typename P1, typename P2>
struct TypeList2 : private Storage2<P1, P2>
{
	typedef Storage2<P1, P2> BaseClass;

	TypeList2(P1 p1, P2 p2) : BaseClass(p1, p2){}

	template <typename T>
	T	&operator[](Value<T> &value) { return (value.get()); }

	template <typename ReturnType, typename Caller, typename List>
	ReturnType operator()(TypeTraits<ReturnType>, Caller& caller, List& list)
	{
		return (caller(list[BaseClass::_t1], list[BaseClass::_t2]));
	}
};

template <typename P1, typename P2, typename P3>
struct TypeList3 : private Storage3<P1, P2, P3>
{
	typedef Storage3<P1, P2, P3> BaseClass;

	TypeList3(P1 p1, P2 p2, P3 p3) : BaseClass(p1, p2, p3){}

	template <typename T>
	T	&operator[](Value<T> &value) { return (value.get()); }

	template <typename ReturnType, typename Caller, typename List>
	ReturnType operator()(TypeTraits<ReturnType>, Caller& caller, List& list)
	{
		return (caller(list[BaseClass::_t1], list[BaseClass::_t2], list[BaseClass::_t3]));
	}
};

template <typename P1, typename P2, typename P3, typename P4>
struct TypeList4 : private Storage4<P1, P2, P3, P4>
{
	typedef Storage4<P1, P2, P3, P4> BaseClass;

	TypeList4(P1 p1, P2 p2, P3 p3, P4 p4) : BaseClass(p1, p2, p3, p4){}

	template <typename T>
	T	&operator[](Value<T> &value) { return (value.get()); }

	template <typename ReturnType, typename Caller, typename List>
	ReturnType operator()(TypeTraits<ReturnType>, Caller& caller, List& list)
	{
		return (caller(list[BaseClass::_t1], list[BaseClass::_t2], list[BaseClass::_t3], list[BaseClass::_t4]));
	}
};

template <typename P1, typename P2, typename P3, typename P4, typename P5>
struct TypeList5 : private Storage5<P1, P2, P3, P4, P5>
{
	typedef Storage5<P1, P2, P3, P4, P5> BaseClass;

	TypeList5(P1 p1, P2 p2, P3 p3, P4 p4, P5 p5) : BaseClass(p1, p2, p3, p4, p5){}

	template <typename T>
	T	&operator[](Value<T> &value) { return (value.get()); }

	template <typename ReturnType, typename Caller, typename List>
	ReturnType operator()(TypeTraits<ReturnType>, Caller& caller, List& list)
	{
		return (caller(list[BaseClass::_t1], list[BaseClass::_t2], list[BaseClass::_t3], list[BaseClass::_t4], list[BaseClass::_t5]));
	}
};

template <typename P1, typename P2, typename P3, typename P4, typename P5, typename P6>
struct TypeList6 : private Storage6<P1, P2, P3, P4, P5, P6>
{
	typedef Storage6<P1, P2, P3, P4, P5, P6> BaseClass;

	TypeList6(P1 p1, P2 p2, P3 p3, P4 p4, P5 p5, P6 p6) : BaseClass(p1, p2, p3, p4, p5, p6){}

	template <typename T>
	T	&operator[](Value<T> &value) { return (value.get()); }

	template <typename ReturnType, typename Caller, typename List>
	ReturnType operator()(TypeTraits<ReturnType>, Caller& caller, List& list)
	{
		return (caller(list[BaseClass::_t1], list[BaseClass::_t2], list[BaseClass::_t3], list[BaseClass::_t4], list[BaseClass::_t5], list[BaseClass::_t6]));
	}
};

struct Traits0
{
	typedef TypeList0	Type;
};

template <typename P1>
struct Traits1
{
	typedef typename GetType<P1>::Type	Type_Parameter_1;

	typedef TypeList1<Type_Parameter_1>	Type;
};

template <typename P1, typename P2>
struct Traits2
{
	typedef typename GetType<P1>::Type	Type_Parameter_1;
	typedef typename GetType<P2>::Type	Type_Parameter_2;

	typedef TypeList2<Type_Parameter_1, Type_Parameter_2>	Type;
};

template <typename P1, typename P2, typename P3>
struct Traits3
{
	typedef typename GetType<P1>::Type	Type_Parameter_1;
	typedef typename GetType<P2>::Type	Type_Parameter_2;
	typedef typename GetType<P3>::Type	Type_Parameter_3;

	typedef TypeList3<Type_Parameter_1, Type_Parameter_2, Type_Parameter_3>	Type;
};

template <typename P1, typename P2, typename P3, typename P4>
struct Traits4
{
	typedef typename GetType<P1>::Type	Type_Parameter_1;
	typedef typename GetType<P2>::Type	Type_Parameter_2;
	typedef typename GetType<P3>::Type	Type_Parameter_3;
	typedef typename GetType<P4>::Type	Type_Parameter_4;

	typedef TypeList4<Type_Parameter_1, Type_Parameter_2, Type_Parameter_3, Type_Parameter_4>	Type;
};

template <typename P1, typename P2, typename P3, typename P4, typename P5>
struct Traits5
{
	typedef typename GetType<P1>::Type	Type_Parameter_1;
	typedef typename GetType<P2>::Type	Type_Parameter_2;
	typedef typename GetType<P3>::Type	Type_Parameter_3;
	typedef typename GetType<P4>::Type	Type_Parameter_4;
	typedef typename GetType<P5>::Type	Type_Parameter_5;

	typedef TypeList5<Type_Parameter_1, Type_Parameter_2, Type_Parameter_3, Type_Parameter_4, Type_Parameter_5>	Type;
};

template <typename P1, typename P2, typename P3, typename P4, typename P5, typename P6>
struct Traits6
{
	typedef typename GetType<P1>::Type	Type_Parameter_1;
	typedef typename GetType<P2>::Type	Type_Parameter_2;
	typedef typename GetType<P3>::Type	Type_Parameter_3;
	typedef typename GetType<P4>::Type	Type_Parameter_4;
	typedef typename GetType<P5>::Type	Type_Parameter_5;
	typedef typename GetType<P6>::Type	Type_Parameter_6;

	typedef TypeList6<Type_Parameter_1, Type_Parameter_2, Type_Parameter_3, Type_Parameter_4, Type_Parameter_5, Type_Parameter_6>	Type;
};

template <typename Class, typename Func> class Pointer;
template <typename Class, typename TRet> class Pointer<Class, TRet(Class::*)(void)>
{
	Class		*_c;
	TRet(Class::*_f)(void);

public:
	Pointer(Class *c, TRet(Class::*f)(void)) : _c(c), _f(f) {}
	TRet	operator()(void) { return ((_c->*_f)()); }
};
template <typename Class> class Pointer<Class, void(Class::*)(void)>
{
	Class		*_c;
	void(Class::*_f)(void);

public:
	Pointer(Class *c, void(Class::*f)(void)) : _c(c), _f(f) {}
	void	operator()(void) { return ((_c->*_f)()); }
};
template <typename Class, typename TRet, typename T1> class Pointer<Class, TRet(Class::*)(T1)>
{
	Class		*_c;
	TRet(Class::*_f)(T1);

public:
	Pointer(Class *c, TRet(Class::*f)(T1)) : _c(c), _f(f) {}
	TRet	operator()(T1 t1) { return ((_c->*_f)(t1)); }
};
template <typename Class, typename T1> class Pointer<Class, void(Class::*)(T1)>
{
	Class		*_c;
	void(Class::*_f)(T1);

public:
	Pointer(Class *c, void(Class::*f)(T1)) : _c(c), _f(f) {}
	void	operator()(T1 t1) { return ((_c->*_f)(t1)); }
};

template <typename Class, typename TRet, typename T1, typename T2> class Pointer<Class, TRet(Class::*)(T1, T2)>
{
	Class		*_c;
	TRet(Class::*_f)(T1, T2);

public:
	Pointer(Class *c, TRet(Class::*f)(T1, T2)) : _c(c), _f(f) {}
	TRet	operator()(T1 t1, T2 t2) { return ((_c->*_f)(t1, t2)); }
};
template <typename Class, typename T1, typename T2> class Pointer<Class, void(Class::*)(T1, T2)>
{
	Class		*_c;
	void(Class::*_f)(T1, T2);

public:
	Pointer(Class *c, void(Class::*f)(T1, T2)) : _c(c), _f(f) {}
	void	operator()(T1 t1, T2 t2) { return ((_c->*_f)(t1, t2)); }
};

template <typename Class, typename TRet, typename T1, typename T2, typename T3> class Pointer<Class, TRet(Class::*)(T1, T2, T3)>
{
	Class		*_c;
	TRet(Class::*_f)(T1, T2, T3);

public:
	Pointer(Class *c, TRet(Class::*f)(T1, T2, T3)) : _c(c), _f(f) {}
	TRet	operator()(T1 t1, T2 t2, T3 t3) { return ((_c->*_f)(t1, t2, t3)); }
};
template <typename Class, typename T1, typename T2, typename T3> class Pointer<Class, void(Class::*)(T1, T2, T3)>
{
	Class		*_c;
	void(Class::*_f)(T1, T2, T3);

public:
	Pointer(Class *c, void(Class::*f)(T1, T2, T3)) : _c(c), _f(f) {}
	void	operator()(T1 t1, T2 t2, T3 t3) { return ((_c->*_f)(t1, t2, t3)); }
};

template <typename Class, typename TRet, typename T1, typename T2, typename T3, typename T4> class Pointer<Class, TRet(Class::*)(T1, T2, T3, T4)>
{
	Class		*_c;
	TRet(Class::*_f)(T1, T2, T3, T4);

public:
	Pointer(Class *c, TRet(Class::*f)(T1, T2, T3, T4)) : _c(c), _f(f) {}
	TRet	operator()(T1 t1, T2 t2, T3 t3, T4 t4) { return ((_c->*_f)(t1, t2, t3, t4)); }
};
template <typename Class, typename T1, typename T2, typename T3, typename T4> class Pointer<Class, void(Class::*)(T1, T2, T3, T4)>
{
	Class		*_c;
	void(Class::*_f)(T1, T2, T3, T4);

public:
	Pointer(Class *c, void(Class::*f)(T1, T2, T3, T4)) : _c(c), _f(f) {}
	void	operator()(T1 t1, T2 t2, T3 t3, T4 t4) { return ((_c->*_f)(t1, t2, t3, t4)); }
};

template <typename Class, typename TRet, typename T1, typename T2, typename T3, typename T4, typename T5> class Pointer<Class, TRet(Class::*)(T1, T2, T3, T4, T5)>
{
	Class		*_c;
	TRet(Class::*_f)(T1, T2, T3, T4, T5);

public:
	Pointer(Class *c, TRet(Class::*f)(T1, T2, T3, T4, T5)) : _c(c), _f(f) {}
	TRet	operator()(T1 t1, T2 t2, T3 t3, T4 t4, T5 t5) { return ((_c->*_f)(t1, t2, t3, t4, t5)); }
};
template <typename Class, typename T1, typename T2, typename T3, typename T4, typename T5> class Pointer<Class, void(Class::*)(T1, T2, T3, T4, T5)>
{
	Class		*_c;
	void(Class::*_f)(T1, T2, T3, T4, T5);

public:
	Pointer(Class *c, void(Class::*f)(T1, T2, T3, T4, T5)) : _c(c), _f(f) {}
	void	operator()(T1 t1, T2 t2, T3 t3, T4 t4, T5 t5) { return ((_c->*_f)(t1, t2, t3, t4, t5)); }
};

template <typename Class, typename TRet, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6> class Pointer<Class, TRet(Class::*)(T1, T2, T3, T4, T5, T6)>
{
	Class		*_c;
	TRet(Class::*_f)(T1, T2, T3, T4, T5, T6);

public:
	Pointer(Class *c, TRet(Class::*f)(T1, T2, T3, T4, T5, T6)) : _c(c), _f(f) {}
	TRet	operator()(T1 t1, T2 t2, T3 t3, T4 t4, T5 t5, T6 t6) { return ((_c->*_f)(t1, t2, t3, t4, t5, t6)); }
};
template <typename Class, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6> class Pointer<Class, void(Class::*)(T1, T2, T3, T4, T5, T6)>
{
	Class		*_c;
	void(Class::*_f)(T1, T2, T3, T4, T5, T6);

public:
	Pointer(Class *c, void(Class::*f)(T1, T2, T3, T4, T5, T6)) : _c(c), _f(f) {}
	void	operator()(T1 t1, T2 t2, T3 t3, T4 t4, T5 t5, T6 t6) { return ((_c->*_f)(t1, t2, t3, t4, t5, t6)); }
};

template <typename ReturnType>
Caller<ReturnType, ReturnType(*)(void), typename Traits0::Type > bind(ReturnType(*f)(void))
{
	typedef TypeList0	ListType;

	ListType	l();
	return (Caller<ReturnType, ReturnType(*)(void), ListType >(f, l));
}
template <typename ReturnType, typename Class>
Caller<ReturnType, Pointer<Class, ReturnType(Class::*)(void)>, typename Traits0::Type > bind(ReturnType(Class::*f)(void), Class *c)
{
	typedef TypeList0	ListType;
	typedef Pointer<Class, ReturnType(Class::*)(void)>	Pointer;

	ListType	l();
	return (Caller<ReturnType, Pointer, ListType >(Pointer(c, f), l));
}

template <typename ReturnType, typename X1, typename Param1>
Caller<ReturnType, ReturnType(*)(X1), typename Traits1<Param1>::Type > bind(ReturnType(*f)(X1), Param1 &&p1)
{
	typedef typename GetType<Param1>::Type	P1;
	typedef TypeList1<P1>					ListType;

	ListType	l(p1);
	return (Caller<ReturnType, ReturnType(*)(X1), ListType >(f, l));
}
template <typename ReturnType, typename Class, typename X1, typename Param1>
Caller<ReturnType, Pointer<Class, ReturnType(Class::*)(X1)>, typename Traits1<Param1>::Type > bind(ReturnType(Class::*f)(X1), Class *c, Param1 &&p1)
{
	typedef typename GetType<Param1>::Type	P1;
	typedef TypeList1<P1>					ListType;
	typedef Pointer<Class, ReturnType(Class::*)(X1)>	Pointer;

	ListType	l(p1);
	return (Caller<ReturnType, Pointer, ListType >(Pointer(c, f), l));
}

template <typename ReturnType, typename X1, typename X2, typename Param1, typename Param2>
Caller<ReturnType, ReturnType(*)(X1, X2), typename Traits2<Param1, Param2>::Type > bind(ReturnType(*f)(X1, X2), Param1 &&p1, Param2 &&p2)
{
	typedef typename GetType<Param1>::Type	P1;
	typedef typename GetType<Param2>::Type	P2;
	typedef TypeList2<P1, P2>				ListType;

	ListType	l(p1, p2);
	return (Caller<ReturnType, ReturnType(*)(X1, X2)>, ListType >(f, l));
}
template <typename ReturnType, typename Class, typename X1, typename X2, typename Param1, typename Param2>
Caller<ReturnType, Pointer<Class, ReturnType(Class::*)(X1, X2)>, typename Traits2<Param1, Param2>::Type > bind(ReturnType(Class::*f)(X1, X2), Class *c, Param1 &&p1, Param2 &&p2)
{
	typedef typename GetType<Param1>::Type	P1;
	typedef typename GetType<Param2>::Type	P2;
	typedef TypeList2<P1, P2>				ListType;
	typedef Pointer<Class, ReturnType(Class::*)(X1, X2)>	Pointer;

	ListType	l(p1, p2);
	return (Caller<ReturnType, Pointer, ListType >(Pointer(c, f), l));
}

template <typename ReturnType, typename X1, typename X2, typename X3, typename Param1, typename Param2, typename Param3>
Caller<ReturnType, ReturnType(*)(X1, X2, X3), typename Traits3<Param1, Param2, Param3 >::Type > bind(ReturnType(*f)(X1, X2, X3), Param1 &&p1, Param2 &&p2, Param3 &&p3)
{
	typedef typename GetType<Param1>::Type	P1;
	typedef typename GetType<Param2>::Type	P2;
	typedef typename GetType<Param3>::Type	P3;
	typedef TypeList3<P1, P2, P3>			ListType;

	ListType	l(p1, p2, p3);
	return (Caller<ReturnType, ReturnType(*)(X1, X2, X3), ListType >(f, l));
}
template <typename ReturnType, typename Class, typename X1, typename X2, typename X3, typename Param1, typename Param2, typename Param3>
Caller<ReturnType, Pointer<Class, ReturnType(Class::*)(X1, X2, X3)>, typename Traits3<Param1, Param2, Param3 >::Type > bind(ReturnType(Class::*f)(X1, X2, X3), Class *c, Param1 &&p1, Param2 &&p2, Param3 &&p3)
{
	typedef typename GetType<Param1>::Type	P1;
	typedef typename GetType<Param2>::Type	P2;
	typedef typename GetType<Param3>::Type	P3;
	typedef TypeList3<P1, P2, P3>			ListType;
	typedef Pointer<Class, ReturnType(Class::*)(X1, X2, X3)>	Pointer;

	ListType	l(p1, p2, p3);
	return (Caller<ReturnType, Pointer, ListType >(Pointer(c, f), l));
}

template <typename ReturnType, typename X1, typename X2, typename X3, typename X4, typename Param1, typename Param2, typename Param3, typename Param4>
Caller<ReturnType, ReturnType(*)(X1, X2, X3, X4), typename Traits4<Param1, Param2, Param3, Param4>::Type > bind(ReturnType(*f)(X1, X2, X3, X4), Param1 &&p1, Param2 &&p2, Param3 &&p3, Param4 &&p4)
{
	typedef typename GetType<Param1>::Type	P1;
	typedef typename GetType<Param2>::Type	P2;
	typedef typename GetType<Param3>::Type	P3;
	typedef typename GetType<Param4>::Type	P4;
	typedef TypeList4<P1, P2, P3, P4>		ListType;

	ListType	l(p1, p2, p3, p4);
	return (Caller<ReturnType, ReturnType(*)(X1, X2, X3, X4), ListType >(f, l));
}
template <typename ReturnType, typename Class, typename X1, typename X2, typename X3, typename X4, typename Param1, typename Param2, typename Param3, typename Param4>
Caller<ReturnType, Pointer<Class, ReturnType(Class::*)(X1, X2, X3, X4)>, typename Traits4<Param1, Param2, Param3, Param4>::Type > bind(ReturnType(Class::*f)(X1, X2, X3, X4), Class *c, Param1 &&p1, Param2 &&p2, Param3 &&p3, Param4 &&p4)
{
	typedef typename GetType<Param1>::Type	P1;
	typedef typename GetType<Param2>::Type	P2;
	typedef typename GetType<Param3>::Type	P3;
	typedef typename GetType<Param4>::Type	P4;
	typedef TypeList4<P1, P2, P3, P4>		ListType;
	typedef Pointer<Class, ReturnType(Class::*)(X1, X2, X3, X4)>	Pointer;

	ListType	l(p1, p2, p3, p4);
	return (Caller<ReturnType, Pointer, ListType >(Pointer(c, f), l));
}

template <typename ReturnType, typename X1, typename X2, typename X3, typename X4, typename X5, typename Param1, typename Param2, typename Param3, typename Param4, typename Param5>
Caller<ReturnType, ReturnType(*)(X1, X2, X3, X4, X5), typename Traits5<Param1, Param2, Param3, Param4, Param5>::Type > bind(ReturnType(*f)(X1, X2, X3, X4, X5), Param1 &&p1, Param2 &&p2, Param3 &&p3, Param4 &&p4, Param5 &&p5)
{
	typedef typename GetType<Param1>::Type	P1;
	typedef typename GetType<Param2>::Type	P2;
	typedef typename GetType<Param3>::Type	P3;
	typedef typename GetType<Param4>::Type	P4;
	typedef typename GetType<Param5>::Type	P5;
	typedef TypeList5<P1, P2, P3, P4, P5>	ListType;

	ListType	l(p1, p2, p3, p4, p5);
	return (Caller<ReturnType, ReturnType(*)(X1, X2, X3, X4, X5), ListType >(f, l));
}
template <typename ReturnType, typename Class, typename X1, typename X2, typename X3, typename X4, typename X5, typename Param1, typename Param2, typename Param3, typename Param4, typename Param5>
Caller<ReturnType, Pointer<Class, ReturnType(Class::*)(X1, X2, X3, X4, X5)>, typename Traits5<Param1, Param2, Param3, Param4, Param5>::Type > bind(ReturnType(Class::*f)(X1, X2, X3, X4, X5), Class *c, Param1 &&p1, Param2 &&p2, Param3 &&p3, Param4 &&p4, Param5 &&p5)
{
	typedef typename GetType<Param1>::Type	P1;
	typedef typename GetType<Param2>::Type	P2;
	typedef typename GetType<Param3>::Type	P3;
	typedef typename GetType<Param4>::Type	P4;
	typedef typename GetType<Param5>::Type	P5;
	typedef TypeList5<P1, P2, P3, P4, P5>	ListType;
	typedef Pointer<Class, ReturnType(Class::*)(X1, X2, X3, X4, X5)>	Pointer;

	ListType	l(p1, p2, p3, p4, p5);
	return (Caller<ReturnType, Pointer, ListType >(Pointer(c, f), l));
}

template <typename ReturnType, typename X1, typename X2, typename X3, typename X4, typename X5, typename X6, typename Param1, typename Param2, typename Param3, typename Param4, typename Param5, typename Param6>
Caller<ReturnType, ReturnType(*)(X1, X2, X3, X4, X5, X6), typename Traits6<Param1, Param2, Param3, Param4, Param5, Param6>::Type > bind(ReturnType(*f)(X1, X2, X3, X4, X5, X6), Param1 &&p1, Param2 &&p2, Param3 &&p3, Param4 &&p4, Param5 &&p5, Param6 &&p6)
{
	typedef typename GetType<Param1>::Type		P1;
	typedef typename GetType<Param2>::Type		P2;
	typedef typename GetType<Param3>::Type		P3;
	typedef typename GetType<Param4>::Type		P4;
	typedef typename GetType<Param5>::Type		P5;
	typedef typename GetType<Param6>::Type		P6;
	typedef TypeList5<P1, P2, P3, P4, P5, P6>	ListType;

	ListType	l(p1, p2, p3, p4, p5, p6);
	return (Caller<ReturnType, ReturnType(*)(X1, X2, X3, X4, X5, X6), ListType >(f, l));
}
template <typename ReturnType, typename Class, typename X1, typename X2, typename X3, typename X4, typename X5, typename X6, typename Param1, typename Param2, typename Param3, typename Param4, typename Param5, typename Param6>
Caller<ReturnType, Pointer<Class, ReturnType(Class::*)(X1, X2, X3, X4, X5, X6)>, typename Traits6<Param1, Param2, Param3, Param4, Param5, Param6>::Type > bind(ReturnType(Class::*f)(X1, X2, X3, X4, X5, X6), Class *c, Param1 &&p1, Param2 &&p2, Param3 &&p3, Param4 &&p4, Param5 &&p5, Param6 &&p6)
{
	typedef typename GetType<Param1>::Type		P1;
	typedef typename GetType<Param2>::Type		P2;
	typedef typename GetType<Param3>::Type		P3;
	typedef typename GetType<Param4>::Type		P4;
	typedef typename GetType<Param5>::Type		P5;
	typedef typename GetType<Param6>::Type		P6;
	typedef TypeList5<P1, P2, P3, P4, P5, P6>	ListType;
	typedef Pointer<Class, ReturnType(Class::*)(X1, X2, X3, X4, X5, X6)>	Pointer;

	ListType	l(p1, p2, p3, p4, p5, p6);
	return (Caller<ReturnType, Pointer, ListType >(Pointer(c, f), l));
}
