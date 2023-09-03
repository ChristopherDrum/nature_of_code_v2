#include "../../processing.h"
#include "raylib.h"
#include <stdio.h>

#define BUCKETS 20

int distribution[BUCKETS] = {0};
int totalSamples = 1;

int acceptReject(int min, int max)
{
	while (true)
	{
		int b1 = GetRandomValue(0,BUCKETS-1);
		float probability = (float)b1/BUCKETS;
		int b2 = GetRandomValue(0,BUCKETS-1);
		float ar = (float)b2/BUCKETS;
		if (ar < probability) return b1;	//linear
		// if (ar < (probability * probability)) return b1;	//quadratic
	}
}

int main() 
{
	// Initialization
	//--------------------------------------------------------------------------
	const int screenWidth = 800;
	const int screenHeight = 600;

	InitWindow(screenWidth, screenHeight,
		"Nature of Code, Chapter 0, Random Distribution Visualization");

	SetTargetFPS(60);

	// Main game loop
	while (!WindowShouldClose())	// Detect window close button or ESC key
	{
		int sampleCount = 1; //increase to get faster equilibrium
		for (size_t i = 0; i < sampleCount; i++)
		{
			int bucketNumber = acceptReject(0,BUCKETS-1);
			distribution[bucketNumber]++;
			totalSamples++;
		}
		
		BeginDrawing();
			ClearBackground(BLACK);
			int bucketWidth = screenWidth/BUCKETS;
			for (size_t i = 0; i < BUCKETS; i++)
			{
				float bucketHeight = (float)distribution[i]/totalSamples*screenHeight * 5;
				DrawRectangle(i*bucketWidth,screenHeight-bucketHeight,bucketWidth,bucketHeight,YELLOW);
				DrawRectangleLines(i*bucketWidth,screenHeight-bucketHeight,bucketWidth,bucketHeight,BLACK);
			}
		EndDrawing();
	}

	
	// De-Initialization
	CloseWindow();	// Close window and OpenGL context

	return(0);
}
