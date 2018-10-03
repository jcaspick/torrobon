#include "Game.h"

void main(int argc, char** argv[]) {
	Game game;
	while (game.GetWindow()->isOpen()) {
		game.Update();
		game.Draw();
	}
}