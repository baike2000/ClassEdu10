#include<iostream>
#include<vector>
#include<cmath>
#include<ctime>

using namespace std;

template<typename T>
T sum(vector<T>& v)
{
	T s = 0;
	for (int i = 0; i < v.size(); i++)
		s += v[i];
	return s;
}

template<typename T1, typename T2>
vector<T2> mapi(vector<T1>& v1, T2 fn(T1 point))
{
	vector<T2> v;
	for (int i = 0; i < v1.size(); i++)
	{
		v.push_back(fn(v1[i]));
	}
	return v;
}

class QPointF
{
private:
	double _x, _y;
public:

	QPointF(double x, double y)
	{
		_x = x;
		_y = y;
	}

	double x()
	{
		return _x;
	}
	double y()
	{
		return _y;
	}
};

class BaseRegression {
public:
	BaseRegression(vector<QPointF*> &points)
	{
		_points = points;
		_size = (int)_points.size();
		mse();
		std();
	}
	virtual double y(double x) = 0;
	
	QPointF point(double x) {
		return QPointF(x, y(x));
	}

	double mse()
	{
		double mse_ = 0;
		for (int i = 0; i < _points.size(); i++)
		{
			mse_ += _points[i]->x();
		}
		_mse = mse_ / _points.size();
		return _mse;
	}
	double std() 
	{
		double std_ = 0;
		for (int i = 0; i < _points.size(); i++)
		{
			std_ += pow(_points[i]->x() - _mse,2);
		}
		std_ = sqrt(std_ / _points.size());
		_std = std_;
		return _std;
	}

protected:
	virtual void calculate() = 0;
	vector<QPointF*> _points;
	int _size;
	double _mse;
	double _std;
};

class LinearRegression: public BaseRegression 
{
public:
	LinearRegression(vector<QPointF*> &points) :BaseRegression(points) 
	{
		calculate();
	}

	// y=Ax+B
	double a()
	{
		return _a;
	}
	double b()
	{
		return _b;
	}

	double y(double x) { return a() * x + b(); }
	double x(double y) { return (y - b()) / a(); }
	QPointF point(double x) { return QPointF(x, y(x)); }

protected:
	void calculate() override
	{
		auto xx = mapi<QPointF*, double>(_points, [](QPointF* point) { return point->x(); });
		auto sx = sum(xx);
		auto yy = mapi<QPointF*, double>(_points, [](QPointF* point) { return point->y(); });
		auto sy = sum(yy);
		auto list_xy = mapi<QPointF*, double>(_points, [](QPointF* point) { return point->y() * point->x(); });
		auto sxy = sum(list_xy);
		auto list_x_sq = mapi<QPointF*, double>(_points, [](QPointF* point) { return point->x() * point->x(); });
		auto sx_sq = sum(list_x_sq);
		double a = double(rand() % 100 - 50) / 100;
		double b = double(rand() % 100 - 50) / 100;
		vector<double> errors { 1, 0 };
		double tolerance = 0.0000000001;
		vector<double> ab(2);
		double l = 0.1;
		while (abs(errors[errors.size() - 1] - errors[errors.size() - 2]) > tolerance)
		{
			auto a_step = a - l * (_size * a + b * sx - sy) / _size;
			auto b_step = b - l * (a * sx + b * sx_sq - sxy) / _size;
			a = a_step;
			b = b_step;
			ab[0] = a; ab[1] = b;
			errors.push_back(errors_sq(ab));
		}
		_a = ab[0];
		_b = ab[1];
	}
	double _a, _b;
	double errors_sq(vector<double>& answers)
	{
		vector<double> list_errors;
		double sum = 0;
		for (int i = 0; i < _points.size(); i++)
		{
			double err = pow(answers[1] + answers[0] * _points[i]->x() - _points[i]->y(), 2);
			list_errors.push_back(err);
			sum += err;
		}
		return sum;
	}
};



class ExponentialRegression : public BaseRegression 
{
public:
	ExponentialRegression(vector<QPointF*> &points) :BaseRegression(points) 
	{
		calculate();
	};

	// y=A*exp(B*x)
	double a()
	{
		return _a;
	}
	double b()
	{
		return _b;
	}
	double y(double x) 
	{ 
		return a() * exp(b() * x); 
	}
protected:
	void calculate() override
	{
		vector<QPointF*> logpoints(_size);
		for (int i = 0; i < _size; ++i)
			logpoints[i] = new QPointF(_points[i]->x(),log(fabs(_points[i]->y())));
		LinearRegression lr(logpoints);
		_b = lr.a();
		_a = exp(lr.b());
		if (_size > 0 && _points[0]->y() < 0)
			_a *= -1;
		ready = true;
		for (int i = 0; i < _size; ++i)
			delete logpoints[i];
	}

	bool ready;
	double _a, _b;
};

int main()
{
	vector<QPointF*> points { new QPointF(1,5.3), new QPointF(2,6.3), 
		                        new QPointF(3,4.8), new QPointF(4,3.8), new QPointF(5,3.3) };
	LinearRegression* lr = new LinearRegression(points);
	cout << lr->a() << " " << lr->b();
	return 0;
}