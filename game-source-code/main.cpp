// Kgadile Masemola, Jashna Gurahoo


#include "Game.h"

int main()
{
    defender::Setup::initialize();

    defender::Game game(1280, 800);
    game.run();

    return 0;
}
