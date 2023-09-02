//This is intended to be a single-file include to add the "missing" Processing functions to a Raylib project
#include <stdio.h>
#include <stdlib.h>
#include <float.h>
#include <stdbool.h>
#include <time.h>
#include <math.h>

float randf(float limit)
{
	float r = (float)rand()/(float)RAND_MAX;
	return r * limit;
}

//implemented from https://github.com/processing/p5.js/blob/36437b3d68bc651b8695a401159eef36aeec5881/src/math/random.js#L247
//pass mean=0, sd=1 for "defaults" 
float randomGaussian(float mean, float sd)
{
	float y1 = 0.0f;
	static bool y2Precalculated = false;
	static float y2 = 0.0f;
	float x1 = 0.0f;
	float x2 = 0.0f;
	float w = 0.0f;

	if (y2Precalculated)
	{
		y1 = y2;
		y2 = 0.0f;
		y2Precalculated = false;
	} else {
		do
		{
			x1 = randf(2) - 1.0f; //shift so we have -1.99999 to +1.99999 range
			x2 = randf(2) - 1.0f;
			w = (x1*x1) + (x2*x2);
		} while (w >= 1);
		w = sqrtf(-2 * logf(w) / w);
		y1 = x1*w;
		y2 = x2*w;
		y2Precalculated = true;
	}
	return y1 * sd + mean;
}
