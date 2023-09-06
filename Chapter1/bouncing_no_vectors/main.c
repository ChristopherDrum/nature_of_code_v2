#include "../../processing.h"
#include "raylib.h"
#include <stdio.h>

//Coordinates and sizes and such need to be in virtual screen pixels
//however, high-res things like text could be appended *after*
//the low-rez render texture is blitted to screen.
const int virtualWidth = 400;
const int virtualHeight = 300;
const int resolutionScale = 2;

const int screenWidth = virtualWidth * resolutionScale;
const int screenHeight = virtualHeight * resolutionScale;


int main() 
{
    // Initialization
    //----------------------------------------------------------------

    InitWindow(screenWidth, screenHeight,
		"Nature of Code, Ch.x Ex.x, Base Template Project");

    SetTargetFPS(60);

	//This becomes the "real" canvas we draw to.
	//Normally, ClearBackground is called every frame
	//If you want to build a composite image
	//set up the virtualScreen texture  with its base bg color once,
	//draw into that, then blit that the texture to screen in
	//BeginDrawing()/EndDrawing() phase without (necessarily) needing to clear 
	RenderTexture2D virtualScreen = LoadRenderTexture(virtualWidth, virtualHeight);

	float x = 100.0f;
	float y = 100.0f;
	float xSpeed = 2.5f;
	float ySpeed = 2.0f;

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {

		//For low-res drawing, virtualScreen.texture is the "real" canvas
		BeginTextureMode(virtualScreen);
			/* Stick your virtual resolution drawing stuff in here*/
			ClearBackground(DARKGRAY);
			x += xSpeed;
			y += ySpeed;
			if (x > virtualWidth || x < 0)
			{
				xSpeed *= -1;
			}
			if (y > virtualHeight || y < 0)
			{
				ySpeed *= -1;
			}
			DrawCircle(x, y, 10, RED);
		EndTextureMode();

		
		BeginDrawing();
			//virtualScreen.texture has y coordinates flipped due to OpenGL
			//we re-flip them here when drawing the scaled image to screen.
			DrawTexturePro(virtualScreen.texture, (Rectangle){0,0,virtualWidth, -virtualHeight}, (Rectangle){0,0,screenWidth, screenHeight}, (Vector2){0,0}, 0.0f, WHITE);
		EndDrawing();
	}

	
	// De-Initialization
	CloseWindow();	// Close window and OpenGL context

	return(0);
}
