#include<iostream>

using namespace std;

class Pizza
{
protected:
    string Name;
public:
    Pizza(string n)
    {
        Name = n;
    }
    string GetName()
    {
        return Name;
    }
    virtual int GetCost() = 0;
};

class ItalianPizza : public Pizza
{
public:
    ItalianPizza() : Pizza("����������� �����") { }
    int GetCost() override
    {
        return 10;
    }
};

class BulgerianPizza : public Pizza
{
public:
    BulgerianPizza() : Pizza("���������� �����") { }
    int GetCost() override
    {
        return 8;
    }
};

class PizzaDecorator : public Pizza
{
protected:
    Pizza* _pizza;
public:
    PizzaDecorator(string n, Pizza* pizza) : Pizza(n)
    {
        _pizza = pizza;
    }
};

class TomatoPizza : public PizzaDecorator
{
public:
    TomatoPizza(Pizza* p) : PizzaDecorator(p->GetName() + ", � ��������", p)
    { }

    int GetCost() override
    {
        return _pizza->GetCost() + 3;
    }
};

class CheesePizza : public PizzaDecorator
{
public:
    CheesePizza(Pizza* p) : PizzaDecorator(p->GetName() + ", � �����", p)
    { }

    int GetCost() override
    {
        return _pizza->GetCost() + 5;
    }
};

int main()
{
    Pizza* pizza1 = new ItalianPizza();
    pizza1 = new TomatoPizza(pizza1); // ����������� ����� � ��������
    cout << "��������: "<<  pizza1->GetName() << endl;
    cout << "����: " << pizza1->GetCost() << endl;;

    Pizza* pizza2 = new ItalianPizza();
    pizza2 = new CheesePizza(pizza2);// ����������� ����� � �����
    cout << "��������: " << pizza2->GetName() << endl;
    cout << "����: " << pizza2->GetCost() << endl;

    Pizza* pizza3 = new BulgerianPizza();
    pizza3 = new TomatoPizza(pizza3);
    pizza3 = new CheesePizza(pizza3);// ���������� ����� � �������� � �����
    cout << "��������: " << pizza3->GetName() << endl;
    cout << "����: " << pizza3->GetCost() << endl;

    return 0;
}
