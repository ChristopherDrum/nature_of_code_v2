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

const float widthRatio = (float)virtualWidth/screenWidth;
const float heightRatio = (float)virtualHeight/screenHeight;

// Vector2 virtualMousePosition()
// {
// 	Vector2 realMouse = GetMousePosition();
// 	Vector2 virtualMouse = (Vector2){(float)realMouse.x*widthRatio, (float)realMouse.y*heightRatio};
// 	virtualMouse = Vector2Clamp(virtualMouse, (Vector2){0,0}, (Vector2){virtualWidth, virtualHeight});
// }

int main(void) 
{
    // Initialization
    //----------------------------------------------------------------

    InitWindow(screenWidth, screenHeight,
		"Nature of Code, Ch.1 Ex.3, Mouse Vector Subtraction");

    SetTargetFPS(60);

	//This becomes the "real" canvas we draw to.
	//Normally, ClearBackground is called every frame
	//If you want to build a composite image
	//set up the virtualScreen texture  with its base bg color once,
	//draw into that, then blit that the texture to screen in
	//BeginDrawing()/EndDrawing() phase without (necessarily) needing to clear 
	RenderTexture2D virtualScreen = LoadRenderTexture(virtualWidth, virtualHeight);

	SetMouseScale(widthRatio, heightRatio);

	Vector2 center = {.x=(float)virtualWidth/2, .y=(float)virtualHeight/2};

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
		Vector2 mouse = GetMousePosition();

		//For low-res drawing, virtualScreen.texture is the "real" canvas
		BeginTextureMode(virtualScreen);
			ClearBackground(WHITE);
			DrawLineEx(Vector2Zero(), mouse, 3, LIGHTGRAY);
			DrawLineEx(Vector2Zero(), center, 3, LIGHTGRAY);
			mouse = Vector2Subtract(mouse, center);
			Matrix translation = MatrixTranslate((float)virtualWidth/2, (float)virtualHeight/2, 0);
			mouse = Vector2Transform(mouse, translation);
			DrawLineEx(mouse, center, 6, RED);
		EndTextureMode();

		
		BeginDrawing();
			//virtualScreen.texture has y coordinates flipped due to OpenGL
			//we re-flip them here when drawing the scaled image to screen.
			DrawTexturePro(virtualScreen.texture, (Rectangle){0,0,virtualWidth, -virtualHeight}, (Rectangle){0,0,screenWidth, screenHeight}, (Vector2){0,0}, 0.0f, WHITE);
			// DrawFPS(20,20);
		EndDrawing();
	}

	
	// De-Initialization
	CloseWindow();	// Close window and OpenGL context

	return(0);
}
