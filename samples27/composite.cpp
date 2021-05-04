#include<iostream>
#include<vector>

using namespace std;


class Component
{
protected:
    string _name;

public:
    Component(string name)
    {
        _name = name;
    }

    virtual void Add(Component* component) = 0;

    virtual void Remove(Component* component) = 0;

    virtual void Print()
    {
        cout << _name << endl;
    }
};
class Directory :public Component
{
private:
    vector<Component*> components;

public: Directory(string name)
    : Component(name)
{
}

      void Add(Component* component) override
      {
          components.push_back(component);
      }

      void Remove(Component* component) override
      {
          // auto it = find(components.begin(),components)
          // components.erase(component);
      }

      void Print() override
      {
          cout << "Node " << _name << endl;
          cout << "Nodes:" << endl;
          for (int i = 0; i < components.size(); i++)
          {
              components[i]->Print();
          }
      }
};

class File : public Component
{
private:
    vector<Component*> components;
public: 
    File(string name)
        : Component(name)
    {}

    void Add(Component* component) override
    {
        components.push_back(component);
    }

    void Remove(Component* component) override
    {
        // auto it = find(components.begin(),components)
        // components.erase(component);
    }
};

class NullObject : public Component
{
public:
    NullObject():Component("NULL")
    {
    }

    void Add(Component* component) {};

    void Remove(Component* component) {};

};

int main()
{
    Component* file = new NullObject();
    file->Print();
    Component* fileSystem = new Directory("File system");
    // ���������� ����� ����
    Component* diskC = new Directory("Disk C");
    // ����� �����
    Component* pngFile = new File("12345.png");
    Component* docxFile = new File("Document.docx");
    // ��������� ����� �� ���� �
    diskC->Add(pngFile);
    diskC->Add(docxFile);
    // ��������� ���� � � �������� �������
    fileSystem->Add(diskC);
    // ������� ��� ������
    fileSystem->Print();
    cout << endl;
    // ������� � ����� � ����
    diskC->Remove(pngFile);
    // ������� ����� �����
    Component* docsFolder = new Directory("My documents");
    // ��������� � ��� �����
    Component* txtFile = new File("readme.txt");
    Component* csFile = new File("Program.cs");
    docsFolder->Add(txtFile);
    docsFolder->Add(csFile);
    diskC->Add(docsFolder);

    fileSystem->Print();

    return 0;
}
