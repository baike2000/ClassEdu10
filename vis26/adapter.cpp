#include<iostream>

using namespace std;

class ITransport
{
public:
    virtual void Drive() = 0;
};

// класс машины
class Auto : public ITransport
{
public:
    void Drive() override
    {
        cout << "Машина едет по дороге" << endl;
    }
};

class Driver
{
public:
    void Travel(ITransport* transport)
    {
        transport->Drive();
    }
};
// интерфейс животного
class IAnimal
{
public:
    virtual void Move() = 0;
};
// класс верблюда
class Camel : public IAnimal
{
public:
    void Move() override
    {
        cout << "Верблюд идет по пескам пустыни" << endl;
    }
};
// Адаптер от Camel к ITransport
class CamelToTransportAdapter : public ITransport
{
private:
    Camel* camel;
public:
    CamelToTransportAdapter(Camel* c)
    {
        camel = c;
    }

    void Drive() override
    {
        camel->Move();
    }
};

int main()
{
    // путешественник
    Driver* driver = new Driver();
    // машина
    Auto* at = new Auto();
    // отправляемся в путешествие
    driver->Travel(at);
    // встретились пески, надо использовать верблюда
    Camel* camel = new Camel();
    // используем адаптер
    ITransport* camelTransport = new CamelToTransportAdapter(camel);
    // продолжаем путь по пескам пустыни
    driver->Travel(camelTransport);

    return 0;
}
