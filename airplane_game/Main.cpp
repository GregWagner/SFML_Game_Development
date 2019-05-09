#include "Game.h"
#include <iostream>

int main()
{
    try {
        Game game;
        game.run();
    } catch (std::exception e) {
        std::cout << "\nEXCEPtioN: " << e.what() << '\n';
    }
}
