#include<iostream>
#include<vector>
#include<cmath>
#include<ctime>
// Улучшенная версия классической реализации
class Singleton;
class Destroyer {
	Singleton* p_instance;
public:
	~Destroyer();
	void initialize(Singleton* p);
};
class Singleton {
	static Singleton* p_instance;
	static Destroyer destroyer;
public:
	static Singleton& getInstance();
protected:
	friend class Destroyer;
	Singleton() {}
	~Singleton() {}
	Singleton(Singleton const&) = delete;
	void operator=(Singleton const&) = delete;
};

Destroyer::~Destroyer() {
	delete p_instance;
}
void Destroyer::initialize(Singleton* p) {
	p_instance = p;
}
Singleton& Singleton::getInstance() {
	if (!p_instance) {
		p_instance = new Singleton();
		destroyer.initialize(p_instance);
	}
	return *p_instance;
}

int main()
{
	Singleton s();
	return 0;
}
