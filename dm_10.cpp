#include <iostream>
using namespace std;

//复杂对象的抽象类
class House
{
public:
	void setDoor(string door) { m_door = door; }
	void setWall(string wall) { m_wall = wall; }
	void setWindow(string window) { m_window = window; }

	string getDoor() { return m_door; }
	string getWall() { return m_wall; }
	string getWindow() { return m_window; }

private:
	string m_door;
	string m_wall;
	string m_window;
};

//工程队的抽象类
class Builder
{
public:
	virtual void buildDoor() = 0;
	virtual void buildWall() = 0;
	virtual void buildWindow() = 0;
	virtual House* getHouse() = 0;
};

//负责建造公寓的工程队
class FlatBuilder : public Builder
{
public:
	FlatBuilder() { m_pHouse = new House; }

	virtual void buildWindow()
	{
		m_pHouse->setWindow("FlatWindow");
	}
	virtual void buildWall()
	{
		m_pHouse->setWall("FlatWadll");
	}
	virtual void buildDoor()
	{
		m_pHouse->setDoor("FlatDoor");
	}
	virtual House* getHouse()
	{
		return m_pHouse;
	}

private:
	House *m_pHouse;
};

//负责建造别墅的工程队
class VillaBuilder : public Builder
{
public:
	VillaBuilder() { m_pHouse = new House; }

	virtual void buildWindow()
	{
		m_pHouse->setWindow("VillaWindow");
	}
	virtual void buildWall()
	{
		m_pHouse->setWall("VillaWadll");
	}
	virtual void buildDoor()
	{
		m_pHouse->setDoor("VillaDoor");
	}
	virtual House* getHouse()
	{
		return m_pHouse;
	}

private:
	House *m_pHouse;
};

//设计师（指挥者） 负责建造逻辑
//指挥建筑队干具体的活
class Director
{
public:
	Director(Builder *build)
	{
		m_pBuild = build;
	}
	void construct()
	{
		m_pBuild->buildWall();
		m_pBuild->buildWindow();
		m_pBuild->buildDoor();
	}

private:
	Builder *m_pBuild;
};

int main()
{
	Builder *builder = NULL;
	Director *dre = NULL;
	House *house = NULL;

	builder = new VillaBuilder();
	dre = new Director(builder);
	dre->construct();
	house = builder->getHouse();

	cout << (house->getWindow()).c_str() << endl;

	delete house;
	delete builder;
	delete dre;


	builder = new FlatBuilder();
	dre = new Director(builder);
	dre->construct();
	house = builder->getHouse();

	cout << (house->getWindow()).c_str() << endl;

	delete house;
	delete builder;
	delete dre;
	house = NULL;
	builder = NULL;
	dre = NULL;

	return 0;
}
