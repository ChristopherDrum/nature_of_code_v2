#include "../../processing.h"
#include "raylib.h"
#include "raymath.h"
#include <stdio.h>
#include <math.h>


int frameCount = 0;

const int screenWidth = 800;
const int screenHeight = 800;

const int virtualWidth = 300;
const int virtualHeight = 300;

bool pause = false;


// A black dot moves randomly on a gray square
void Test1()
{
	ClearBackground(DARKGRAY);
	float xn = noise(0.01*frameCount, 0, 0);
	float yn = noise(0.01*frameCount + 50000, 0, 0);
	// printf("%.5f, %.5f\n", xn, yn);
	float x = 100 * xn;
	float y = 100 * yn;
	DrawCircle(x, y, 2, BLACK);	
}

// A calm sea drawn in gray against a black sky. Wow!
void Test2()
{
	ClearBackground(LIGHTGRAY);
	float noiseLevel = 100.0;
	float noiseScale = 0.002f;

	for (size_t x = 0; x < virtualWidth; x++)
	{
		float nx = noiseScale * (float)x;
		float nt = noiseScale * (float)frameCount;
		float y = noiseLevel * noise(nx, nt, 0);
		DrawLine(x,0,x,y,BLACK);
	}
}

// A cloudy pattern that changes, against a blue sky.
void Test3()
{
	ClearBackground(BLUE);
	float noiseScale = .009;

	for (int y = 0; y < virtualHeight; y++)
	{
		for (int x = 0; x < virtualWidth; x++)
		{
			float nx = noiseScale * (float)x;
			float ny = noiseScale * (float)y;
			float nt = noiseScale * (float)frameCount;
			float n = noise(nx, ny, nt);
			int c = (int)(n * 255.0f);
			if (c < 0) c = 0;
			if (c > 255) c = 255;
			DrawPixel(x, y, (Color){255,255,255,c});
			// below is used to trap when noise() returns odd values
			// if (c < 0 || c > 255) {
			// 	pause = true;
			// 	printf("%f, %f, %f => %f => %d", nx, ny, nt, n, c);
			// 	return;
			// }
		}
	}
	
}

int main() 
{
    // Initialization
    //--------------------------------------------------------------------------


    InitWindow(screenWidth, screenHeight,
		"Nature of Code, Chapter 0, Perlin Tests");

    SetTargetFPS(60);

	RenderTexture2D virtualScreen = LoadRenderTexture(virtualWidth, virtualHeight);

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
		frameCount++;

		// for debugging purposes
		if (GetCharPressed() == 'p') pause = !pause;

		if (!pause)
		{
			BeginTextureMode(virtualScreen);
				Test3();
			EndTextureMode();
		}

		BeginDrawing();
			//the virtualScreen.texture has y coordinates flipped due to OpenGL; we re-flip them when drawing to screen.
			DrawTexturePro(virtualScreen.texture, (Rectangle){0,0,virtualWidth, -virtualHeight}, (Rectangle){0,0,screenWidth, screenHeight}, (Vector2){0,0}, 0.0f, WHITE);
		EndDrawing();
    }

	
	// De-Initialization
    CloseWindow();	// Close window and OpenGL context

    return 0;
}


//  let x = 100 * noise(0.005 * frameCount);
//  let y = 100 * noise(0.005 * frameCount + 10000);
//  strokeWeight(5);
//  point(x, y);

// let noiseLevel = 100;
// let noiseScale = 0.005;
// // Scale input coordinate.
// let nt = noiseScale * frameCount;
// // Compute noise value.
// let x = noiseLevel * noise(nt);
// let y = noiseLevel * noise(nt + 10000);
// // Render.
// strokeWeight(5);
// point(x, y);

// let noiseLevel = 100;
// let noiseScale = 0.02;
// // Scale input coordinate.
// let x = frameCount;
// let nx = noiseScale * x;
// // Compute noise value.
// let y = noiseLevel * noise(nx);
// // Render.
// line(x, 0, x, y);

// let noiseLevel = 255;
// let noiseScale = 0.009;
// for (let y = 0; y < height; y += 1) {
//   for (let x = 0; x < width; x += 1) {
//     // Scale input coordinates.
//     let nx = noiseScale * x;
//     let ny = noiseScale * y;
//     let nt = noiseScale * frameCount;
//     // Compute noise value.
//     let c = noiseLevel * noise(nx, ny, nt);
//     // Render.
//     stroke(c);
//     point(x, y);
//   }
// }