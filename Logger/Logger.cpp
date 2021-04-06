#include<iostream>
#include<algorithm>
#include <sstream>  
#include <string>
#include<vector>
#include<queue>
#include<map>

using namespace std;

class Logger 
{
private:
    ostream* _out;
    string _name;

public:
    Logger(ostream* outs, string name)
    {
        _out = outs;
        _name = name;
    }

    void Info()
    {
        (*_out) << _name << endl;
    }

    template<typename... T>
    void Error(string header, int errcode,T... args)
    {
        (*_out) << "Error" << endl;
        (*_out) << header << endl;
        (*_out) << "Error code: " << errcode << endl;
        cout << args <<endl;
    }

    template<typename... T>
    void Notification(string header, T... args)
    {
        (*_out) << "Notification" << endl;
        (*_out) << header << endl;
        for(auto x:args)
           (*_out) << x;
        cout << endl;
    }

    template<typename T>
    void Warning(string header, T message)
    {
        (*_out) << "Warning" << endl;
        (*_out) << header << endl;
        (*_out) << message << endl;
    }
};

class Singleton
{
public:
    static Singleton* instance(ostream* outs = &cout, string name = "Logger") {
        static Singleton inst(outs, name);
        return &inst;
    }
    Logger* getLogger()
    {
        return _logger;
    }
private:
    Logger* _logger = NULL;
    Singleton(ostream* outs, string name) 
    {
        _logger = new Logger(outs, name);
    }
};

bool IsPrime(int number, Logger* logger = Singleton::instance()->getLogger())
{
    int i = 2;
    int cnt = 0;
    while (i * i <= number && cnt == 0)
    {
        if (number % i == 0)
            cnt++;
        i++;
        logger->Notification("Current state", (cnt == 0 ? "True" : "False", i));
    }
    return cnt == 0;
}

int main()
{
    bool res = IsPrime(1001);
    return 0;
}
