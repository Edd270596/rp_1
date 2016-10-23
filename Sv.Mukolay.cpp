#include <iostream>
#include <cmath>
#include <time.h>
#include <vector>
#include <string>
#include <algorithm>
#include <Windows.h>
using namespace std;
class EatablePresent
{
	string name;
public:
	EatablePresent(){};
	virtual string getName()=0;
};
class UneatablePresent
{
	string name;
public:
	UneatablePresent(){};
	virtual string getName()=0;
};
class Sweets : public EatablePresent
{
	string getName()
	{
		return "�������";
	}	
};
class BitterPills : public EatablePresent
{
	string getName()
	{
		return "������� ��������";
	}	
};
class Toys:public UneatablePresent
{
	string getName()
	{
		return "�������";
	}
};
class Rod:public UneatablePresent
{
	string getName()
	{
		return "�����";
	}
};
class Child
{
	string name;
	int good;
	int bad;
public:
	Child(string n)
	{
		name = n;
		good = rand() % 100;
		bad = rand() % 100;
	}
	int getGood()
	{
		return good;
	}
	int getBad()
	{
		return bad;
	}
	void getEatablePresent(EatablePresent* P)
	{
		cout << name << " ������� " << P->getName() << "." << endl;
	}
	void getUneatablePresent(UneatablePresent* P)
	{
		cout << name << " ������� " << P->getName() << "." << endl;
	}
	string getName()
	{
		return name;
	}
	void setNewYear()
	{
		good = rand() % 100;
		bad = rand() % 100;
	}
};
class Factory
{
public:
	virtual UneatablePresent* makeUneatablePresent() = 0;
	virtual EatablePresent* makeEatablePresent() = 0;
};
class GoodFactory : public Factory
{
public:
	GoodFactory(){};
	Sweets* makeEatablePresent()
	{
		Sweets* s = new Sweets();
		return s;
	}
	Toys* makeUneatablePresent()
	{
		Toys* t = new Toys();
		return t;
	}
};
class BadFactory : public Factory
{
public:
	BadFactory(){};
	BitterPills* makeEatablePresent()
	{
		BitterPills* s = new BitterPills();
		return s;
	}
	Rod* makeUneatablePresent()
	{
		Rod* t = new Rod();
		return t;
	}
};
class Mickle
{
	static Mickle* inst;
protected:
	Mickle(){};
	vector <Child*> ChildList;
	vector <Factory*> FactoryList;
public:
	void getMessage(Child* CH)
	{
		if (CH->getGood() > CH->getBad())
		{
			cout << "��������� " << CH->getName() << " ������ " << CH->getGood() << " ������ ��� � " << CH->getBad() << " ������. �� ������� �������." << endl;
			ChildList.push_back(CH);
			Factory* F = new GoodFactory();
			FactoryList.push_back(F);
		}
		else
		{
			cout << "��������� " << CH->getName() << " ������ " << CH->getGood() << " ������ ��� � " << CH->getBad() << " ������. �� ������ �������." << endl;
			ChildList.push_back(CH);
			Factory* F = new BadFactory();
			FactoryList.push_back(F);
		}
	}
	void sendPresents()
	{
		for (int i = 0; i<ChildList.size(); i++)
		{
			ChildList[i]->getEatablePresent(FactoryList[i]->makeEatablePresent());
			ChildList[i]->getUneatablePresent(FactoryList[i]->makeUneatablePresent());
		}
		ChildList.clear();
		FactoryList.clear();
	}
	static Mickle* getInstance()
	{
		if (!inst)
			inst = new Mickle();
		return inst;
	}
};
Mickle* Mickle::inst = 0;
int main()
{
	setlocale(LC_ALL, "Russian");
	srand(time(NULL));
	Child* arr[5];
	arr[0] = new Child("������");
	arr[1] = new Child("�����");
	arr[2] = new Child("�����");
	arr[3] = new Child("�����");
	arr[4] = new Child("����");
	while (true)
	{
		for (int i = 0; i<5; i++)
		{
		Mickle::getInstance()->getMessage(arr[i]);
		Mickle::getInstance()->sendPresents();
		cout<<endl;
		}

		for (int i = 0; i<5; i++)
		arr[i]->setNewYear();
		cout << endl << endl;
		Sleep(20000);
	}
}

