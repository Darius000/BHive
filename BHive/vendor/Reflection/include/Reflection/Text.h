#pragma once

#include "AdditionalProperties.h"

/*Example File
class Text;

namespace Reflection
{
	DEFINE_CLASS(Text)
	//DEFINE_PROPERTY(Text, Text)
}

class Text
{
public:
	Text() :line(), text(nullptr) {}
	~Text() { delete text; }

	std::string line;
	int age = 20;
	float height = 53.5;

	Text* text;

	virtual bool operator==(const Text& v) const { return line == v.line; }
	virtual bool operator!=(const Text& v) const { return line != v.line; }
	virtual bool operator>=(const Text& v) const { return line >= v.line; }
	virtual bool operator<=(const Text& v) const { return line <= v.line; }
	virtual bool operator>(const Text& v) const { return  line > v.line; }
	virtual bool operator<(const Text& v) const { return  line < v.line; }
	Text& operator=(const Text& text);
	friend std::ostream& operator<<(std::ostream& os, const Text& t)
	{
		os << t.line;
		return os;
	}
	friend std::fstream& operator>>(std::fstream& is, Text& t)
	{
		is >> t.line;
		return is;
	}
	using T = Text;
	Reflection::TextClass Class = {"TEXT", this,{
	new Reflection::Property<std::string>{"line", &(Text::line)},
	new Reflection::Property<int>{"age", &(Text::age)},
	new Reflection::Property<float>{"height", &(Text::height)},
	new Reflection::Property<Text>{"Text", (Text::text)}}};

	Reflection::TextClass& GetClass() { return Class; }
};
*/
