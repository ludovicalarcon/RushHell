#pragma once

template <typename TRet, typename TArg1, typename TArg2, typename TArg3, typename TArg4> struct _IPointer;
template <typename TRet> struct _IPointer<TRet, void, void, void, void> { virtual TRet	operator()(void) = 0; };
template <typename TRet, typename TArg1> struct _IPointer<TRet, TArg1, void, void, void> { virtual TRet	operator()(TArg1 arg1) = 0; };
template <typename TRet, typename TArg1, typename TArg2> struct _IPointer<TRet, TArg1, TArg2, void, void> { virtual TRet	operator()(TArg1 arg1, TArg2 arg2) = 0; };
template <typename TRet, typename TArg1, typename TArg2, typename TArg3> struct _IPointer<TRet, TArg1, TArg2, TArg3, void> { virtual TRet	operator()(TArg1 arg1, TArg2 arg2, TArg3 arg3) = 0; };
template <typename TRet, typename TArg1, typename TArg2, typename TArg3, typename TArg4> struct _IPointer { virtual TRet	operator()(TArg1 arg1, TArg2 arg2, TArg3 arg3, TArg4 arg4) = 0; };

template <typename TPtr, typename TRet, typename TArg1, typename TArg2, typename TArg3, typename TArg4> struct _Pointer;
template <typename TPtr, typename TRet> struct _Pointer<TPtr, TRet, void, void, void, void> : public _IPointer<TRet, void, void, void, void>
{
	_Pointer(TPtr ptr) : _ptr(ptr) {}
	TRet	operator()(void) { return (_ptr()); }
	TPtr	_ptr;
};
template <typename TPtr> struct _Pointer<TPtr, void, void, void, void, void> : public _IPointer<void, void, void, void, void>
{
	_Pointer(TPtr ptr) : _ptr(ptr) {}
	void	operator()(void) { _ptr(); }
	TPtr	_ptr;
};

template <typename TPtr, typename TRet, typename TArg1> struct _Pointer<TPtr, TRet, TArg1, void, void, void> : public _IPointer<TRet, TArg1, void, void, void>
{
	_Pointer(TPtr ptr) : _ptr(ptr) {}
	TRet	operator()(TArg1 arg1) { return (_ptr(arg1)); }
	TPtr	_ptr;
};
template <typename TPtr, typename TArg1> struct _Pointer<TPtr, void, TArg1, void, void, void> : public _IPointer<void, TArg1, void, void, void>
{
	_Pointer(TPtr ptr) : _ptr(ptr) {}
	void	operator()(TArg1 arg1) { _ptr(arg1); }
	TPtr	_ptr;
};

template <typename TPtr, typename TRet, typename TArg1, typename TArg2> struct _Pointer<TPtr, TRet, TArg1, TArg2, void, void> : public _IPointer<TRet, TArg1, TArg2, void, void>
{
	_Pointer(TPtr ptr) : _ptr(ptr) {}
	TRet	operator()(TArg1 arg1, TArg2 arg2) { return (_ptr(arg1, arg2)); }
	TPtr	_ptr;
};
template <typename TPtr, typename TArg1, typename TArg2> struct _Pointer<TPtr, void, TArg1, TArg2, void, void> : public _IPointer<void, TArg1, TArg2, void, void>
{
	_Pointer(TPtr ptr) : _ptr(ptr) {}
	void	operator()(TArg1 arg1, TArg2 arg2) { _ptr(arg1, arg2); }
	TPtr	_ptr;
};

template <typename TPtr, typename TRet, typename TArg1, typename TArg2, typename TArg3> struct _Pointer<TPtr, TRet, TArg1, TArg2, TArg3, void> : public _IPointer<TRet, TArg1, TArg2, TArg3, void>
{
	_Pointer(TPtr ptr) : _ptr(ptr) {}
	TRet	operator()(TArg1 arg1, TArg2 arg2, TArg3 arg3) { return (_ptr(arg1, arg2, arg3)); }
	TPtr	_ptr;
};
template <typename TPtr, typename TArg1, typename TArg2, typename TArg3> struct _Pointer<TPtr, void, TArg1, TArg2, TArg3, void> : public _IPointer<void, TArg1, TArg2, TArg3, void>
{
	_Pointer(TPtr ptr) : _ptr(ptr) {}
	void	operator()(TArg1 arg1, TArg2 arg2, TArg3 arg3) { _ptr(arg1, arg2, arg3); }
	TPtr	_ptr;
};

