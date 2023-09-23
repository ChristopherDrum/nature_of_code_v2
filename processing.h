//This is intended to add "missing" Processing functions to a Raylib project
#include "raylib.h"
#include "raymath.h"
#include <stdio.h>
#include <stdlib.h>
#include <float.h>
#include <stdbool.h>
#include <math.h>
#include <external/stb_perlin.h>

#define TWOPI 6.28318530717958647692f;

float _clamp(float value, float min, float max)
{
	if (value < min) return min;
	if (value > max) return max;
	return value;
}

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

//Uses "rational" default values and returns float from [0,1]
//Pass 0 for y and/or z when in doubt
float noise(float x, float y, float z)
{
	float n = stb_perlin_fbm_noise3(x, y, z, 2.0f, 0.5f, 4);
	n = _clamp(n, -1.0, 1.0);
	return (n + 1.0f)/2.0f;	
}

float heading2D(Vector2 *vec)
{
	return atan2f(vec->y, vec->x);
}

void mult2D(Vector2 *vec, float n)
{
	vec->x *= n;
	vec->y *= n;
}

void setMag2D(Vector2 *vec, float len)
{
	*vec = Vector2Normalize(*vec);
	mult2D(vec, len);
}

Vector2 Vector2Unit(void)
{
	return (Vector2){1.0f, 0.0f};
}

//Raylib-aligned function name
Vector2 Vector2Random(void)
{
	//start with a unit vector at angle 0, then rotate it by a random angle
	float randomAngle = randf(1)*TWOPI;
	return Vector2Rotate(Vector2Unit(), randomAngle);
}
//P5.js-aligned function name
Vector2 random2D(void) {  return Vector2Random();  }

Vector2 Vector2SetLength(Vector2 v, float len)
{
	Vector2 newVec = Vector2Normalize(v);
	newVec = Vector2Scale(newVec, len);
	return newVec;
}
