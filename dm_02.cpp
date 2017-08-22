#include <iostream>
#include <stdlib.h>
using namespace std;

class BankWorker
{
public:
	void save()
	{
		cout << "save" << endl;
	}

	void transfer()
	{
		cout << "transfer" << endl;
	}

	void fee()
	{
		cout << "fee" << endl;
	}
};

//抽象实现
class AbBankWorker
{
public:
	virtual void dothing() = 0;
};

class SaveBanker : public AbBankWorker
{
public:
	virtual void dothing()
	{
		cout << "save" << endl;
	}
};

class transferBanker : public AbBankWorker
{
public:
	virtual void dothing()
	{
		cout << "transfer" << endl;
	}
};

void test1()
{
	BankWorker *bw = new BankWorker();
	bw->save();
	bw->transfer();
	bw->fee();

	delete bw;
}

void test2()
{
	AbBankWorker *bw = NULL;

	bw = new SaveBanker();
	bw->dothing();
	delete bw;
	
	bw = new transferBanker();
	bw->dothing();
	delete bw;
}

void howdo(AbBankWorker *bw)
{
	bw->dothing();
}
void test3()
{
	AbBankWorker *bw = NULL;

	bw = new SaveBanker();
	howdo(bw);
	delete bw;

	bw = new transferBanker();
	howdo();
	delete bw;
}


int main()
{
	//test1();
	//test2();

	test3();

	system("pause");
	return 0;
}