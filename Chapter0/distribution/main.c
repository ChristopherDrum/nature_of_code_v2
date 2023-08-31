#include "raylib.h"
#include <stdio.h>

#define BUCKETS 20

int distribution[BUCKETS] = {0};
int totalSamples = 1;

int main() 
{
	// Initialization
	//--------------------------------------------------------------------------
	const int screenWidth = 800;
	const int screenHeight = 600;

	InitWindow(screenWidth, screenHeight,
		"Nature of Code, Chapter 0, Random Walker");

	SetTargetFPS(60);

	// Main game loop
	while (!WindowShouldClose())	// Detect window close button or ESC key
	{
		int sampleCount = 1; //increase to get faster equilibrium
		for (size_t i = 0; i < sampleCount; i++)
		{
			int bucketNumber = GetRandomValue(0,BUCKETS-1);
			distribution[bucketNumber]++;
			totalSamples++;
		}
		
		BeginDrawing();
			ClearBackground(BLACK);
			int bucketWidth = screenWidth/BUCKETS;
			for (size_t i = 0; i < BUCKETS; i++)
			{
				float bucketHeight = (float)distribution[i]/totalSamples*screenHeight;
				DrawRectangle(i*bucketWidth,screenHeight-bucketHeight,bucketWidth,bucketHeight,YELLOW);
				DrawRectangleLines(i*bucketWidth,screenHeight-bucketHeight,bucketWidth,bucketHeight,BLACK);
			}
		EndDrawing();
	}

	
	// De-Initialization
	CloseWindow();	// Close window and OpenGL context

	return(0);
}
