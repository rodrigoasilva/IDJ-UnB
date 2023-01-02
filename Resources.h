#ifndef RESOURCES_H 
#define RESOURCES_H 
#include <cstdlib>
#include <iostream>
#include <ctime>
using namespace std;
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>
#include <unordered_map>

class Resources{
private:
    static unordered_map<string, SDL_Texture*> imageTable;
    static unordered_map<string, Mix_Music*>   musicTable;
    static unordered_map<string, Mix_Chunk*> soundTable;
    
public:
    static SDL_Texture* GetImage(string file);
    static void ClearImages();
    static Mix_Music* GetMusic(string file);
    static void ClearMusics();
    static Mix_Chunk* GetSound(string file);
    static void ClearSounds();

};
#endif