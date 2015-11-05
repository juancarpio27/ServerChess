#include <iostream>
#include "game/Game.h"

using namespace std;

int main() {
    Game game;
    game.init();
    return game.execute();
}