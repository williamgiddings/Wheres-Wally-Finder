#include "WG_Matrix.h"
#include "WG_Utils.h"
#include <iostream>
#include <vector>



const char* refPath = "./resources/Wally_grey.txt";
const char* largePath = "./resources/Cluttered_scene.txt";
const char* output = "./resources/wally.pgm";
const int nGuesses = 3;

Guess GetSumDiff(Reference_Image *ri, Large_Image *li);
std::vector<Guess*> *Guesses;



int main()
{
	Guesses = new std::vector<Guess*>();

	std::cout << "Loading Images...\n";
	Reference_Image *refImage = new Reference_Image(refImageH, refImageW);
	refImage->LoadFile(refPath);
	Large_Image *largeImage = new Large_Image(fullImageH, fullImageW, refImage);
	largeImage->LoadFile(largePath);

	std::cout << "Looking For Wally...\n";
	Guess *guess = new Guess(0,0,0.0f);
	*guess = GetSumDiff(refImage, largeImage); //Gets the segment with the lowest sum of differences


	std::cout << "Found Him! \n";
	Matrix *guessData = new Matrix(fullImageH, fullImageW);
	guessData = largeImage->GetImageGuess(guess); //Gets the whole image with 'wally' highlighted
	
	std::cout << "Writing File to '" << output << "'\n";
	ReadWrite::write_pgm(output, guessData->MatrixToDoubles(), guessData->length()->r, guessData->length()->c, 255);//write output file


	std::cout << "Done\n";

	//Cleanup
	delete guess;
	delete guessData;
	delete refImage;
	delete largeImage;

	return 0;
}

Guess GetSumDiff(Reference_Image *ri, Large_Image *li)
{
	float minDifferences = UNDEFINED; 
	Guess *guess = new Guess(0,0,0);

	for (int x = 0; x <= li->imageMetrics->c - ri->imageMetrics->c; x+= ri->imageMetrics->c/2) {
		for (int y = 0; y <= li->imageMetrics->r - ri->imageMetrics->r; y+= ri->imageMetrics->r/2) {
			float curDifferences = 0.0f;

			for (int j = 0; j < ri->imageMetrics->c; j++)
				for (int i = 0; i < ri->imageMetrics->r; i++) {
					float largeImagePixel = li->imageData->GetValueFast((y + i),(x + j));
					float refImagePixel = ri->imageData->GetValueFast(i, j);

					curDifferences += abs(largeImagePixel - refImagePixel);
					
				}
				
			if (minDifferences == UNDEFINED) 
			{
				minDifferences = curDifferences;
				
			}
			if (minDifferences > curDifferences) {
				
				guess->c = x;
				guess->r = y;
				guess->SAD = curDifferences;
				minDifferences = curDifferences;
				
				
			}
		}

	}
	return *guess;
}



