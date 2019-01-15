#pragma once
#include <fstream>
#include <string>
#include "WG_Matrix.h"
#include <algorithm>
#define UNDEFINED -999

const int fullImageH = 768;
const int fullImageW = 1024;
const int refImageH = 49;
const int refImageW = 36;




namespace ReadWrite
{
	double* read_text(const char *fileName, int sizeR, int sizeC);
	void write_pgm(const char *filename, double *data, int sizeR, int sizeC, int Q);
}

struct Guess
{
public:
	int r;
	int c;
	float SAD;
	Guess(int x, int y, float s);

	bool operator==(const Guess &g)
	{
		if (r == g.r && c == g.c && SAD == g.SAD)
		{
			return true;
		}
		return false;

	}
};


class Base_Image
{
public:
	Matrix *imageData;
	Metric *imageMetrics = new Metric(0,0);
	void LoadFile(const char* path);
	Base_Image(int h, int w);
	Base_Image();
	~Base_Image();
};


class Reference_Image : public Base_Image
{
	using Base_Image::Base_Image;
};

class Large_Image : public Base_Image
{
public:
	//Chunk amounts, 32x16
	//Chunk dimentions, 32x48
	const Metric chunkSize = Metric(48, 32);
	Metric chunkAmounts = Metric(0, 0);

	Large_Image(int h, int w, Reference_Image *ri);
	Matrix *GetChunkMatrix(Matrix *m, int startr, int startc);
	Matrix *GetImageGuess(Guess *g);
	Matrix *GetImageGuess(std::vector<Guess*> *g);
};

