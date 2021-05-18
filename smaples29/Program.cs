using System;
using System.Collections.Generic;

namespace smaples29
{

	enum CarEnum { SUV, HATCHBACK, SEDAN }

	class Wheel
	{
		public int Size { get; set; }
	};

	class Engine
	{
		public int horsepower { get; set; }
	}

	class Body
	{
		public CarEnum shape;
		public string toString()
		{
			if (shape == CarEnum.SUV)
				return "SUV";
			else if (shape == CarEnum.HATCHBACK)
				return "HATCHBACK";
			else if (shape == CarEnum.SEDAN)
				return "SEDAN";
			else return "";
		}
	}

	class Car
	{
	public string Brand { get; set; }
		public List<Wheel> wheels { get; set; }
		public Engine engine { get; set; }
		public Body body { get; set; }
		public void Specifications()
		{
			if (body != null)
			{
				Console.WriteLine($"brand: {Brand}"); ;
				Console.WriteLine($"body: {body.toString()}");
				Console.WriteLine($"engine horsepower:{engine.horsepower}");
				Console.WriteLine($"tire size:{wheels[0].Size}'");
			}
		}
	}

	interface IBuilder
	{
		string getBrand();
		Wheel getWheel();
		Engine getEngine();
		Body getBody();
	}


	class JeepBuilder : IBuilder
	{
		public string getBrand()
		{
			return "Jeep";
		}
		public Wheel getWheel()
		{
			Wheel wheel = new Wheel();
			wheel.Size = 22;
			return wheel;
		}
		public Engine getEngine()
		{
			Engine engine = new Engine();
			engine.horsepower = 400;
			return engine;
		}
		public Body getBody()
		{
			Body body = new Body();
			body.shape = CarEnum.SUV;
			return body;
		}
	}

	class NissanBuilder : IBuilder
	{
		public string getBrand()
		{
			return "Nissan";
		}
		public Wheel getWheel()
		{
			Wheel wheel = new Wheel();
			wheel.Size = 16;
			return wheel;
		}
		public Engine getEngine()
		{
			Engine engine = new Engine();
			engine.horsepower = 85;
			return engine;
		}
		public Body getBody()
		{
			Body body = new Body();
			body.shape = CarEnum.HATCHBACK;
			return body;
		}
	}

/*class BMWBuilder : public Builder
{
public:
	string getBrand()
{
	return "BMW";
}

Wheel* getWheel()
{
	Wheel* wheel = new Wheel();
	wheel->size = 21;
	return wheel;
}
Engine* getEngine()
{
	Engine* engine = new Engine();
	engine->horsepower = 500;
	return engine;
}
Body* getBody()
{
	Body* body = new Body();
	body->shape = Body::SEDAN;
	return body;
}
};*/

class Director
{
	private IBuilder builder;
	public	void setBuilder(IBuilder newBuilder)
	{
		builder = newBuilder;
	}
	public Car getCar()
	{
		Car car = new Car();
		car.Brand = builder.getBrand();
		car.body = builder.getBody();
		car.engine = builder.getEngine();
		car.wheels = new List<Wheel>();
		car.wheels.Add(builder.getWheel());
		car.wheels.Add(builder.getWheel());
		car.wheels.Add(builder.getWheel());
		car.wheels.Add(builder.getWheel());
		return car;
	}
};
class Program
    {
        static void Main(string[] args)
        {
			List<IBuilder> builders = new List<IBuilder> 
				{ new JeepBuilder(), new NissanBuilder() };

			List<Car> cars = new List<Car>();
			Director director = new Director();
			JeepBuilder jeepBuilder = new JeepBuilder();
			NissanBuilder nissanBuilder = new NissanBuilder();
//			BMWBuilder bmwBuilder;

			for (int i = 0; i < 18; i++)
			{
				director.setBuilder(builders[i % 2]);
				cars.Add(director.getCar());
			}

			foreach (var car in cars)
			{
				car.Specifications();
				Console.WriteLine();
			}
		}
    }
}
