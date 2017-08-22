#include <iostream>
using namespace std;

//让Computer框架 和 具体的厂商进行 解耦合
class HardDisk
{
public:
	virtual void work() = 0;
};

class Memory
{
public:
	virtual void work() = 0;
};

class Cpu
{
public:
	virtual void work() = 0;
};

class Computer
{
public:
	Computer(HardDisk *hardDisk, Memory *mem, Cpu *cpu)
	{
		m_pHardDisk = hardDisk;
		m_pMemory = mem;
		m_pCpu = cpu;
	}

public:
	void work()
	{
		m_pHardDisk->work();
		m_pMemory->work();
		m_pCpu->work();
	}

private:
	HardDisk *m_pHardDisk;
	Memory *m_pMemory;
	Cpu *m_pCpu;
};

class InterCpu : public Cpu
{
public:
	virtual void work()
	{
		cout << "Inter Cpu" << endl;
	}
};

class XSDisk : public HardDisk
{
public:
	virtual void work()
	{
		cout << "XS HardDisk" << endl;
	}
};

class JSDMem : public Memory
{
public:
	virtual void work()
	{
		cout << "JSD Memory" << endl;
	}
};

int main()
{
	HardDisk *hardDisk = NULL;
	Memory *mem = NULL;
	Cpu *cpu = NULL;

	hardDisk = new XSDisk;
	mem = new JSDMem;
	cpu = new InterCpu;

	Computer *comp = new Computer(hardDisk, mem, cpu);
	comp->work();

	delete hardDisk;
	delete mem;
	delete cpu;
	delete comp;

	return 0;
}