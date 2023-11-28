#include <iostream>
#include "Engine.h"
#include "Arkanoid/Game.h"

void funkcja() {
	Game game;
	game.game_loop();
}


int main()
{

	Engine e;

	e.ini_grafika();
	e.set_frames(60);
	e.init_display();
	e.ini_bitmap(true);
	e.set_mouse(true);
	e.set_keyboard(true);

	e.run(funkcja);

}
