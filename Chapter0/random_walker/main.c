#include "raylib.h"
#include <stdio.h>

#define CROWD_SIZE 3

typedef struct {
	int x;
	int y;
	Color c;
} Walker;

Walker crowd[CROWD_SIZE];

void step(Walker *w)
{
	int ran = GetRandomValue(0, 3);
	switch (ran)
	{
	case 0:
		w->x++;
		break;
	case 1:
		w->x--;
		break;
	case 2:
		w->y++;
		break;
	case 3:
		w->y--;
		break;
	}
}

void draw(Walker *w)
{
	DrawPixel(w->x, w->y, w->c);
}

int main() 
{
    // Initialization
    //--------------------------------------------------------------------------
    const int screenWidth = 600;
    const int screenHeight = 400;

    InitWindow(screenWidth, screenHeight,
		"Nature of Code, Chapter 0, Random Walker");

    SetTargetFPS(60);

	crowd[0] = (Walker){screenWidth/4,screenHeight/4,RED};
	crowd[1] = (Walker){screenWidth/2,screenHeight/2,GREEN};
	crowd[2] = (Walker){screenWidth*.75,screenHeight*.75,BLUE};

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
		for (size_t i = 0; i < CROWD_SIZE; i++)
		{
			step(&crowd[i]);
		}
		
		
		BeginDrawing();
			for (size_t i = 0; i < CROWD_SIZE; i++)
			{
				draw(&crowd[i]);
			}
			
		EndDrawing();
    }

	
	// De-Initialization
    CloseWindow();	// Close window and OpenGL context

    return 0;
}
