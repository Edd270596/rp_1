#include <iostream>
#include <vector>
#include <Windows.h>
#include <locale>;
using namespace std;
class Observer
{
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

        cout << "Время: " << hour << ":00!" << endl;

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
        cout << "  Пекарь: росжигает печь." << endl;
    }
    void kneadTheDough()
    {
        cout << "  Пекарь: замешивает тесто." << endl;
    }
    void bake()
    {
        cout << "  Пекарь: ставит тесто выпекатся." << endl;
    }
    void takeBaking()
    {
        cout << "  Пекарь: вытягивает выпечку с печи." << endl;
    }
    void open()
    {
        cout << "  Пекарь: открывает пекарню для продажи выпечки." << endl;
    }

    void close()
    {
        cout << "  Пекарь: Закрывает пекарню!" << endl;
    }
};
class Cobbler : public Craftsman
{
public:
    void open()
    {
        cout << "  Сапожник: Открывает мастерскую." << endl;
    }
    void drink()
    {
        cout << "  Сапожник: выпивает бакал пива." << endl;
    }
    void sing()
    {
        cout << "  Сапожник: начинает петь песню." << endl;
    }
    void close()
    {
        cout << "  Сапожник: закрывает мастерскую, и идёт в пивную!" << endl;
    }
};
class Innkeeper : public Craftsman
{
public:
    void makeBeer()
    {
        cout << "  Бармен: Варит пиво." << endl;
    }

    void open()
    {
        cout << "  Бармен: открывает пивную!" << endl;
    }

    void close()
    {
        cout << "  Бармен: закрывает пивную!" << endl;
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

