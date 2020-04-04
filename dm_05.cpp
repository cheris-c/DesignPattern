#include <iostream>
using namespace std;

//饿汉式单例
class Singleton
{
private:
	Singleton()
	{
		cout << "Singleton constructor called!" << endl;
	}

public:
	static Singleton* getInstance()
	{
		return m_psl;
	}

	static void freeInstance()
	{
		if (m_psl != NULL)
		{
			delete m_psl;
			m_psl = NULL;
		}
	}

private:
	static Singleton *m_psl;
};

Singleton* Singleton::m_psl = new Singleton();

int main()
{
	Singleton *p1 = Singleton::getInstance();
	Singleton *p2 = Singleton::getInstance();

	if (p1 == p1)
		cout << "They are same!" << endl;
	else
		cout << "They are't similiar!" << endl;

	Singleton::freeInstance();
	return 0;
}