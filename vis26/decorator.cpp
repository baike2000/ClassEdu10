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
    ItalianPizza() : Pizza("Итальянская пицца") { }
    int GetCost() override
    {
        return 10;
    }
};

class BulgerianPizza : public Pizza
{
public:
    BulgerianPizza() : Pizza("Болгарская пицца") { }
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
    TomatoPizza(Pizza* p) : PizzaDecorator(p->GetName() + ", с томатами", p)
    { }

    int GetCost() override
    {
        return _pizza->GetCost() + 3;
    }
};

class CheesePizza : public PizzaDecorator
{
public:
    CheesePizza(Pizza* p) : PizzaDecorator(p->GetName() + ", с сыром", p)
    { }

    int GetCost() override
    {
        return _pizza->GetCost() + 5;
    }
};

int main()
{
    Pizza* pizza1 = new ItalianPizza();
    pizza1 = new TomatoPizza(pizza1); // итальянская пицца с томатами
    cout << "Название: "<<  pizza1->GetName() << endl;
    cout << "Цена: " << pizza1->GetCost() << endl;;

    Pizza* pizza2 = new ItalianPizza();
    pizza2 = new CheesePizza(pizza2);// итальянская пиццы с сыром
    cout << "Название: " << pizza2->GetName() << endl;
    cout << "Цена: " << pizza2->GetCost() << endl;

    Pizza* pizza3 = new BulgerianPizza();
    pizza3 = new TomatoPizza(pizza3);
    pizza3 = new CheesePizza(pizza3);// болгарская пиццы с томатами и сыром
    cout << "Название: " << pizza3->GetName() << endl;
    cout << "Цена: " << pizza3->GetCost() << endl;

    return 0;
}
