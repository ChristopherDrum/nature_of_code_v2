#include "../../processing.h"
#include "raylib.h"
#include <stdio.h>
#include <math.h>

const int PERLIN_YWRAPB = 4;
const int PERLIN_YWRAP = 1 << PERLIN_YWRAPB;
const int PERLIN_ZWRAPB = 8;
const int PERLIN_ZWRAP = 1 << PERLIN_ZWRAPB;
const int PERLIN_SIZE = 4095;

int perlin_octaves = 4; 		// default to medium smooth
float perlin_amp_falloff = 0.5; // 50% reduction/octave
#define scaled_cosine(x) ((0.5 * (1.0 - cos((x) * PI))) + 0.5)


//implementing from https://github.com/processing/p5.js/blob/36437b3d68bc651b8695a401159eef36aeec5881/src/math/noise.js#L200
//x is required, and if you don't need y and z pass 0 for those
float noise(float x, float y, float z)
{
	static float perlin[4096];
	if (perlin[0] == 0.0f)
	{
		for (size_t i = 0; i < 4096; i++)
		{
			perlin[i] = randf(1);
		}
	}

	if (x < 0) x = -x;
	if (y < 0) y = -y;
	if (z < 0) z = -z;

	int xi = floorf(x);
	int yi = floorf(y);
	int zi = floorf(z);

	float xf = x - xi;
	float yf = y - yi;
	float zf = z - zi;

	float rxf, ryf;
	float r = 0.0;
	float ampl = 0.5f;

	float n1, n2, n3;

	for (size_t o = 0; o < perlin_octaves; o++)
	{
		int of = xi + (yi << PERLIN_YWRAPB) + (zi << PERLIN_ZWRAPB);
		rxf = scaled_cosine(xf);
		ryf = scaled_cosine(yf);

		n1 = perlin[of & PERLIN_SIZE];
		n1 += rxf * (perlin[(of+1) & PERLIN_SIZE] - n1);
		n2 = perlin[(of + PERLIN_YWRAP) & PERLIN_SIZE];
		n2 += rxf * (perlin[(of + PERLIN_YWRAP + 1) & PERLIN_SIZE] - n2);
		n1 += ryf * (n2 - n1);

		of += PERLIN_ZWRAP;
		n2 = perlin[of & PERLIN_SIZE];
		n2 += rxf * (perlin[(of + 1) & PERLIN_SIZE] - n2);
		n3 = perlin[(of + PERLIN_YWRAP) & PERLIN_SIZE];
		n3 += rxf * (perlin[(of + PERLIN_YWRAP + 1) & PERLIN_SIZE] - n3);
		n2 += ryf * (n3 - n2);

		n1 += scaled_cosine(zf) * (n2 - n1);

		r += n1 * ampl;
		ampl *= perlin_amp_falloff;
		xi <<= 1;
		xf *= 2;
		yi <<= 1;
		yf *= 2;
		zi <<= 1;
		zf *= 2;

		if (xf >= 1.0) {
			xi++;
			xf--;
		}
		if (yf >= 1.0) {
			yi++;
			yf--;
		}
		if (zf >= 1.0) {
			zi++;
			zf--;
		}
	}
	return r;
}

int main(void)
{
	int frame = 1;
	for (size_t i = 0; i < 20; i++)
	{
		float x = 100 * noise(0.005 * frame, 0, 0);
		float x = 100 * stb_p
		float y = 100 * noise(0.005 * frame + 10000, 0, 0);
		printf("%.5f, %.5f\n", x, y);
		frame++;
	}
	
	return(0);
}