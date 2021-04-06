#include<iostream>
#include<algorithm>
#include <sstream>  
#include <string>
#include<vector>
#include<queue>
#include<map>

using namespace std;

template<class T>
class IParser
{
public:
    virtual bool HasNextLine() = 0;
    virtual vector<T> NextLine() = 0;
};

template<class T>
class TextFileParse : public IParser<T>
{
private:
    istream* _streamreader;
    char* _line;

public:
    TextFileParse(istream* streamreader)
    {
        _streamreader = streamreader;
        _line = new char[100000];
    }
    bool HasNextLine() override
    {
        _streamreader->getline(_line, 100000);
        return (!_streamreader->eof() || (strlen(_line) > 0));
    }

    vector<T> NextLine() override
    {
        string s(_line);
        istringstream si(s);
        vector<T> res;
        T cur;
        while (si >> cur)
            res.push_back(cur);
        return res;
    }

    ~TextFileParse()
    {
        _streamreader = NULL;
        _line = NULL;
    }
};

class ParagraphFormatter
{
protected:
    int _width = 0;
    vector<string> _words;
    string _result;
public:
    void AddLine(vector<string> words, int width)
    {
        _words = words;
        _width = width;
        Format();
    }
    string GetFormattedLine()
    {
        return _result;
    }
    virtual void Format() = 0;
};

class LeftJustifyFormatter :public ParagraphFormatter
{
public:
    void Format() override
    {
        _result = "";
        int curwidth = 0;
        for (auto w : _words)
        {
            if (curwidth + w.size() <= _width)
            {
                curwidth += w.size() +  1;
                _result += w + " ";
            }
            else
            {
                curwidth = 0;
                _result.erase(_result.size() - 1, 1);
                _result += "\n";
                curwidth += w.size() + 1;
                _result += w + " ";
            }
        }
        if (_result != "")
            _result.erase(_result.size() - 1, 1);
    }
};


class RightJustifyFormatter : public ParagraphFormatter
{
public:
    void Format() override
    {
        _result = "";
        int curwidth = 0;
        vector<string> res;
        for (auto w : _words)
        {
            if (curwidth + w.size() <= _width)
            {
                curwidth += w.size() + 1;
                _result += w + " ";
            }
            else
            {
                _result.erase(_result.size() - 1, 1);

                while (curwidth <= _width)
                {
                    _result = " " + _result;
                    curwidth++;
                }
                curwidth = 0;
                _result += "\n";
                res.push_back(_result);
                _result = "";
                curwidth += w.size() + 1;
                _result += w + " ";
            }
        }

        if (_result != "")
        {
            _result.erase(_result.size() - 1, 1);
            while (curwidth <= _width)
            {
                _result = " " + _result;
                curwidth++;
            }
            res.push_back(_result);
        }
        _result = "";
        for (auto l : res)
        {
            _result += l;
        }
    }
};

class CenterJustifyFormatter : public ParagraphFormatter
{
public:
    void Format() override
    {

    }
};

class WidthJustifyFormatter : public ParagraphFormatter
{
public:
    void Format() override
    {
        _result = "";
        int curwidth = 0;
        vector<string> res;
        for (auto w : _words)
        {
            if (curwidth + w.size() <= _width)
            {
                curwidth += w.size() + 1;
                _result += w + " ";
            }
            else
            {
                int p = 0;
                _result.erase(_result.size() - 1, 1);
                while (curwidth <= _width)
                {
                    int prev = p;
                    p = _result.find(' ', p);
                    if (p == -1)
                    {
                        if (prev == 0)
                            break;
                        p = 0;
                        continue;
                    }
                    _result.insert(p, 1, ' ');
                    while (_result[p] == ' ')
                    {
                        p++;
                    }
                    curwidth++;
                }
                curwidth = 0;
                _result += "\n";
                res.push_back(_result);
                _result = "";
                curwidth += w.size() + 1;
                _result += w + " ";
            }
        }
        if (_result != "")
        {
            int p = 0;
            _result.erase(_result.size() - 1, 1);
            while (curwidth <= _width)
            {
                int prev = p;
                p = _result.find(' ', p);
                if (p == -1)
                {
                    if (prev == 0)
                        break;
                    p = 0;
                    continue;
                }
                _result.insert(p, 1, ' ');
                while (_result[p] == ' ')
                {
                    p++;
                }
                curwidth++;
            }
            res.push_back(_result);
        }
        _result = "";
        for (auto l : res)
        {
            _result += l;
        }
    }
};


class TextFromatter
{
private:
    ParagraphFormatter* _pf;
    istream* _in;
    ostream* _out;
    int _width;
public:
    TextFromatter(ParagraphFormatter* pf, istream* ins, ostream* outs, int width)
    {
        _pf = pf;
        _in = ins;
        _out = outs;
        _width = width;
    }

    void Format()
    {
        vector<string> words;
        TextFileParse<string>* parser = new TextFileParse<string>(_in);
        while (parser->HasNextLine())
        {
            for (auto i : parser->NextLine())
            {
                words.push_back(i);
            }
        }
        _pf->AddLine(words, _width);
        _out->write(_pf->GetFormattedLine().c_str(), _pf->GetFormattedLine().size());
    }
};

int main()
{
    int n;
    char J;
    cin >> n >> J;
    ParagraphFormatter* pf = NULL;
    switch (J)
    {
    case 'L': pf = new LeftJustifyFormatter(); break;
    case 'R': pf = new RightJustifyFormatter(); break;
    case 'E': pf = new WidthJustifyFormatter(); break;
    }
    TextFromatter* tf = new TextFromatter(pf, (&cin), (&cout), n);
    tf->Format();
    return 0;
}

/*
*/