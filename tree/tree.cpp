#include<iostream>
#include<vector>
#include<queue>
#include<map>

using namespace std;

struct Point
{
	int x, y;
};

map<int, Point> direct =
{
	{0,{1,0}},
	{45,{1,-1}},
	{90,{0,-1}},
	{135,{-1,-1}},
	{180,{-1,0}},
	{225,{-1,1}},
	{270,{0,1}},
	{315,{1,1}}
};

const int c_initdir = 90;
const Point c_begin = { 320,480 };

class Node
{
private:
	int v_id = 0, v_direction = 90;
	Point v_begin, v_end;
	vector<int> getAllowDirection(int dir)
	{
		vector<int> v;
		if (dir == -1)
		{
			for (int i = 0; i < 3; i++)
				v.push_back(c_initdir);
			return v;
		}
		for (int i = dir - 45; i <= dir + 45; i += 45)
		{
			if (i < 0)
			{
				v.push_back(360 + i);
				continue;
			}
			if (i >= 360)
			{
				v.push_back(i % 360);
				continue;
			}
			v.push_back(i);
		}
	}
protected:
	int v_len = 0;
	bool v_stopped = false;
	Node* v_parent;
	vector<Node*> v_children;
	int v_speed = 0;
	int v_maxlen = 0;
public:
	Node(Node* parent)
	{
		int dir = -1;
		v_id = 1;
		v_begin = c_begin;
		v_len = 0;
		if (parent != NULL)
		{
			dir = parent->v_direction;
			v_id = parent->v_id + 1;
			v_begin = parent->v_end;
			v_end = v_begin;
			v_parent = parent;
		}
		v_direction = getAllowDirection(dir)[rand() % 3];
	}
	int GetLength()
	{
		return v_len;
	}
	int GetSpeed()
	{
		return v_speed;
	}
	int GetMaxLen()
	{
		return v_maxlen;
	}
	void IncLength()
	{
		if (v_len < v_maxlen)
			v_len += v_speed;
		for (int i = 0; i < v_speed; i++)
		{
			v_end.x += direct[v_direction].x;
			v_end.y += direct[v_direction].y;
		}
	}
	bool IsStopped()
	{
		return v_stopped;
	}
	void SetStop()
	{
		v_stopped = true;
	}
	void AddChild(Node* node)
	{
		v_children.push_back(node);
	}
	int GetNumOfChildren()
	{
		return v_children.size();
	}
	vector<Node*> GetChildren()
	{
		return v_children;
	}
	virtual int GetNumChildNodes() = 0;
};

class RedNode : public Node
{
public:
	RedNode(Node* parent) :Node(parent)
	{
		v_speed = 1;
		v_maxlen = 20;
	}
	int GetNumChildNodes()  override
	{
		return 2;
	}
};

class BlueNode : public Node
{

public:
	BlueNode(Node* parent) :Node(parent)
	{
		v_speed = 2;
		v_maxlen = 30;
	}
	int GetNumChildNodes()  override
	{
		return 1;
	}
};

class TreeBuilder
{
private:
	Node* v_tree;

	Node* getRandomNode(Node* parent)
	{
		if (rand() % 2 == 0)
			return new RedNode(parent);
		else
			return new BlueNode(parent);
	}
public:
	TreeBuilder()
	{
		v_tree = getRandomNode(NULL);
	}
	void NextStep()
	{
		Node* tree = v_tree;
		queue<Node*> q;
		q.push(tree);
		while (!q.empty())
		{
			auto t = q.front();
			q.pop();
			if (!t->IsStopped())
			{
				t->IncLength();
				if (t->GetLength() == t->GetMaxLen())
				{
					t->SetStop();
				}
			}
			if (t->IsStopped() && t->GetNumOfChildren() == 0)
			{
				for (int i = 0; i < t->GetNumChildNodes(); i++)
				{
					Node* ct = getRandomNode(t);
					t->AddChild(ct);
				}
			}
			if (t->IsStopped() && t->GetNumChildNodes() == t->GetNumOfChildren())
			{
				for (int i = 0; i < t->GetNumOfChildren(); i++)
				{
					q.push(t->GetChildren()[i]);
				}
			}
		}
	}
};

int main()
{
	TreeBuilder* builder = new TreeBuilder();
	for (int i = 0; i < 1000; i++)
	{
		builder->NextStep();
	}
	return 0;
}