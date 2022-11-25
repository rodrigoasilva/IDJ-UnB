#include <cstdlib>
#include <iostream>
#include <ctime>
using namespace std;
#define INCLUDE_SDL_IMAGE
#define INCLUDE_SDL_MIXER
#include "SDL_include.h"
#include "Game.h"
#include "State.h"

Game* Game::instance = nullptr;

Game::Game(string title, int  width  , int  height )
{


    if(instance==nullptr){
        
        instance = this;

        if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_TIMER) !=0){
            SDL_Log("Unable to initialize SDL: %s", SDL_GetError());
            exit(1);
        }
     

        int flagsIMAGENS = (IMG_INIT_JPG | IMG_INIT_PNG | IMG_INIT_TIF);
        int initIMAGENS = IMG_Init(flagsIMAGENS);
        if ((initIMAGENS & flagsIMAGENS) != flagsIMAGENS) {
            cout << "Error in IMG_Init: " << IMG_GetError() << endl;
            exit(1);
        }

     
        int flagsMIX = (/*MIX_INIT_MP3 |*/ MIX_INIT_OGG);
        int initMIX = Mix_Init(flagsMIX);
        if ((initMIX & flagsMIX) != flagsMIX) {
            cout << "Error in Mix_Init: " << Mix_GetError() << endl;
            exit(1);
        }

        if (Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024) != 0) {
            cout << "Error in Mix_OpenAudio: " << Mix_GetError() << endl;
            exit(1);
        }

      
        if (TTF_Init() != 0) {
            cout << "Error in TTF_Init: " << TTF_GetError() << endl;
            exit(1);
        }

          window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height,
                                  0);
        if (window == nullptr) {
            cout << "Error in create window: " << SDL_GetError() << endl;
            exit(1);
        }

        //Cria o renderizador
        renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
        if (renderer == nullptr) {
            cout << "Unable to create renderer: " << SDL_GetError() << endl;
            exit(1);
        }


    }
    else{

        cout <<"A instancia ja existe"<< endl;
        exit(1);
    }
    
 
}

Game::~Game(){



     
    
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    TTF_Quit();
    Mix_CloseAudio();
    Mix_Quit();
    IMG_Quit();
    SDL_Quit();



}

Game &Game::GetInstance() {
    if(instance == nullptr) {
        
        instance = new Game("Rodrigo - 15/0147287",1024 ,600);
        
    }

    return *instance;
}

SDL_Renderer *Game::GetRenderer() {
    return renderer;
}





void Game::Run(){
    
    state = new State;
    while(state->QuitRequested() != true){
     state->Update(45);
     state->Render();
     SDL_RenderPresent(renderer);
     SDL_Delay(33);
     
     
    }
}
