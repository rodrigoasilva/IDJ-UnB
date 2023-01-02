#ifndef INPUTMANAGER_H 
#define INPUTMANAGER_H 
using namespace std;
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>
#define LEFT_ARROW_KEY    SDLK_LEFT
#define RIGHT_ARROW_KEY   SDLK_RIGHT
#define SPACE_ARROW_KEY   SDLK_SPACE
#define UP_ARROW_KEY      SDLK_UP
#define DOWN_ARROW_KEY    SDLK_DOWN
#define ESCAPE_KEY        SDLK_ESCAPE
#define LEFT_MOUSE_BUTTON SDL_BUTTON_LEFT
#include <unordered_map>

 
class InputManager{
private:
    InputManager();
    ~InputManager();
    bool mouseState[6];
    int mouseUpdate[6];
    bool  quitRequested;
    int updateCounter;
    int mouseX;
    int mouseY;
   std::unordered_map<int, bool> keyState;
   std::unordered_map<int, int> keyUpdate; 
public:

    void Update();
    bool KeyPress(int key);
    bool KeyRelease(int key);
    bool IsKeyDown(int key);
    bool MousePress(int button);
    bool MouseRelease(int button);
    bool IsMouseDown(int button);
    int GetMouseX();
    int GetMouseY();
    bool QuitRequested();
    static InputManager& GetInstance();


 
};
#endif
