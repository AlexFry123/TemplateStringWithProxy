#pragma once
#include <string.h>
#include <iostream>
using namespace std;

template<typename T>
class String {
private:
	struct StringStruct;
	StringStruct* _rep;
	size_t length(const T* t);
	T read(const size_t i) const;
	void write(const size_t i, T c);
public:
	class Proxy;
	class BadString;
	String() : _rep (new StringStruct(0, new T[1]))
	{
		return;
	}
	explicit String(const T*);
	String(const String& s);
	~String();
	String& operator=(const String&);
	String& operator=(const T*);
	Proxy operator[](const size_t i) {
		if (_rep->_len <= i) throw BadString("Bad Index", i);
		return Proxy(*this, i);
	};
	T operator[](const size_t i) const; 
	size_t length() const { return _rep->_len; }
	bool empty() const { return _rep->_len == 0; }
};

template<typename T>
const String<T> operator+(const String<T>&str1, const String<T> &str)
{
	size_t newlen = str1.length() + str.length();
	T* allocat = new T[newlen + 1];
	for (size_t i = 0; i < newlen; i++) {
		if (i >= str1.length()) {
			allocat[i] = str[i - str1.length()];
			continue;
		}
		allocat[i] = str1[i];
	}
	allocat[newlen] = 0;
	//char* resAlloc = new char[str1.length() + str.length() + 1];
	//strcpy(resAlloc, str1.c_str());
	//strcpy(resAlloc + str1.length(), str.c_str());
	//resAlloc[str1.length() + str.length()] = '\0';
	String<T> res(allocat);
	return res;
}

template<typename T>
bool operator==(const String<T>& a, const String<T> &str)
{
	bool equal = a.length() == str.length();
	if (!equal) return equal;
	for (size_t i = 0; (i < a.length()) && equal; i++) {
		equal = a[i] == str[i];
		if (!equal) break;
	}
	return equal;
}

template<typename T>
bool operator!=(const String<T>& a, const String<T>& str)
{
	return !(a == str);
}

template<typename T>
bool operator<(const  String<T>& a, const  String<T>& str)
{
	bool res = true;
	size_t i = 0;
	while (res && (i < a.length()) && (i < str.length()))
	{
		res = res && (a[i] == str[i]);
		i++;
	}
	if (res)
		return a.length() < str.length();
	i--;
	return a[i] < str[i];
}

template<typename T>
bool operator<=(const String<T>& a, const String<T> &str)
{
	if (a == str)
		return true;
	return a < str;

}

template<typename T>
bool operator>(const String<T>& a, const String<T> &str)
{
	return !(a <= str);
}

template<typename T>
bool operator>=(const String<T>& a, const String<T> &str)
{
	return !(a < str);
}

template<typename T>
ostream& operator<<(ostream& os, const String<T> &s)
{
	for (size_t i = 0; i < s.length(); i++)
		os << static_cast<char>(s[i]);
	return os;
}

template<typename T>
class String<T>::BadString
{
private:
	string _reason;
	size_t _index;
public:
	BadString(string reason = "", size_t index = 0) :
		_reason(reason), _index(index)
	{
		return;
	};
	~BadString() {};
	void diagnose() const
	{
		cerr << _reason;
		if (_index != 0)
			cerr << ' ' << _index;
		cerr << endl;
	}
};

template<typename T>
size_t String<T>::length(const T * t)
{
	size_t n = 0;
	while (*t++)
		++n;
	return n;
}

template<typename T>
String<T>::String(const T *s)
{
	_rep = new StringStruct(length(s), s);
	return;
}

template<typename T>
String<T>::String(const String & s)
{
	s._rep->_refCounter++; 
	_rep = s._rep;
	return;
}

template<typename T>
String<T>::~String()
{
	if (--_rep->_refCounter == 0)
		delete _rep;
	return;
}

