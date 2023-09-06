#include "../../processing.h"
#include "raylib.h"
#include "raymath.h"
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

	Vector2 position = {100.0f, 100.0f};
	Vector2 velocity = {2.5f, 2.0f};
	float radius = 10.0f;

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {

		//For low-res drawing, virtualScreen.texture is the "real" canvas
		BeginTextureMode(virtualScreen);
			/* Stick your virtual resolution drawing stuff in here*/
			ClearBackground(WHITE);
			position = Vector2Add(position, velocity);
			if (position.x + radius >= virtualWidth || position.x-radius <= 0)
			{
				velocity.x *= -1;
			}
			if (position.y+radius >= virtualHeight || position.y-radius <= 0)
			{
				velocity.y *= -1;
			}
			DrawCircleV(position, radius+3.0f, DARKPURPLE);
			DrawCircleV(position, radius, PURPLE);
		EndTextureMode();

		
		BeginDrawing();
			//virtualScreen.texture has y coordinates flipped due to OpenGL
			//we re-flip them here when drawing the scaled image to screen.
			DrawTexturePro(virtualScreen.texture, (Rectangle){0,0,virtualWidth, -virtualHeight}, (Rectangle){0,0,screenWidth, screenHeight}, (Vector2){0,0}, 0.0f, WHITE);
			DrawFPS(20,20);
		EndDrawing();
	}

	
	// De-Initialization
	CloseWindow();	// Close window and OpenGL context

	return(0);
}
