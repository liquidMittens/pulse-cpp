#ifndef FOO_H_
#define FOO_H_
#include <string>
#include <ostream>
#include <format>

class Foo
{
public:
	Foo();
	~Foo();

	void AddToNumber(const int& x);
	void AddToString(const std::string& str);
	const std::string CombineNumberAndString();

	friend std::ostream& operator<<(std::ostream& os, const Foo& obj)
	{
		os << std::format("Number: {} | Name: {}", obj.number(), obj.name());
		return os;
	}

	const int& number() const { return _number; }
	const std::string& name() const { return _name; }

private: 
	int _number;
	std::string _name;
};



#endif
