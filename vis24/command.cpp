#include<iostream>
#include<vector>
#include<cmath>
#include<map>
#include<set>

using namespace std;

class TextBuffer {
private:
	vector<string> _text;
	pair<int,int> _pos;
public:
	void AddLine(int index, string text)
	{
		auto it = _text.begin();
		_text.insert(it+index, text);
	}
	void DelLine(int index)
	{
		auto it = _text.begin();
		_text.erase(it + index);
	}
	string GetLine(int i)
	{
		return _text[i];
	}
	void SetLine(int i, string text)
	{
		_text[i] = text;
	}
	void SetPosition(pair<int,int> pos)
	{
		_pos = pos;
	}
	pair<int,int> CurrentPosition()
	{
		return _pos;
	}
	int Size()
	{
		return _text.size();
	}
};

class EditorCommand {
protected:
	TextBuffer* textbuf; 
public:
	EditorCommand(TextBuffer* text)
	{
		textbuf = text;
	}
	virtual void redo() = 0;
	virtual void undo() = 0;

};

class DeleteTextCommand : public EditorCommand {
private:
	pair<int, int> position;
	string old;
public:
	DeleteTextCommand(TextBuffer* text, pair<int,int> pos):EditorCommand(text) 
	{
		position = pos;
	}
	void redo() override
	{
		auto cur = textbuf->GetLine(position.first);
		old = cur;
		cur.erase(position.second,1);
		textbuf->SetLine(position.first, cur);
	}
	void undo() override
	{
		textbuf->SetLine(position.first, old);
	}
};

class SearchAndReplaceCommand : public EditorCommand {
private:
	string _replace;
	map<int, string> _old;
public:
	SearchAndReplaceCommand(TextBuffer* text, string st):EditorCommand(text) 
	{
		_replace = st;
	}
	void redo() override
	{
		for (int i = 0; i < textbuf->Size(); i++)
		{
			auto cur = textbuf->GetLine(i);
			auto old = cur;
			//replace in cur
			textbuf->SetLine(i, cur);
			_old[i] = old;
		}
	}
	void undo() override
	{
		for (auto it = _old.begin(); it != _old.end(); it++)
		{
			textbuf->SetLine(it->first, it->second);
		}
	}
};

class InsertLineCommand : public EditorCommand {
private:
	int _pos;
	string _itext;
public:
	InsertLineCommand(TextBuffer* text, int pos, string itext) :EditorCommand(text) 
	{
		_itext = itext;
		_pos = pos;
	}
	void redo() override
	{
		textbuf->AddLine(_pos, _itext);
		_pos++;
	}
	void undo() override
	{
		textbuf->DelLine(_pos);
	}
};

class Editor {

public:
	void onCtrlCPressed()
	{
		
	}

	void onCtrlVPressed() {
		addAndExecuteCommand(new InsertLineCommand(text, text->CurrentPosition().first, ClipBoard));
	}
	void addAndExecuteCommand(EditorCommand* cmd) {
		commands.push_back(cmd);
		cmd->redo();
	}
	void undo() {
		if (commands.empty()) return;
		auto cmd = commands.back();
		cmd->undo();
		delete cmd;
		commands.pop_back();
	}
private:
	vector<EditorCommand*> commands;
	string ClipBoard;
	TextBuffer* text;
};

int main()
{
	Editor* editor = new Editor();
	editor->onCtrlVPressed();
	editor->undo();
	return 0;
}