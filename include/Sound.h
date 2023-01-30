#ifndef SOUND_H 
#define SOUND_H 
#include <cstdlib>
#include <iostream>
#include <ctime>
using namespace std;
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>
#include "Component.h"


 
class Sound : public Component{
private:
    shared_ptr<Mix_Chunk> chunk;
    int channel;
 
public:
    explicit Sound(GameObject& associated);
    Sound(GameObject& associated , string file);
    ~Sound() override;
    void Play(int times=1);
    void Stop();
    void Open(string file);
    bool IsOpen();
    void Update(float dt);
    void Render() override;
    bool Is(string type);
    bool GetIsPlaying();


};
#endif
