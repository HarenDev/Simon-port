#include "Button.hpp"

Button::Button(float x, float y, float width, float height, string imagePath, string soundPath) {
    this->x = x;
    this->y = y;
    this->width = width;
    this->height = height;

    isPressed = false;

    image.Load(imagePath);
    buttonSound.Load(soundPath);
}

void Button::render(){
    
    if (image.IsValid()){
        image.Draw(x, y, )
    }

}

void Button::tick(){

}

void playSound(){

}

void setPressed(int x, int y){
}