#include "../../processing.h"
#include "raylib.h"
#include "raymath.h"
#include <corecrt.h>
#include <stdio.h>

const int virtualWidth = 800;
const int virtualHeight = 600;
const int resolutionScale = 2;

const int screenWidth = virtualWidth * resolutionScale;
const int screenHeight = virtualHeight * resolutionScale;

const float widthRatio = (float)virtualWidth/screenWidth;
const float heightRatio = (float)virtualHeight/screenHeight;


typedef struct Mover
{
	Vector2 position;
	Vector2 velocity;
	Vector2 acceleration;
	float topSpeed;
	Color c;
} Mover;

Mover make(Color c)
{
	Vector2 pos = {(float)virtualWidth/2, (float)virtualHeight/2};
	Vector2 vel = Vector2Zero();
	Vector2 acc = Vector2Zero();
	float   top = 6.0f;
	if (c.a == 0) c = DARKGREEN;
	Mover m = {pos, vel, acc, top, c};
	return m;
}

void update(Mover *m)
{
	Vector2 mouseVec = Vector2Subtract(GetMousePosition(), m->position);
	float distance = Vector2Length(mouseVec);
	float gravity = Remap(distance, 0.0f, 800.0f, 0.3f, 0.01f);
	Vector2 newAcc = Vector2SetLength(mouseVec, gravity);
	
	m->velocity = Vector2Add(m->velocity, newAcc);
	m->velocity = Vector2ClampValue(m->velocity, 0.0f, m->topSpeed);
	m->position = Vector2Add(m->position, m->velocity);
}

void show(Mover *m)
{
	DrawCircle(m->position.x, m->position.y, 10.0f, m->c);
}

void checkEdges(Mover *m)
{
	if (m->position.x > virtualWidth) 
	{
		m->position.x = 0;
	} else if (m->position.x < 0) {
		m->position.x = virtualWidth;
	}

	if (m->position.y > virtualHeight) 
	{
		m->position.y = 0;
	} else if (m->position.y < 0) {
		m->position.y = virtualHeight;
	}
}

int main(void) 
{
    // Initialization
    //----------------------------------------------------------------

    InitWindow(screenWidth, screenHeight,
		"Nature of Code, Ch.1 Exercise 8, Fake Gravity");

    SetTargetFPS(60);

	RenderTexture2D virtualScreen = LoadRenderTexture(virtualWidth, virtualHeight);

	SetMouseScale(widthRatio, heightRatio);

	Mover a = make(BLUE);
	a.acceleration = (Vector2){-0.001, 0.01};

	BeginTextureMode(virtualScreen);
		ClearBackground(RAYWHITE);
	EndTextureMode();


    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
		BeginTextureMode(virtualScreen);
			ClearBackground(Fade(RAYWHITE, 0.3f)); //fake trail effect
				update(&a);
				checkEdges(&a);
				show(&a);
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
