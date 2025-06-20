#include "GameEngine.h"
GameEngine game;
int main()
{
	InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Game");
	SetTargetFPS(60);

	game.startUp();
	while (!WindowShouldClose())
	{
		game.update();
		BeginDrawing();
		game.render();
		EndDrawing();
	}
	game.shutdown();
	CloseWindow();

}