template <typename TPtr, typename TRet, typename TArg1, typename TArg2, typename TArg3, typename TArg4> struct _Pointer : public _IPointer<TRet, TArg1, TArg2, TArg3, TArg4>
{
	_Pointer(TPtr ptr) : _ptr(ptr) {}
	TRet	operator()(TArg1 arg1, TArg2 arg2, TArg3 arg3, TArg4 arg4) { return (_ptr(arg1, arg2, arg3, arg4)); }
	TPtr	_ptr;
};
template <typename TPtr, typename TArg1, typename TArg2, typename TArg3, typename TArg4> struct _Pointer<TPtr, void, TArg1, TArg2, TArg3, TArg4> : public _IPointer<void, TArg1, TArg2, TArg3, TArg4>
{
	_Pointer(TPtr ptr) : _ptr(ptr) {}
	void	operator()(TArg1 arg1, TArg2 arg2, TArg3 arg3, TArg4 arg4) { _ptr(arg1, arg2, arg3, arg4); }
	TPtr	_ptr;
};

template <typename TRet, typename TArg1, typename TArg2, typename TArg3, typename TArg4> class _FunctionBase;
template <typename TRet> class _FunctionBase<TRet, void, void, void, void>
{
	_IPointer<TRet, void, void, void, void>	*_func;
public:
	template <typename Type> _FunctionBase(Type func) { _func = new _Pointer<Type, TRet, void, void, void, void>(func); }
	TRet	operator()(void) { return ((*_func)()); }
};
template <> class _FunctionBase<void, void, void, void, void>
{
	_IPointer<void, void, void, void, void>	*_func;
public:
	template <typename Type> _FunctionBase(Type func) { _func = new _Pointer<Type, void, void, void, void, void>(func); }
	void	operator()(void) { (*_func)(); }
};

template <typename TRet, typename TArg1> class _FunctionBase<TRet, TArg1, void, void, void>
{
	_IPointer<TRet, TArg1, void, void, void>	*_func;
public:
	template <typename Type> _FunctionBase(Type func) { _func = new _Pointer<Type, TRet, TArg1, void, void, void>(func); }
	TRet	operator()(TArg1 arg1) { return ((*_func)(arg1)); }
};
template <typename TArg1> class _FunctionBase<void, TArg1, void, void, void>
{
	_IPointer<void, TArg1, void, void, void>	*_func;
public:
	template <typename Type> _FunctionBase(Type func) { _func = new _Pointer<Type, void, TArg1, void, void, void>(func); }
	void	operator()(TArg1 arg1) { (*_func)(arg1); }
};

template <typename TRet, typename TArg1, typename TArg2> class _FunctionBase<TRet, TArg1, TArg2, void, void>
{
	_IPointer<TRet, TArg1, TArg2, void, void>	*_func;
public:
	template <typename Type> _FunctionBase(Type func) { _func = new _Pointer<Type, TRet, TArg1, TArg2, void, void>(func); }
	TRet	operator()(TArg1 arg1, TArg2 arg2) { return ((*_func)(arg1, arg2)); }
};
template <typename TArg1, typename TArg2> class _FunctionBase<void, TArg1, TArg2, void, void>
{
	_IPointer<void, TArg1, TArg2, void, void>	*_func;
public:
	template <typename Type> _FunctionBase(Type func) { _func = new _Pointer<Type, void, TArg1, TArg2, void, void>(func); }
	void	operator()(TArg1 arg1, TArg2 arg2) { (*_func)(arg1, arg2); }
};

template <typename TRet, typename TArg1, typename TArg2, typename TArg3> class _FunctionBase<TRet, TArg1, TArg2, TArg3, void>
{
	_IPointer<TRet, TArg1, TArg2, TArg3, void>	*_func;
public:
	template <typename Type> _FunctionBase(Type func) { _func = new _Pointer<Type, TRet, TArg1, TArg2, TArg3, void>(func); }
	TRet	operator()(TArg1 arg1, TArg2 arg2, TArg3 arg3) { return ((*_func)(arg1, arg2, arg3)); }
};
template <typename TArg1, typename TArg2, typename TArg3> class _FunctionBase<void, TArg1, TArg2, TArg3, void>
{
	_IPointer<void, TArg1, TArg2, TArg3, void>	*_func;
public:
	template <typename Type> _FunctionBase(Type func) { _func = new _Pointer<Type, void, TArg1, TArg2, TArg3, void>(func); }
	void	operator()(TArg1 arg1, TArg2 arg2, TArg3 arg3) { (*_func)(arg1, arg2, arg3); }
};

