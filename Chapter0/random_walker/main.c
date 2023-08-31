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
		(*w).x++;
		break;
	case 1:
		(*w).x--;
		break;
	case 2:
		(*w).y++;
		break;
	case 3:
		(*w).y--;
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
    const int screenWidth = 800;
    const int screenHeight = 600;

	//If we keep this to nice multiples with actual window size
	//we can draw into a small virtual canvas, then draw that canvas
	//enlarged pixel-perfect to the full window size
	//and get that low-res look. 
	const int virtualWidth = 200;
	const int virtualHeight = 150;

    InitWindow(screenWidth, screenHeight,
		"Nature of Code, Chapter 0, Random Walker");

    SetTargetFPS(60);

	//Coordinates and sizes and such need to be in virtual screen pixels
	//however, high-res things like text could be appended *after*
	//the low-rez render texture is blitted to screen.
	crowd[0] = (Walker){25,25,ORANGE};
	crowd[1] = (Walker){100,75,GREEN};
	crowd[2] = (Walker){175,125,YELLOW};

	//This becomes the "real" canvas we draw to.
	//Normally, ClearBackground is called every frame, but for this project
	//we want to append to the composite image every frame
	//So we can set up our target texture canvas with its base background color
	//just once and draw into that, then blit that to screen in the normal
	//BeginDrawing()/EndDrawing() phase without (necessarily) needing to clear every frame; though we could if we wanted to, I think

	//This is all to avoid a weird flickering/checkerboard pixel pattern that appears when we circumvent Raylib's normal "draw everything fresh every frame" draw cycle. This differs somewhat from Pico-8 and its image persistence and flip() concept.
	RenderTexture2D target = LoadRenderTexture(virtualWidth, virtualHeight);
	BeginTextureMode(target);
	ClearBackground(DARKGRAY);
	EndTextureMode();

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {

		//Raylib really wants a per-frame redraw of everything
		//But we want persistence from frame to frame for the random walker
		//The solution is to draw to a texture and blit that texture every frame
		//This satisfies our persistence needs
		//and keeps Raylib happy with something "new" to blit every frame.
		//So, for us, the target texture is the "real" canvas
		BeginTextureMode(target);
			for (size_t i = 0; i < CROWD_SIZE; i++)
			{
				step(&crowd[i]);
				draw(&crowd[i]);
			}
			DrawCircle(20,120,10,BLUE);
		EndTextureMode();

		
		BeginDrawing();
			//the target.texture has y coordinates flipped due to OpenGL; we re-flip them when drawing to screen.
			// DrawTextureRec(target.texture, (Rectangle){0,0,target.texture.width, -target.texture.height}, (Vector2){0,0}, WHITE);
			DrawTexturePro(target.texture, (Rectangle){0,0,virtualWidth, -virtualHeight}, (Rectangle){0,0,screenWidth, screenHeight}, (Vector2){0,0}, 0.0f, WHITE);
		EndDrawing();
    }

	
	// De-Initialization
    CloseWindow();	// Close window and OpenGL context

    return 0;
}
