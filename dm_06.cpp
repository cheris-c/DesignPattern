/*使用C++11改进单例模式*/
#include <iostream>
#include <string>
using namespace std;

template<class T>
class Singleton
{
public:
	template<typename... Args>
	static T* GetInstance(Args&&... args)
	{
		if (NULL == m_pInstance)
			m_pInstance = new T(forward<Args>(args)...);//完美转发

		return m_pInstance;
	}

	static void ReleaseInstance()
	{
		delete m_pInstance;
		m_pInstance = NULL;
	}

private:
	Singleton(void);
	virtual ~Singleton(void);
	Singleton(const Singleton &);
	Singleton& operator=(const Singleton &);

private:
	static T* m_pInstance;
};

template<class T> T* Singleton<T>::m_pInstance = nullptr;

struct A
{
	A(const string &) { cout << "lValue" << endl; }
	A(string &&x) { cout << "rValue" << endl; }
};

struct B
{
	B(const string &){ cout << "lValue" << endl; }
	B(string &&x){ cout << "rValue" << endl; }
};

struct C
{
public:
	C(int x, double y) {m_a = x; m_b = y;}

	void get() const {cout << m_a << "  " << m_b << endl;}

private:
	int m_a;
	int m_b;
};

int main()
{
	string str = "bb";

	//创建A的单例
	Singleton<A>::GetInstance(str);

	//创建B的单例,临时变量str被move之后变成右值， 然后可以根据移动语义来避免复制
	Singleton<B>::GetInstance(move(str));

	//创建C的单例，含两个参数
	Singleton<C>::GetInstance(1, 3.14)->get();

	Singleton<A>::ReleaseInstance();
	Singleton<B>::ReleaseInstance();
	Singleton<C>::ReleaseInstance();

	system("pause");
	return 0;
}