#pragma once
#include <vector>
#include <string>


struct Metric
{
public:
	int r;
	int c;
	Metric(int tr, int tc)
	{
		c = tc;
		r = tr;
	}
};


class Matrix
{
private:
	std::vector<std::vector<double>> values;
	Metric *len;
	
public:
	
	Matrix(int x, int y);
	~Matrix();
	void Populate(double* val, Metric *metric);
	void Populate(Matrix *val, Metric * metric, int startR, int startC);
	double GetValue(int indexX, int indexY);
	double GetValueFast(int indexX, int indexY);
	void SetValue(int indexX, int indexY, double val, bool test);
	void SetValue(int indexX, int indexY, double val);
	double* MatrixToDoubles();
	Metric *length();
	std::vector<double> operator[](const int index) {
		return values.at(index);
	};
	

};


