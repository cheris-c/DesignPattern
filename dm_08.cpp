/*工厂模式的实现案例*/
#include <iostream>
using namespace std;
#include <string.h>

//抽象角色
class Fruit
{
public:
	virtual void getFruit() = 0;//所有实例的公共接口
};

//具体产品类
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

//抽象工厂类
class AbFactory
{
public:
	virtual Fruit* Create() = 0;
};

//具体工厂类
class BananaFac : public AbFactory
{
public:
	virtual Fruit* Create()
	{
		return new Banana();
	}
};

class AppleFac : public AbFactory
{
public:
	virtual Fruit* Create()
	{
		return new Apple();
	}
};


int main()
{
	AbFactory *fac = NULL;
	Fruit *f = NULL;

	fac = new BananaFac();
	f = fac->Create();
	f->getFruit();

	delete fac;
	delete f;

	return 0;
}