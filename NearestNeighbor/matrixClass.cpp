#include "WG_Matrix.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "WG_Utils.h"
#include <vector>




void Matrix::Populate(double *val, Metric *m)
{
	int index = 0;
	for (int r = 0; r < m->r; r++)
	{
		for (int c = 0; c < m->c; c++)
		{
			
			SetValue(r, c, val[index]);
			index++;
		}
	}
}

void Matrix::Populate(Matrix *val, Metric * metric, int startR, int startC)
{
	int indexX = 0;
	for (int r = startR; r <= startR + metric->r; r++)
	{
		indexX++;
		int indexY = 0;
		for (int c = startC; c <= startC + metric->c; c++)
		{
			indexY++;
			if (r <= val->length()->r && c <= val->length()->c)
			{
				SetValue(indexX, indexY, val->GetValue(r, c), true);
				
			}
		}
	}

}

Matrix::Matrix(int x, int y)
{
	values = std::vector<std::vector<double>>(x, std::vector<double>(y, 0.0f));
	len = new Metric(x,y);
}
Matrix::~Matrix()
{
	delete len;
}

double Matrix::GetValue(int indexX, int indexY)
{
	if (values.size() > indexX && values[indexX].size() > indexY)
	{
		return values[indexX][indexY];
	}
	return 0;
}

double Matrix::GetValueFast(int indexX, int indexY)
{
	return values[indexX][indexY];
}

double* Matrix::MatrixToDoubles()
{
	Matrix *m = this;
	double *values = new double[(m->length()->r)*(m->length()->c)];
	int indx = 0;
	for (int r = 0; r < m->len->r; r++)
	{
		for (int c = 0; c < m->len->c; c++)
		{
			values[indx] = m->GetValueFast(r,c);
			indx += 1;

		}
	}
	return values;
}

void Matrix::SetValue(int indexX, int indexY, double val)
{
	if (indexX <= values.size() && indexY <= values[0].size())
	{
		values[indexX][indexY] = val;
	}
	
}

void Matrix::SetValue(int indexX, int indexY, double val, bool test)
{
	if (indexX < values.size() && indexY < values[0].size())
	{
		values[indexX][indexY] = val;
	}

}

Metric *Matrix::length()
{
	return len;
}