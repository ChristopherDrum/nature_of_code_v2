#include "../../processing.h"
#include "raylib.h"
#include "raymath.h"

Vector2 realMouse;
Vector2 virtualMouse;
Color c = BLUE;
int spread = 5;

int main() 
{
	srand(time(NULL));

    // Initialization
    //--------------------------------------------------------------------------
    const int screenWidth = 1024;
    const int screenHeight = 1024;

	const int virtualWidth = 400;
	const int virtualHeight = 400;

	const float widthRatio = (float)virtualWidth/screenWidth;
	const float heightRatio = (float)virtualHeight/screenHeight;


    InitWindow(screenWidth, screenHeight,
		"Nature of Code, Ch.0 Exercise 1.4, Paint Splatter");

    SetTargetFPS(60);

	//The "real" canvas we draw to.
	RenderTexture2D virtualScreen = LoadRenderTexture(virtualWidth, virtualHeight);
	BeginTextureMode(virtualScreen);
	ClearBackground(WHITE);
	EndTextureMode();

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {

		realMouse = GetMousePosition();
		virtualMouse = (Vector2){(float)realMouse.x*widthRatio, (float)realMouse.y*heightRatio};
		virtualMouse = Vector2Clamp(virtualMouse, (Vector2){0,0}, (Vector2){virtualWidth, virtualHeight});

		//Raylib really wants a per-frame redraw of everything
		//But we want persistence from frame to frame for the random walker
		//The solution is to draw to a texture and blit that texture every frame
		//This satisfies our persistence needs
		//and keeps Raylib happy with something "new" to blit every frame.
		//So, for us, the virtualScreen texture is the "real" canvas

		int key = GetCharPressed();
		bool shouldClear = false;
		switch (key)
		{
		case '1':
			printf("1 pressed\n");
			c = BLUE;
			break;
		case '2':
			c = ORANGE;
			break;
		case '3':
			c = RED;
			break;
		case '4':
			c = YELLOW;
			break;
		case 'c':
			shouldClear = true;
			break;
		}

		bool isPainting = IsMouseButtonDown(0);

		BeginTextureMode(virtualScreen);
			if (shouldClear) ClearBackground(WHITE);

			if (isPainting)
			{
				for (size_t i = 0; i < 12; i++)
				{
					float x = randomGaussian(virtualMouse.x, spread);
					float y = randomGaussian(virtualMouse.y, spread);
					int rad = randomGaussian(3,3);
					float r = randomGaussian(c.r, .5);
					float g = randomGaussian(c.g, .5);
					float b = randomGaussian(c.b, .5);
					float a = GetRandomValue(20, 180);
					DrawCircle(x,y,rad,(Color){r,g,b,a});
				}
			}
			DrawRectangle(0,0,10,10,c);
		EndTextureMode();
		shouldClear = false;
		
		BeginDrawing();
			//virtualScreen.texture has flipped-y due to OpenGL; flip it back
			DrawTexturePro(virtualScreen.texture, (Rectangle){0,0,virtualWidth, -virtualHeight}, (Rectangle){0,0,screenWidth, screenHeight}, (Vector2){0,0}, 0.0f, WHITE);
		EndDrawing();
    }

	
	// De-Initialization
    CloseWindow();	// Close window and OpenGL context

    return 0;
}
