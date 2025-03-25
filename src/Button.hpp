#pragma once

#include <string>
#include "raylib-cpp/raylib-cpp.hpp"

using namespace std;

enum Buttons{
    Green,
    Red,
    Yellow,
    Blue
};

class Button{
    public:
        Button(float x, float y, float width, float height, string imagePath, string soundPath);
        void render();
        void tick();
        void playSound();
        void setPressed(raylib::Vector2 mousePosition);
        bool wasPressed(){return isPressed;}
        int getX(){return x;}
        int getY(){return y;}
        void toggleLightOn(){isLightUp = true;}
        void toggleLightOff(){isLightUp = false;}
        bool GetIsLightUp(){return isLightUp;}
        

    private:
        float x, y, width, height;
        bool isPressed;
        bool isLightUp = false;
        raylib::Texture image;
        raylib::Sound buttonSound;
        string imagePath, soundPath;
        int pressCounter = -1;

};