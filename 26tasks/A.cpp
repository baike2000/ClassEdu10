#include<iostream>
#include<string>
#include<algorithm>

using namespace std;

class Number
{
protected:
    int _base = 0;
    int _number[100001] = { 0 };
    int _size = 0;
public:
    virtual void Print() = 0;
    int Get(int i)
    {
        return _number[i];
    }
    void Set(int i, int v)
    {
        _number[i] = v;
    }
    int Size()
    {
        return _size;
    }
    void SetSize(int size)
    {
        _size = size;
    }
    int Base()
    {
        return _base;
    }
};

class BinaryNumber : public Number
{
public: 
    BinaryNumber(string number)
    {
        _base = 2;
        for (int i = 0; i < number.size(); i++)
        {
            _number[i] = (int)(number[i] - '0');
        }
        _size = number.size();
    }
    void Print() override
    {
        for (int i = 0; i < _size; i++)
        {
            cout << _number[i];
        }
        cout << endl;
    }
};

class DecNumber : public Number
{
private:
    void print0(int n)
    {
        int k = _base / 10;
        while (n / k == 0)
        {
            cout << "0";
            k /= 10;
        }
    }
public:
    DecNumber(string number)
    {
        _base = 1000000000;
        int j = number.size() / 9;
        int k = 1;
        for (int i = 0; i < number.size(); i++)
        {
            if (i % 9 == 0)
            {
                j++;
                k = 1;
            }
            _number[j] += (int)(number[i] - '0') * k;
            k *= 10;
        }
        _size = number.size()/9;
    }
    void Print() override
    {
        bool fl = true;
        for (int i = _size; i >= 0; i--)
        {
            if (_number[i] > 0 && fl)
            {
                fl = false;
                cout << _number[i];
                continue;
            }
            if (!fl)
            {
                if (_number[i] < _base / 10) 
                    print0(_number[i]);
                cout << _number[i];
            }
        }
    }
};


class ConverterToDec
{
private:
    Number* _result;
    Number* _from;
    Number* _temp;
    void sum2(int b, int& k, int& ks)
    {
        int c = 0;
        int c1 = 0;
        ks = max(ks, k);
        if (b > 0)
        {
            for (int i = 0; i < ks; i++)
            {
                c1 = _result->Get(i) + _temp->Get(i) + c1;
                if (c1 > _result->Base())
                {
                    _result->Set(i, c1 % _result->Base());
                    c1 = c1 / _result->Base();
                }
                else
                {
                    _result->Set(i, c1);
                    c1 = 0;
                }
            }
            if (c1 > 0)
            {
                ks++;
                _result->Set(ks - 1, c1);
            }
        }
        for (int i = 0; i < k; i++)
        {
            c = _temp->Get(i) + _temp->Get(i) + c;
            if (c > _result->Base())
            {
                _temp->Set(i, c % _result->Base());
                c = c / _result->Base();
            }
            else
            {
                _temp->Set(i, c);
                c = 0;
            }
        }
        if (c > 0)
        {
            k++;
            _temp->Set(k - 1, c);
        }
    }    
    void converter()
    {
        _temp->Set(0, 1);
        int k = 1, ks = 1;
        int ln = _from->Size();
        for (int i = ln - 1; i >= 0; i--)
        {
            if (_temp->Get(i) == 0)
                sum2(0, k, ks);
            else
                sum2(1, k, ks);
        }
        _result->SetSize(k);
    }
public:
    ConverterToDec(Number* numberFrom)
    {
        _from = numberFrom;
        _temp = new DecNumber("0");
        _result = new DecNumber("0");
        converter();
    }
    Number* GetNumber()
    {
        return _result;
    }
};
int main()
{
    string s;
    cin >> s;
    BinaryNumber* bin = new BinaryNumber(s);
    ConverterToDec* conv = new ConverterToDec(bin);
    conv->GetNumber()->Print();
    return 0;
}
