#include "WG_Utils.h"
#include <string>
#include "WG_Matrix.h"
#include <iostream>

void Base_Image::LoadFile(const char* path) //Load pgm data from a file into a matrix
{
	imageData->Populate(ReadWrite::read_text(path, imageMetrics->c, imageMetrics->r), imageMetrics);
}

double clip(double n, double lower, double upper)
{
	return std::max(lower, std::min(n, upper));
}

Base_Image::Base_Image(int h, int w) //Initialize reference data
{
	imageData = new Matrix(h, w);
	imageMetrics = new Metric(h, w);	
}

Base_Image::Base_Image()
{
}

Base_Image::~Base_Image() //Cleanup reference data
{
	delete imageData;
	delete imageMetrics;
}

Large_Image::Large_Image(int h, int w, Reference_Image *ri)
{
	imageData = new Matrix(h, w);
	imageMetrics = new Metric(h, w);
	chunkAmounts = Metric(h/ri->imageMetrics->r, w / ri->imageMetrics->c);
}

Matrix *Large_Image::GetChunkMatrix(Matrix *m, int startr, int startc)
{

	m->Populate(imageData, m->length(), startr, startc);
	return m;
	
}

Guess::Guess(int x, int y, float s)
{
	r = x;
	c = y;
	SAD = s;
}


Matrix *Large_Image::GetImageGuess(std::vector<Guess*>* g)
{
	Matrix *newM = new Matrix(fullImageH, fullImageW);
	newM->Populate(imageData, imageMetrics, 0, 0);

	for (auto &guess : *g)
	{
		for (int x = guess->r; x < guess->r + refImageH; x++)
		{
			newM->SetValue(x, guess->c, 0);
			newM->SetValue(x, guess->c + refImageW, 0);

			for (int y = guess->c; y < guess->c + refImageW; y++)
			{

				if (x == guess->r || x == guess->r + refImageH - 1)
				{
					newM->SetValue(x, y, 0);
				}
				newM->SetValue(x, y, clip(newM->GetValue(x, y)*0.5f, 0, 255));
			}
		}
	}

	
	return newM;
}

Matrix *Large_Image::GetImageGuess(Guess *g)
{
	Matrix *newM = new Matrix(fullImageH, fullImageW);
	newM->Populate(imageData, imageMetrics, 0, 0);

	for (int x = g->r; x < g->r + refImageH; x++)
	{
		newM->SetValue(x, g->c, 0);
		newM->SetValue(x, g->c + refImageW, 0);

		for (int y = g->c; y < g->c + refImageW; y++)
		{
			
			if (x == g->r || x == g->r + refImageH - 1)
			{
				newM->SetValue(x, y, 0);
			}
			newM->SetValue(x, y,clip(newM->GetValue(x, y)*0.5f, 0, 255));
		}
	}
	return newM;

}

