#include<iostream>
#include<algorithm>
#include <sstream>  
#include <string>
#include<vector>
#include<queue>
#include<map>

using namespace std;

class Wheel {
public:
	int size;
};

class Engine {
public:
	int horsepower;
};

class Body {
public:
	enum { SUV, HATCHBACK, SEDAN } shape;
	string toString() 
	{
		if (shape == SUV)
			return "SUV";
		else if (shape == HATCHBACK)
			return "HATCHBACK";
		else if (shape == SEDAN)
			return "SEDAN";
		else return "";
	};
};

class Car {
public:
	string Brand;
	vector<Wheel*> wheels;
	Engine* engine;
	Body* body;
	void specifications() {
		if (body)
		{
			cout << "brand:" << Brand << endl;
			cout << "body:" << body->toString() << endl;
			cout << "engine horsepower:" << engine->horsepower << endl;
			cout << "tire size:" << wheels[0]->size << "'" << endl;
		}
	}
};

class Builder {
public:
	virtual string getBrand() = 0;
	virtual Wheel* getWheel() = 0;
	virtual Engine* getEngine() = 0;
	virtual Body* getBody() = 0;
};


class JeepBuilder : public Builder {
public:
	string getBrand()
	{
		return "Jeep";
	}
	Wheel* getWheel() {
		Wheel* wheel = new Wheel();
		wheel->size = 22;
		return wheel;
	}
	Engine* getEngine() {
		Engine* engine = new Engine();
		engine->horsepower = 400;
		return engine;
	}
	Body* getBody() {
		Body* body = new Body();
		body->shape = Body::SUV;
		return body;
	}
};

class NissanBuilder : public Builder {
public:
	string getBrand()
	{
		return "Nissan";
	}
	Wheel* getWheel() {
		Wheel* wheel = new Wheel();
		wheel->size = 16;
		return wheel;
	}
	Engine* getEngine() {
		Engine* engine = new Engine();
		engine->horsepower = 85;
		return engine;
	}
	Body* getBody() {
		Body* body = new Body();
		body->shape = Body::HATCHBACK;
		return body;
	}
};

class BMWBuilder : public Builder {
public:
	string getBrand()
	{
		return "BMW";
	}

	Wheel* getWheel() {
		Wheel* wheel = new Wheel();
		wheel->size = 21;
		return wheel;
	}
	Engine* getEngine() {
		Engine* engine = new Engine();
		engine->horsepower = 500;
		return engine;
	}
	Body* getBody() {
		Body* body = new Body();
		body->shape = Body::SEDAN;
		return body;
	}
};

class Director {
	Builder* builder;
public:
	void setBuilder(Builder* newBuilder) {
		builder = newBuilder;
	}
	Car* getCar() {
		Car* car = new Car();
		car->Brand = builder->getBrand();
		car->body = builder->getBody();
		car->engine = builder->getEngine();
		car->wheels.push_back(builder->getWheel());
		car->wheels.push_back(builder->getWheel());
		car->wheels.push_back(builder->getWheel());
		car->wheels.push_back(builder->getWheel());
		return car;
	}
};
/*
int main() {
	vector<Builder*> builders = { new  JeepBuilder(), new NissanBuilder(), new BMWBuilder() };

	vector<Car*> cars;
	Director director;
	JeepBuilder jeepBuilder;
	NissanBuilder nissanBuilder;
	BMWBuilder bmwBuilder;

	for (int i = 0; i < 18; i++)
	{
		director.setBuilder(builders[i % 3]);
		cars.push_back(director.getCar());
	}

	for (auto car : cars)
	{
		car->specifications();
		cout << endl;
	}

	return 0;
}
*/ 

