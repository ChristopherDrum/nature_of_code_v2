#include "raylib.h"
#include <stdio.h>

#define CROWD_SIZE 3

typedef struct {
	int x;
	int y;
	Color c;
} Walker;

Walker crowd[CROWD_SIZE];
Vector2 realMouse;
Vector2 virtualMouse;

void step(Walker *w)
{
	int ran = GetRandomValue(1,8);
	switch (ran)
	{
	case 1:
		(*w).x++;
		break;
	case 2:
		(*w).x--;
		break;
	case 3:
		(*w).y++;
		break;
	case 4:
		(*w).y--;
		break;
	default:
		//steer toward mouse
		if (w->x < virtualMouse.x) w->x++;
		if (w->x > virtualMouse.x) w->x--;
		if (w->y < virtualMouse.y) w->y++;
		if (w->y > virtualMouse.y) w->y--;
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

	//remember: casting is super important, even if the receiving
	//variable is a float, if the division was by two ints you'll get an int
	//I think this is called "type promotion" to force the system to do
	//math in specific precisions
	const float widthRatio = (float)virtualWidth/screenWidth;
	const float heightRatio = (float)virtualHeight/screenHeight;

    InitWindow(screenWidth, screenHeight,
		"Nature of Code, Ch 0, Ex 1.3: Walker Tends Toward Mouse");

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

		realMouse = GetMousePosition();
		virtualMouse = (Vector2){(float)realMouse.x*widthRatio, (float)realMouse.y*heightRatio};

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
