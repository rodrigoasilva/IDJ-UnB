/*
 * oi.cpp
 *
 *  Created on: 11 de jun. de 2022
 *      Author: gomes
 */
#include <stdio.h>
#include <stdlib.h>
#include "Game.h"

int main (int argc, char** argv) {

    /* Inicializa todas as bibliotecas */
    Game::GetInstance().Run();
    return 0;
}


