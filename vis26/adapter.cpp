#include<iostream>

using namespace std;

class ITransport
{
public:
    virtual void Drive() = 0;
};

// ����� ������
class Auto : public ITransport
{
public:
    void Drive() override
    {
        cout << "������ ���� �� ������" << endl;
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
// ��������� ���������
class IAnimal
{
public:
    virtual void Move() = 0;
};
// ����� ��������
class Camel : public IAnimal
{
public:
    void Move() override
    {
        cout << "������� ���� �� ������ �������" << endl;
    }
};
// ������� �� Camel � ITransport
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
    // ��������������
    Driver* driver = new Driver();
    // ������
    Auto* at = new Auto();
    // ������������ � �����������
    driver->Travel(at);
    // ����������� �����, ���� ������������ ��������
    Camel* camel = new Camel();
    // ���������� �������
    ITransport* camelTransport = new CamelToTransportAdapter(camel);
    // ���������� ���� �� ������ �������
    driver->Travel(camelTransport);

    return 0;
}
