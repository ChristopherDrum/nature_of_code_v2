#include "../../processing.h"
#include "raylib.h"
#include "raymath.h"
#include <stdio.h>


const int virtualWidth = 800;
const int virtualHeight = 600;
const int resolutionScale = 2;

const int screenWidth = virtualWidth * resolutionScale;
const int screenHeight = virtualHeight * resolutionScale;

const float widthRatio = (float)virtualWidth/screenWidth;
const float heightRatio = (float)virtualHeight/screenHeight;

Vector2 helium = {0,-.02};
Vector2 wind = {.01, 0};

typedef struct Balloon
{
	Vector2 position;
	Vector2 velocity;
	Vector2 acceleration;
	float size;
	Color c;
} Balloon ;

Balloon make(float s, Color c)
{
	Vector2 pos = {s*3, virtualHeight - s*3};
	Vector2 vel = Vector2Zero();
	Vector2 acc = Vector2Zero();
	Balloon b = {pos, vel, acc, s, c};
	return b;
}

void update(Balloon *b)
{
	b->velocity = Vector2Add(b->velocity, b->acceleration);

	b->position = Vector2Add(b->position, b->velocity);

	b->acceleration = Vector2Zero();
}

void applyForce(Balloon *b, Vector2 f)
{
	b->acceleration = Vector2Add(b->acceleration, f);
}

void checkEdges(Balloon *b)
{
	if ((b->position.x - b->size) > virtualWidth) 
	{
		b->position.x = virtualWidth - b->size;
		b->velocity.x *= -1;

	} else if (b->position.x < b->size) {
		b->position.x = b->size;
		b->velocity.x *= -1;
	}

	if ((b->position.y + b->size) > virtualHeight) 
	{
		b->position.y = virtualHeight - b->size;
		b->velocity.y *= -1;

	} else if (b->position.y < b->size) {
		b->position.y = b->size;
		b->velocity.y *= -1;
	}
}

void show(Balloon *b)
{
	DrawCircle(b->position.x, b->position.y, b->size, b->c);
}

int main(void) 
{
    // Initialization
    //----------------------------------------------------------------

    InitWindow(screenWidth, screenHeight,
		"Nature of Code, Ch.2 Exercise 1, Helium Balloon");

    SetTargetFPS(60);

	RenderTexture2D virtualScreen = LoadRenderTexture(virtualWidth, virtualHeight);

	//Make sure we get relative pixel coordinates during low-res renders
	SetMouseScale(widthRatio, heightRatio);

	Balloon b = make(10, RED);

	//Maybe not strictly necessary; wipe the screen before persistent drawing occurs. Ignore this if you need per-frame wipes.
	BeginTextureMode(virtualScreen);
	ClearBackground(DARKGRAY);
	EndTextureMode();

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {

		//For low-res drawing, virtualScreen.texture is the "real" canvas
		BeginTextureMode(virtualScreen);
			ClearBackground(DARKGRAY);
			applyForce(&b, helium);
			applyForce(&b, wind);
			update(&b);
			show(&b);
			checkEdges(&b);
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
