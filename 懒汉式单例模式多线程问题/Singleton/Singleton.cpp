// Singleton.cpp : 定义控制台应用程序的入口点。
//

/*懒汉式单例模式多线程问题抛出*/
/*多线程下懒汉式不能保证是单例模式, 但是可以通过临界区等方法解决保证其在多线程下是单例的*/
#include "stdafx.h"
#include <process.h>
#include "afxmt.h"
#include "winbase.h"

#include <iostream>
using namespace std;

static CCriticalSection cs;

//懒汉式单例
class Singleton
{
private:
	Singleton()
	{
		cout << "Singleton constructor called!\n";
	}
	~Singleton()
	{
		cout << "Singleton deconstructor called!\n";
	}

public:
	static Singleton* getInstance()		//获取实例
	{
		if (m_psl == NULL)
		{
			cs.Lock();
			if (m_psl == NULL)
				m_psl = new Singleton();
			cs.Unlock();
		}

		return m_psl;
	}

	static void freeInstance()		//释放实例
	{
		if (m_psl != NULL)
		{
			delete m_psl;
			m_psl = NULL;
		}
	}

	void print()
	{
		cout << "Singleton test!\n";
	}

private:
	static Singleton *m_psl;
};

Singleton* Singleton::m_psl = NULL;

void MyThreadFunc(void *)
{
	Singleton::getInstance()->print();
}

int _tmain(int argc, _TCHAR* argv[])
{
	HANDLE thread[10];

	for (int i = 0; i < 3; i++)
	{
		thread[i] = (HANDLE)_beginthread(MyThreadFunc, 0, NULL);
		if (thread[i] == NULL)
			cout << "线程" << i << "创建失败" << endl;
	}

	//挂起主线程,让出cpu,等待所有的子线程都执行完毕后再继续执行
	for (int i = 0; i < 3; i++)
	{
		WaitForSingleObject(thread[i], INFINITE);  //第二个参数为等待时间
	}

	Singleton::freeInstance();

	return 0;
}

