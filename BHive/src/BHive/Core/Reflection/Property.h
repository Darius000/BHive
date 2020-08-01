#pragma once

template<typename T>
class Property
{
public:
	virtual ~Property(){}
	virtual T& operator = (const T& f){ return value = f; }
	virtual const T& operator() () const { return value; }
	virtual explicit operator const T& () const { return value; }
	virtual T* operator->(){ return &value };
protected:
	T value;
};


template <typename T>
class ReadOnlyProperty
{
public:
	virtual ~ReadOnlyProperty(){}
	virtual operator T const& () const { return value; }

protected:
	T value;
};

class Test
{
public:	
	Property<float> x;
	Property<bool> y;
	Property<Test*> t;
	Test(){x = 8; }
};

//int main()
//{
//	Test test = Test();
//	test.x = 32;
//	test.y = false;
//	test.t = new Test();
//	test.t->x = 40;
//	test.t->y = true;
//}