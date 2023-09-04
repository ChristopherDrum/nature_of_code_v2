#include "../../processing.h"
#include "raylib.h"
#include "raymath.h"
#include <stdio.h>

const int screenWidth = 800;
const int screenHeight = 600;

const int virtualWidth = 400;
const int virtualHeight = 300;

#define CROWD_SIZE 3

typedef struct {
	int x;
	int y;
	int px;
	int py;
	float tx;
	float ty;
	Color c;
} Walker;

Walker crowd[CROWD_SIZE];

void step(Walker *w)
{
	float nx = noise(w->tx, 0, 0);
	float ny = noise(w->ty, 0, 0);
	
	w->x = Remap(nx, 0.0, 1.0, 0.0, virtualWidth);
	w->y = Remap(ny, 0.0, 1.0, 0.0, virtualHeight);
	w->tx += 0.05;
	w->ty += 0.05;
}

void draw(Walker *w)
{
	// DrawPixel(w->x, w->y, w->c);
	DrawLineBezier((Vector2){w->px, w->py}, (Vector2){w->x, w->y},2, w->c);
	w->px = w->x;
	w->py = w->y;
}

int main() 
{
    // Initialization
    //----------------------------------------------------------------

    InitWindow(screenWidth, screenHeight,
		"Nature of Code, Ch.0 Ex.6, Perlin Noise Walker");

    SetTargetFPS(60);

	//Coordinates and sizes and such need to be in virtual screen pixels
	//however, high-res things like text could be appended *after*
	//the low-rez render texture is blitted to screen.
	crowd[0] = (Walker){25,25,25,25,0.0,2000.0,ORANGE};
	crowd[1] = (Walker){100,75,100,75,1000.0,6000.0,GREEN};
	crowd[2] = (Walker){175,125,175,125,5000.0,10000.0,YELLOW};

	//This becomes the "real" canvas we draw to.
	//Normally, ClearBackground is called every frame, but for this project
	//we want to append to the composite image every frame
	//So we can set up our virtualScreen texture canvas with its base bg color
	//just once and draw into that, then blit that to screen in the normal
	//BeginDrawing()/EndDrawing() phase without (necessarily) needing to clear every frame; though we could if we wanted to, I think
	RenderTexture2D virtualScreen = LoadRenderTexture(virtualWidth, virtualHeight);

	//This is all to avoid a weird flickering/checkerboard pixel pattern that appears when we circumvent Raylib's normal "draw everything fresh every frame" draw cycle. This differs somewhat from Pico-8 and its image persistence and flip() concept.
	BeginTextureMode(virtualScreen);
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
		//So, for us, the virtualScreen texture is the "real" canvas
		BeginTextureMode(virtualScreen);
			for (size_t i = 0; i < CROWD_SIZE; i++)
			{
				step(&crowd[i]);
				draw(&crowd[i]);
			}
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
