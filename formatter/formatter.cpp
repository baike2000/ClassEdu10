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
        _streamreader->getline(_line, 100000, '\n');
        return (!_streamreader->eof());
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
                curwidth += w.size();
                _result += w + " ";
            }
            else
            {
                curwidth = 0;
                _result.erase(_result.size() - 1, 1);
                _result += "\r\n";
            }
        }
    }
};

class RightJustifyFormatter : public ParagraphFormatter
{
public:
    void Format() override
    {

    }
};

class CenterJustifyFormatter : public ParagraphFormatter
{
public:
    void Format() override
    {

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
        vector<string> lines;
        TextFileParse<string>* parser = new TextFileParse<string>(_in);
        while (parser->HasNextLine())
        {
            _pf->AddLine(parser->NextLine(), _width);
            lines.push_back(_pf->GetFormattedLine() + "\r\n");
        }
        for (auto l : lines)
        {
            _out->write(l.c_str(), l.size());
        }
    }
};

int main()
{
    TextFromatter* tf = new TextFromatter(new LeftJustifyFormatter(), (&cin), (&cout), 80);
    tf->Format();
    return 0;
}

