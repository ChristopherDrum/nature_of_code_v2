#include "../../processing.h"
#include "raylib.h"
#include "raymath.h"
#include <stdio.h>

//Coordinates and sizes and such need to be in virtual screen pixels
//however, high-res things like text could be appended *after*
//the low-rez render texture is blitted to screen.
const int virtualWidth = 800;
const int virtualHeight = 600;
const int resolutionScale = 1;

const int screenWidth = virtualWidth * resolutionScale;
const int screenHeight = virtualHeight * resolutionScale;


int main(void) 
{
	// Initialization
    //----------------------------------------------------------------

    InitWindow(screenWidth, screenHeight,
		"Nature of Code, Ch.1 Exercise 3, Bouncing Ball w/Vectors 3D");

    SetTargetFPS(60);

	//This becomes the "real" canvas we draw to.
	//Normally, ClearBackground is called every frame
	//If you want to build a composite image
	//set up the virtualScreen texture  with its base bg color once,
	//draw into that, then blit that the texture to screen in
	//BeginDrawing()/EndDrawing() phase without (necessarily) needing to clear 
	RenderTexture2D virtualScreen = LoadRenderTexture(virtualWidth, virtualHeight);

	// Define the camera to look into our 3d world
    Camera camera = { 0 };
    camera.position = (Vector3){ 18.0,21.0,18.0 }; // Camera position
    camera.target = (Vector3){ 0.0f, 0.0f, 0.0f };     // Camera looking at point
    camera.up = (Vector3){ 0.0f, 1.0f, 0.0f };          // Camera up vector (rotation towards target)
    camera.fovy = 45.0f;                                // Camera field-of-view Y
    camera.projection = CAMERA_PERSPECTIVE;                   // Camera mode type

	Vector3 position = {2.0f, 2.0f, 2.0f};
	Vector3 velocity = {0.2f, 0.3f, 0.6f};
	float radius = 2.0f;

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {

		//For low-res drawing, virtualScreen.texture is the "real" canvas
		BeginTextureMode(virtualScreen);
			/* Stick your virtual resolution drawing stuff in here*/
			ClearBackground(WHITE);
			position = Vector3Add(position, velocity);
			if (fabs(position.x) >= 10)
			{
				velocity.x *= -1;
			}
			if (fabs(position.y) >= 10)
			{
				velocity.y *= -1;
			}
			if (fabs(position.z) >= 10)
			{
				velocity.z *= -1;
			}
			BeginMode3D(camera);
				//draw order is important!
				DrawGrid(10,2);
				DrawCubeWires((Vector3){0,0,0},20,20,20, DARKBLUE);
				DrawSphere(position, radius, RED);
				//note use of Fade() here to get transparency on the cube
				DrawCube((Vector3){0,0,0},20,20,20, Fade(BLUE, 0.2f));
			EndMode3D();
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
