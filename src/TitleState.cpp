#include "TitleState.h"
#include "Sprite.h"
#include "StageState.h"
#include "InputManager.h"
#include <PeriodicEvent.h>
#include "Game.h"
#include "Camera.h"
#include "Text.h"

TitleState::TitleState() : State() {
    auto titleGO(new GameObject);
    titleGO->AddComponent(new Sprite(*titleGO, "img/title.jpg"));
    AddObject(titleGO);

     auto fontGO(new GameObject);
    Text *text = new Text(*fontGO, "font/Call me maybe.ttf", 60, Text::TextStyle::BLENDED, "Press space to continue...", {0, 0, 0, 255});
    fontGO->AddComponent(text);
    Rect &fontBox = fontGO->box;
    fontBox.x = 1024/2 - fontBox.w/2;
    fontBox.y = 600 - fontBox.h;

    fontGO->AddComponent(new PeriodicEvent(*fontGO, 0.4, [text] {
        auto alpha = (text->GetColor().a != 0) ? 0 : 255;
        text->setColor({0, 0, 0, (Uint8)alpha});
    }));

    AddObject(fontGO);

}

TitleState::~TitleState() {

}

void TitleState::LoadAssets() {

}

void TitleState::Update(float dt) {
    

    UpdateArray(dt);

    quitRequested = InputManager::GetInstance().QuitRequested() || InputManager::GetInstance().KeyPress(ESCAPE_KEY);
    if (InputManager::GetInstance().KeyPress(SDLK_SPACE)) {
        Game::GetInstance().Push(new StageState());
    }
}

void TitleState::Render() {
    RenderArray();
}

void TitleState::Start() {
    StartArray();
}

void TitleState::Pause() {

}

void TitleState::Resume() {
    Camera::pos = Vec2(0, 0);
}