template <typename TRet, typename TArg1, typename TArg2, typename TArg3, typename TArg4> class _FunctionBase
{
	_IPointer<TRet, TArg1, TArg2, TArg3, TArg4>	*_func;
public:
	template <typename Type> _FunctionBase(Type func) { _func = new _Pointer<Type, TRet, TArg1, TArg2, TArg3, TArg4>(func); }
	TRet	operator()(TArg1 arg1, TArg2 arg2, TArg3 arg3, TArg4 arg4) { return ((*_func)(arg1, arg2, arg3, arg4)); }
};
template <typename TArg1, typename TArg2, typename TArg3, typename TArg4> class _FunctionBase<void, TArg1, TArg2, TArg3, TArg4>
{
	_IPointer<void, TArg1, TArg2, TArg3, TArg4>	*_func;
public:
	template <typename Type> _FunctionBase(Type func) { _func = new _Pointer<Type, void, TArg1, TArg2, TArg3, TArg4>(func); }
	void	operator()(TArg1 arg1, TArg2 arg2, TArg3 arg3, TArg4 arg4) { (*_func)(arg1, arg2, arg3, arg4); }
};

template <typename TFunc> struct _Function;
template <typename TRet> struct _Function<TRet(void)>{ typedef _FunctionBase<TRet, void, void, void, void> type; };
template <typename TRet, typename TArg1> struct _Function<TRet(TArg1)> { typedef _FunctionBase<TRet, TArg1, void, void, void> type; };
template <typename TRet, typename TArg1, typename TArg2> struct _Function<TRet(TArg1, TArg2)> { typedef _FunctionBase<TRet, TArg1, TArg2, void, void> type; };
template <typename TRet, typename TArg1, typename TArg2, typename TArg3> struct _Function<TRet(TArg1, TArg2, TArg3)> { typedef _FunctionBase<TRet, TArg1, TArg2, TArg3, void> type; };
template <typename TRet, typename TArg1, typename TArg2, typename TArg3, typename TArg4> struct _Function<TRet(TArg1, TArg2, TArg3, TArg4)> { typedef _FunctionBase<TRet, TArg1, TArg2, TArg3, TArg4> type; };

template <typename TFunc> class Function : public _Function<TFunc>::type
{
	typedef typename _Function<TFunc>::type	_Base;
public:
	template <typename Type>
	Function(Type func) : _Base(func) {}
};

//namespace _
//{
//
//	template <typename Type> class Pointer;
//	template <typename TRet, typename ...Args> struct Pointer < TRet(Args...) > { virtual TRet	operator()(Args ...args) = 0; };
//
//	template <typename TFunc, typename Type> class ImpPointer;
//	template <typename TFunc, typename TRet, typename ...Args> class ImpPointer<TFunc, TRet(Args...)> : public Pointer < TRet(Args...) >
//	{
//	protected:
//		TFunc	&&_func;
//
//	public:
//		ImpPointer(TFunc &&func) : _func(func) {}
//		TRet	operator()(Args ...args) { return (_func(args...)); }
//	};
//	template <typename TFunc, typename ...Args> class ImpPointer<TFunc, void(Args...)> : public Pointer < void(Args...) >
//	{
//	protected:
//		TFunc	&&_func;
//
//	public:
//		ImpPointer(TFunc &&func) : _func(func) {}
//		void	operator()(Args ...args) { _func(args...); }
//	};
//
//	template<typename Type> class Function
//	{
//	protected:
//		Pointer<Type>	*_func;
//
//	public:
//		Function(void) : _func(NULL) {}
//		~Function(void) { if (_func) delete (_func); }
//
//		template<typename TFunc> void	assign(TFunc &&func)
//		{
//			if (_func) delete (_func);
//			_func = new ImpPointer<TFunc, Type>(func);
//		}
//	};
//}
//
//template <typename Type> class Function;
//template <typename TRet, typename ...Args> class Function<TRet(Args...)> : public _::Function < TRet(Args...) >
//{
//	typedef Function<TRet(Args...)>		myself;
//	typedef _::Function<TRet(Args...)>	base;
//public:
//	Function(void) {}
//	template <typename TFunc> Function(TFunc &&func) { base::assign(func); }
//
//	TRet	operator()(Args ...args) { return ((*base::_func)(args...)); }
//
//	template <typename TFunc> myself	&operator=(TFunc &&func) { base::assign(func); return (*this); }
//};
//template <typename ...Args> class Function<void(Args...)> : public _::Function < void(Args...) >
//{
//	typedef Function<void(Args...)>		myself;
//	typedef _::Function<void(Args...)>	base;
//public:
//	Function(void) {}
//	template <typename TFunc> Function(TFunc &&func) { base::assign(func); }
//
//	void	operator()(Args ...args) { (*base::_func)(args...); }
//
//	template <typename TFunc> myself	&operator=(TFunc &&func) { base::assign(func); return (*this); }
//};
