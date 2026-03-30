#include "game.h"

int main()
{
    Game *game = new Game();

    while (game->isRunning())
    {
        game->run();
    }

    game->close();
    delete game;
}