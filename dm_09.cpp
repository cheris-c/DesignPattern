/*抽象工厂模式的实现案例*/
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
class SorthApple : public Fruit
{
public:
	virtual void getFruit()
	{
		cout << "Get sorth apple!" << endl;
	}
};

class NorthApple : public Fruit
{
public:
	virtual void getFruit()
	{
		cout << "Get north apple!" << endl;
	}
};

class NorthBanana : public Fruit
{
public:
	virtual void getFruit()
	{
		cout << "Get north banana!" << endl;
	}
};

class SorthBanana : public Fruit
{
public:
	virtual void getFruit()
	{
		cout << "Get sorth banana!" << endl;
	}
};


//抽象工厂类
//弊端所在，无法再创建其他水果，但是从工厂类别的角度看符合设计模式原则
class AbFactory
{
public:
	virtual Fruit* createApple() = 0;
	virtual Fruit* createBanana() = 0;
};

//具体工厂类
class NorthFac : public AbFactory
{
public:
	virtual Fruit* createBanana()
	{
		return new NorthBanana();
	}
	virtual Fruit* createApple()
	{
		return new NorthApple();
	}
};

class SorthFac : public AbFactory
{
public:
	virtual Fruit* createBanana()
	{
		return new SorthBanana();
	}
	virtual Fruit* createApple()
	{
		return new SorthApple();
	}
};


int main()
{
	AbFactory *fac = NULL;
	Fruit *f = NULL;

	//----------生产南方水果
	fac = new SorthFac();
	f = fac->createBanana();
	f->getFruit();
	delete f;
	f = fac->createApple();
	f->getFruit();
	delete f;
	delete fac;

	//-----------生产北方水果
	fac = new NorthFac();
	f = fac->createBanana();
	f->getFruit();
	delete f;
	f = fac->createApple();
	f->getFruit();
	delete f;
	delete fac;


	return 0;
}