#include <iostream>

using namespace std;

class ConsolePrinter
{
public:
    void Print(string text)
    {
        cout << text << endl;
    }
};


class Book
{
public:
    string Text;
    ConsolePrinter Printer;

    void Print()
    {
        Printer.Print(Text);
    }
};


class IPrinter
{
public:
    virtual void Print(string text) = 0;
};

class ConsolePrinterD : public IPrinter
{
public:
    void Print(string text) override
    {
        cout << "Console" << endl;
        cout << text << endl;
    }
};

class HtmlPrinterD : public IPrinter
{
public:
    void Print(string text) override
    {
        cout << "Html" << endl;
        cout << text << endl;
    }
};



class BookD
{
public:
    string Text;
    IPrinter* Printer;

    void SetPrinter(IPrinter* printer)
    {
        Printer = printer;
    }

    void Print()
    {
        Printer->Print(Text);
    }
};

int main()
{
    BookD* book = new BookD();
    book->SetPrinter(new ConsolePrinterD());
    book->Text = "Text Book";
    book->Print();
    book->SetPrinter(new HtmlPrinterD());
    book->Print();
}