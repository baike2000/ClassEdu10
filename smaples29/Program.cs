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
		public int Horsepower { get; set; }
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
				Console.WriteLine($"engine horsepower:{engine.Horsepower}");
				Console.WriteLine($"tire size:{wheels[0].Size}'");
			}
		}
	}

	interface IBuilder
	{
		string getBrand { get; }
		Wheel getWheel();
		Engine getEngine();
		Body getBody();
	}


	class JeepBuilder : IBuilder
	{
		public string getBrand => "Jeep";
		public Wheel getWheel() => new() { Size = 22 };
		public Engine getEngine() => new() { Horsepower = 400 };
		public Body getBody() => new() { shape = CarEnum.SUV };
	}

	class NissanBuilder : IBuilder
	{
		public string getBrand => "Nissan";
		public Wheel getWheel() => new() { Size = 16 };
		public Engine getEngine() => new() { Horsepower = 85 };
		public Body getBody() => new() { shape = CarEnum.HATCHBACK };
	}

	class BMWBuilder : IBuilder
	{
		public string getBrand => "BMW";
		public Wheel getWheel() => new() { Size = 21 };
		public Engine getEngine() => new() { Horsepower = 500 };
        public Body getBody() => new() { shape = CarEnum.SEDAN };
	}

	class Director
	{
		private IBuilder builder;
        public void setBuilder(IBuilder newBuilder) => builder = newBuilder;
        public Car getCar() =>
			new()
            {
				Brand = builder.getBrand,
				body = builder.getBody(),
				engine = builder.getEngine(),
                wheels = new List<Wheel>()
				{
					builder.getWheel(),
					builder.getWheel(),
					builder.getWheel(),
					builder.getWheel()
				}
			};
	}
class Program
    {
        static void Main(string[] args)
        {
			List<IBuilder> builders = new() { new JeepBuilder(), new NissanBuilder(), new BMWBuilder() };

			var cars = new List<Car>();
			var director = new Director();
			var jeepBuilder = new JeepBuilder();
			var nissanBuilder = new NissanBuilder();
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
