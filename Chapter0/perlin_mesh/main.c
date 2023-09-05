#include "../../processing.h"
#include "raylib.h"
#include "raymath.h"
#include <stdio.h>

const int screenWidth = 768;
const int screenHeight = 672;

//PS1 virtual resolution
const int virtualWidth = 256;
const int virtualHeight = 224;
// const int virtualWidth = screenWidth;
// const int virtualHeight = screenHeight;


int main() 
{
    // Initialization
    //----------------------------------------------------------------

    InitWindow(screenWidth, screenHeight,
		"Nature of Code, Ch.0 Ex.10a, Perlin Mesh");

    SetTargetFPS(60);

	RenderTexture2D virtualScreen = LoadRenderTexture(virtualWidth, virtualHeight);

	// Define the camera to look into our 3d world
    Camera camera = { 0 };
    camera.position = (Vector3){ 18.0,21.0,18.0 }; // Camera position
    camera.target = (Vector3){ 0.0f, 0.0f, 0.0f };     // Camera looking at point
    camera.up = (Vector3){ 0.0f, 1.0f, 0.0f };          // Camera up vector (rotation towards target)
    camera.fovy = 45.0f;                                // Camera field-of-view Y
    camera.projection = CAMERA_PERSPECTIVE;                   // Camera mode type

	Image perlinImage = GenImagePerlinNoise(30,30,0,0,1.0f);
	Texture2D perlinTexture = LoadTextureFromImage(perlinImage);
	Mesh perlinMesh = GenMeshHeightmap(perlinImage, (Vector3){16,16,16});
	Model perlinModel = LoadModelFromMesh(perlinMesh);
	perlinModel.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = perlinTexture;

	Mesh waterMesh = GenMeshHeightmap(perlinImage, (Vector3){16,2,16});
	Model waterModel = LoadModelFromMesh(waterMesh);
	waterModel.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = perlinTexture;

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {

		UpdateCamera(&camera, CAMERA_ORBITAL);

		BeginTextureMode(virtualScreen);
			ClearBackground(SKYBLUE);
			BeginMode3D(camera);
				DrawModel(perlinModel, (Vector3){-8,-4,-8}, 1.0, LIGHTGRAY);
				DrawModel(waterModel, (Vector3){-8,-1,-8}, 1.0, SKYBLUE);
				// DrawGrid(20,1.0f);
			EndMode3D();
		EndTextureMode();

		
		BeginDrawing();
			//the virtualScreen.texture has y coordinates flipped due to OpenGL; we re-flip them when drawing to screen.
			DrawTexturePro(virtualScreen.texture, (Rectangle){0,0,virtualWidth, -virtualHeight}, (Rectangle){0,0,screenWidth, screenHeight}, (Vector2){0,0}, 0.0f, WHITE);
		EndDrawing();

    }

	
	// De-Initialization
    CloseWindow();	// Close window and OpenGL context

    return 0;
}
