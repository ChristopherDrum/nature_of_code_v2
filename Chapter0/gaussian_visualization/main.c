#include "../../processing.h"
#include "raylib.h"
// #include <stdio.h>

int main() 
{
	srand(time(NULL));

    // Initialization
    //--------------------------------------------------------------------------
    const int screenWidth = 400;
    const int screenHeight = 400;

	const int virtualWidth = 400;
	const int virtualHeight = 400;

    InitWindow(screenWidth, screenHeight,
		"Nature of Code, Chapter 0, Gaussian Distribution");

    SetTargetFPS(60);

	//The "real" canvas we draw to.
	RenderTexture2D virtualScreen = LoadRenderTexture(virtualWidth, virtualHeight);
	BeginTextureMode(virtualScreen);
	ClearBackground(LIGHTGRAY);
	EndTextureMode();

	Color c = {0, 0, 0, 25};

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {

		//Raylib really wants a per-frame redraw of everything
		//But we want persistence from frame to frame for the random walker
		//The solution is to draw to a texture and blit that texture every frame
		//This satisfies our persistence needs
		//and keeps Raylib happy with something "new" to blit every frame.
		//So, for us, the virtualScreen texture is the "real" canvas
		BeginTextureMode(virtualScreen);
			int x1 = GetRandomValue(0, screenWidth);
			int y1 = 25;
			DrawCircle(x1, y1, 5, c);

			int x2 = randomGaussian(screenWidth/2, 1);
			int y2 = 50;
			DrawCircle(x2, y2, 5, c);

			int x3 = randomGaussian(screenWidth/2, 30);
			int y3 = 75;
			DrawCircle(x3, y3, 5, c);

		EndTextureMode();

		
		BeginDrawing();
			//virtualScreen.texture has flipped-y due to OpenGL; flip it back
			DrawTexturePro(virtualScreen.texture, (Rectangle){0,0,virtualWidth, -virtualHeight}, (Rectangle){0,0,screenWidth, screenHeight}, (Vector2){0,0}, 0.0f, WHITE);
		EndDrawing();
    }

	
	// De-Initialization
    CloseWindow();	// Close window and OpenGL context

    return 0;
}
