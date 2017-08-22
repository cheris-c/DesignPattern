/*简单工厂模式的实现案例*/
#include <iostream>
using namespace std;
#include <string.h>

class Fruit
{
public:
	virtual void getFruit() = 0;
};

class Apple : public Fruit
{
public:
	virtual void getFruit()
	{
		cout << "Get apple!" << endl;
	}
};

class Banana : public Fruit
{
public:
	virtual void getFruit()
	{
		cout << "Get Banana!" << endl;
	}
};

class Orange : public Fruit
{
public:
	virtual void getFruit()
	{
		cout << "Get Orange!" << endl;
	}
};

class Factory
{
public:
	Fruit* Create(char *p)
	{
		if (strcmp(p, "Banana") == 0)
			return new Banana();
		else if (strcmp(p, "Apple") == 0)
			return new Apple();
		else if (strcmp(p, "Orange") == 0)
			return new Orange();
	}
};

int main()
{
	Factory fac;
	Fruit *f = fac.Create("Banana");
	f->getFruit();

	return 0;
}