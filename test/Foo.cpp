#include "Foo.h"
#include <iostream>

Foo::Foo() :
	_number(-1),
	_name("")
{

}

Foo::~Foo()
{

}

void Foo::AddToNumber(const int& x)
{
	_number += x;
}

void Foo::AddToString(const std::string& str)
{
	_name.append(" ").append(str);
}

const std::string Foo::CombineNumberAndString()
{
	return std::format("Combined: {}-{}", _number, _name);
}