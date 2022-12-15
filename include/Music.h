#ifndef MUSIC_H 
#define MUSIC_H 
#include <cstdlib>
#include <iostream>
#include <ctime>
#include "SDL_include.h"
#include "Game.h"



using namespace std;


class Music
{
private:
    Mix_Music* music;
    
public:
    Music();
    explicit Music(string file);
    ~Music();
    void Play( int times  =  -1);
    void Stop( int msToStop  = 1500);
    void Render(int x , int y);
    bool IsOpen();
    void Open(string file);
    void Volume(int volume);

};
#endif