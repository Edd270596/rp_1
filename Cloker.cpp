#include <iostream>
#include <vector>
#include <Windows.h>
#include <locale>;
using namespace std;
class Observer
{fdfdfdf
public:
    virtual void update(int a){};
};

class Clock
{
    static Clock *inst;
protected:
    vector <Observer*> Obs;
    int hour;
    Clock()
    {
        hour = 0;
    }
public:
    void attachObserver(Observer* a)
    {
        Obs.push_back(a);
    }
    void incHour()
    {
        if (hour != 23)
            hour++;
        else
            hour = 0;

        cout << "�����: " << hour << ":00!" << endl;

        for (int i = 0; i<Obs.size(); i++)
        {
            Obs[i]->update(hour);
        }
    }

    static Clock* getInstance()
    {
        if (inst == 0)
            inst = new Clock();
        return inst;
    }
};
Clock* Clock::inst = 0;
class Craftsman
{
};
class Baker : public Craftsman
{
public:
    void fireOven()
    {
        cout << "  ������: ��������� ����." << endl;
    }
    void kneadTheDough()
    {
        cout << "  ������: ���������� �����." << endl;
    }
    void bake()
    {
        cout << "  ������: ������ ����� ���������." << endl;
    }
    void takeBaking()
    {
        cout << "  ������: ���������� ������� � ����." << endl;
    }
    void open()
    {
        cout << "  ������: ��������� ������� ��� ������� �������." << endl;
    }

    void close()
    {
        cout << "  ������: ��������� �������!" << endl;
    }
};
class Cobbler : public Craftsman
{
public:
    void open()
    {
        cout << "  ��������: ��������� ����������." << endl;
    }
    void drink()
    {
        cout << "  ��������: �������� ����� ����." << endl;
    }
    void sing()
    {
        cout << "  ��������: �������� ���� �����." << endl;
    }
    void close()
    {
        cout << "  ��������: ��������� ����������, � ��� � ������!" << endl;
    }
};
class Innkeeper : public Craftsman
{
public:
    void makeBeer()
    {
        cout << "  ������: ����� ����." << endl;
    }

    void open()
    {
        cout << "  ������: ��������� ������!" << endl;
    }

    void close()
    {
        cout << "  ������: ��������� ������!" << endl;
    }
};

class BakerObserver : public Observer
{
    Baker* b;
public:
    BakerObserver(Baker *BInst)
    {
        b = BInst;
    }

    void update(int h)
    {
        if (h == 4)
            b->fireOven();
        else if (h == 5)
            b->kneadTheDough();
        else if (h == 6)
            b->bake();
        else if (h == 7)
            b->takeBaking();
        else if (h == 8)
            b->open();
        else if (h == 16)
            b->close();
    }
};
class CobblerObserver : public Observer
{
    Cobbler* C;
public:
    CobblerObserver(Cobbler* CInst)
    {
        C = CInst;
    }
    void update(int h)
    {
        if (h == 10)
            C->open();
        else if (h == 11)
            C->drink();
        else if (h == 15)
            C->sing();
        else if (h == 18)
            C->close();
    }
};
class InnkeeperObserver : public Observer
{
    Innkeeper* I;
public:
    InnkeeperObserver(Innkeeper* IInst)
    {
        I = IInst;
    }
    void update(int h)
    {
        if (h == 16)
            I->makeBeer();
        else if (h == 17)
            I->open();
        else if (h == 23)
            I->close();
    }
};
class ClockIterator
{
public:
    void next()
    {
        Clock::getInstance()->incHour();
    }
};
int main()
{
    setlocale(LC_ALL, "Russian");
    Baker *Vasya = new Baker();
    Cobbler *Petya = new Cobbler();
    Innkeeper *Sasha = new Innkeeper();
    Observer* B = new BakerObserver(Vasya);
    Observer *C = new CobblerObserver(Petya);
    Observer *I = new InnkeeperObserver(Sasha);
    Clock::getInstance()->attachObserver(B);
    Clock::getInstance()->attachObserver(C);
    Clock::getInstance()->attachObserver(I);
    ClockIterator It;
    while (true)
    {
        It.next();
        Sleep(3600);
    }
}

