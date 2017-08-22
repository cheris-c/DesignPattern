#include <iostream>
using namespace std;

class Pro
{
public:
	virtual Pro* clone() = 0;
	virtual void print() = 0;
};

class CPlusPlusPro : public Pro
{	
public:
	CPlusPlusPro(string name, string job) 
	{
		m_job = job;
		m_name = name;
	}
	//在设计拷贝函数时，要特别注意深拷贝和浅拷贝
	CPlusPlusPro(CPlusPlusPro &cpp)
	{
		m_name = cpp.m_name;
		m_job = cpp.m_job;
	}

	virtual void print() 
	{
		cout << m_name << " : " << m_job << endl;
	}

	virtual Pro* clone()
	{
		return new CPlusPlusPro(*this);
	}

public:
	string m_name;
	string m_job;
};

int main()
{
	CPlusPlusPro *tmp = new CPlusPlusPro("tom", "engineer");
	tmp->print();

	Pro *cpp = tmp->clone();
	cpp->print();

	delete cpp;
	delete tmp;
	return 0;
}