template<typename T>
String<T>& String<T>::operator=(const String& s)
{
		s._rep->_refCounter++;
		assert((&s == this) ? _rep->_refCounter > 1:true);
		if (--_rep->_refCounter == 0) 
			delete _rep;
		_rep = s._rep;
		return *this;
}

template<typename T>
String<T> & String<T>::operator=(const T *s)
{
	if (s == 0)
		throw BadString("Attempt to use not defined pointer");
	if (_rep->_refCounter == 1)
		_rep->assign(length(s), s);
	else
	{
		_rep->_refCounter--;
		_rep = new StringStruct(length(s), s);
	}
	return *this;
}

template<typename T>
T String<T>::read(const size_t i) const
{
	return _rep->_allocator[i];
}

template<typename T>
void String<T>::write(const size_t i, T c)
{
	_rep = _rep->getCopy();
	_rep->_allocator[i] = c;
	return;
}

template<typename T>
T String<T>::operator[](const size_t i) const
{
	if(_rep->_len <= i) throw BadString("Bad Index", i);
	return _rep->_allocator[i];
}

template<typename T>
class String<T>::Proxy {
	friend class String<T>;
private:
	String<T>& _proxyship;
	size_t _index;
	Proxy(String<T>& s, const size_t i) : _proxyship(s), _index(i)
	{
		return;
	}
public:
	const T* operator&() const;
	T* operator&(); 
	operator T& (); 
	operator T() const;
	Proxy& operator=(T c) {
		_proxyship.write(_index, c);
		return *this;
	}
};

template<typename T>
String<T>::Proxy::operator T() const {
	return _proxyship.read(_index);
}

template<typename T>
const T* String<T>::Proxy:: operator&() const {
	return &_proxyship._rep->_allocator[_index];
}

template<typename T>
T* String<T>::Proxy::operator&() {
	if (_proxyship._rep->isShareable() && _proxyship._rep->_refCounter > 1) {
		_proxyship._rep->_refCounter--;
			_proxyship._rep = new StringStruct(_proxyship._rep->_len,_proxyship._rep->_allocator);
	}
	_proxyship._rep->makeUnshareable();
	return &_proxyship._rep->_allocator[_index];
}

template<typename T>
String<T>::Proxy::operator T&() {
	if (_proxyship._rep->isShareable() && _proxyship._rep->_refCounter > 1) {
		_proxyship._rep->_refCounter--;
		_proxyship._rep = new StringStruct(_proxyship._rep->_len, _proxyship._rep->_allocator);
	}
	_proxyship._rep->makeUnshareable();
	return _proxyship._rep->_allocator[_index];
}

template<typename T>
struct String<T>::StringStruct {
	size_t _len;
	T* _allocator;
	size_t _refCounter;
	bool _shareable;
	StringStruct(size_t len, const T *s);
	~StringStruct() { delete [] _allocator; _allocator = 0; return; }
	StringStruct* getCopy() {
		if (_refCounter == 1)
			return this;
		_refCounter--;
		return new StringStruct(_len, _allocator);
	}
	void assign(size_t len, const T *ps) {
		if (ps == 0) throw BadString("Attempt to use not defined pointer");
		if (_len != len) {
			delete[] _allocator;
			_len = len;
			_allocator = new T[_len + 1];
		}
		for (size_t i = 0; i < len; i++)
			_allocator[i] = ps[i];
		_allocator[len] = 0;
		return;
	}
	void makeShareable() { _shareable = true; }
	void makeUnshareable() { _shareable = false; }
	bool isShareable() const { return _shareable; }
private:
	StringStruct(const StringStruct&);
	StringStruct& operator=(const StringStruct&);
};

template<typename T>
String<T>::StringStruct::StringStruct(size_t len, const T *s) :_refCounter(1), _shareable(true), _len(len), _allocator(new T[_len + 1]) {
	for (size_t i = 0; i < len; i++)
		_allocator[i] = s[i];
	_allocator[_len] = 0;
		return;
};
