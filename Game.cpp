#include <cstdlib>
#include <iostream>
#include <ctime>
using namespace std;
#define INCLUDE_SDL_IMAGE
#define INCLUDE_SDL_MIXER
#include "SDL_include.h"
#include "Game.h"
#include "State.h"
#include "Resources.h"
#include "InputManager.h"


Game* Game::instance = nullptr;

Game::Game(string title, int  width  , int  height ) :  dt(0), frameStart(0){


    if(instance==nullptr){
        
        instance = this;

        if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_TIMER) !=0){
            SDL_Log("Unable to initialize SDL: %s", SDL_GetError());
            exit(1);
        }
     

        int flagsIMAGENS = (IMG_INIT_JPG | IMG_INIT_PNG | IMG_INIT_TIF);
        int initIMAGENS = IMG_Init(flagsIMAGENS);
        if ((initIMAGENS & flagsIMAGENS) != flagsIMAGENS) {
            cout << "Unable to IMG_Init: " << IMG_GetError() << endl;
            exit(1);
        }

     
        int flagsMIX = (/*MIX_INIT_MP3 |*/ MIX_INIT_OGG);
        int initMIX = Mix_Init(flagsMIX);
        if ((initMIX & flagsMIX) != flagsMIX) {
            cout << "Unable to Mix_Init: " << Mix_GetError() << endl;
            exit(1);
        }

        if (Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024) != 0) {
            cout << "Unable to Mix_OpenAudio: " << Mix_GetError() << endl;
            exit(1);
        }

      
        if (TTF_Init() != 0) {
            cout << "Unable to TTF_Init: " << TTF_GetError() << endl;
            exit(1);
        }

          window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height,
                                  0);
        if (window == nullptr) {
            cout << "Unable to create window: " << SDL_GetError() << endl;
            exit(1);
        }

        //Cria o renderizador
        renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
        if (renderer == nullptr) {
            cout << "Unable to create renderer: " << SDL_GetError() << endl;
            exit(1);
        }

        //Initialize storedState
        



    }
    else{

          Game::state = new State();

    }
    
 
}

Game::~Game(){



    delete state;

  Resources::ClearImages();
  Resources::ClearMusics();
  Resources::ClearSounds();
    
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    TTF_Quit();
    Mix_CloseAudio();
    Mix_Quit();
    IMG_Quit();
    SDL_Quit();



}



SDL_Renderer *Game::GetRenderer() {
    return renderer;
}





void Game::Run(){
    
    state = new State;
    GetInstance().state->LoadAssets();
    state->Start();
    while(state->QuitRequested() != true){
     CalculateDeltaTime();   
     InputManager::GetInstance().Update();
     state->Update(GetDeltaTime());
     state->Render();
     SDL_RenderPresent(GetInstance().renderer);
     SDL_Delay(33);
     
     
    }
}


State& Game::GetState() {
  return *state;
}
Game& Game::GetInstance() {
  
  if (Game::instance == nullptr) {
    Game::instance = new Game("Rodrigo Andrade da Silva - 15/0147287", 1024, 600);
  }
  return *instance;
}


void Game::CalculateDeltaTime(){

    int ticks = SDL_GetTicks();
    dt = (ticks - frameStart)/1000.;
    frameStart = ticks;

} 

float Game::GetDeltaTime(){

    return dt;
}

