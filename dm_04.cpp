#include <iostream>
using namespace std;

/*单例模式实现要点：将构造函数私有化，通过内部成员构造，利用内部函数作为接口
供外部访问*/
//懒汉式单例
class Singleton
{
private:	Singleton()

	{
		cout << "Singleton constructor called!" << endl;
	}

public:
	static Singleton* getInstance()
	{
		if (m_psl == NULL)
			m_psl = new Singleton();
		
		//上面代码多线程下会有问题，一般加锁再加二次判断
		/*
		if (m_psl == NULL) 
		{
			lock();
			if (m_psl == NULL)
				m_psl = new Singleton();
			unlock();
		}*/

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

	void print()
	{
		cout << "Singleton test!" << endl;
	}

private:
	static Singleton *m_psl;
};

Singleton* Singleton::m_psl = NULL;

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
int add(int a, int b) {
	if (a > b)
	{
		a = a - b;
	}
	return a;
}