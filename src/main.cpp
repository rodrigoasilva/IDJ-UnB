#include <stdio.h>
#include <stdlib.h>
#include "Game.h"

int main (int argc, char** argv) {

    Game::GetInstance().Run();
    return 0;
}


