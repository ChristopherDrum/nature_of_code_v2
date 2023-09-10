#include "../../processing.h"
#include "raylib.h"
#include "raymath.h"
#include <stdio.h>

//Coordinates and sizes and such need to be in virtual screen pixels
//however, high-res things like text could be appended *after*
//the low-rez render texture is blitted to screen.
const int virtualWidth = 600;
const int virtualHeight = 400;
const float resolutionScale = 2.0;

const float screenWidth = virtualWidth * resolutionScale;
const float screenHeight = virtualHeight * resolutionScale;

const float widthRatio = (float)virtualWidth/screenWidth;
const float heightRatio = (float)virtualHeight/screenHeight;


int main(void) 
{
    // Initialization
    //----------------------------------------------------------------

    InitWindow(screenWidth, screenHeight,
		"Nature of Code, Ch.1 Ex.5, Mouse Vector Magnitude");

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
			DrawLineEx(center, mouse, 3, LIGHTGRAY);
			mouse = Vector2Subtract(mouse, center);
			float mag = Vector2Length(mouse);
			int xOffset = 10.0f + mag;
			DrawLineEx((Vector2){10,10}, (Vector2){xOffset, 10}, 6, RED);
			DrawLine(xOffset, 10, xOffset, 18, RED);
			int textWidth = MeasureText(TextFormat("%.2f", mag), 4);
			DrawRectangle(mag-((float)textWidth/2)-3+10, 17, textWidth+6, 11, RED);
			DrawText(TextFormat("%.2f", mag), mag-((float)textWidth/2)+10 , 18, 4, WHITE);
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
