#include "Button.hpp"

Button::Button(float x, float y, float width, float height, string imagePath, string soundPath) {
    this->x = x;
    this->y = y;
    this->width = width;
    this->height = height;

    isPressed = false;

    if (raylib::FileExists(imagePath)){
        image.Load(raylib::Image(imagePath).Resize(width, height));
    }

    if (raylib::FileExists(soundPath)){
        buttonSound.Load(soundPath);
    }
}

void Button::render(){
    
    if (image.IsValid()){
        image.Draw(this->x, this->y, WHITE);
    }

    else {
        raylib::Rectangle(this->x,this->y,this->width,this->height).Draw(RED);
    }

}

void Button::tick(){
    
    if(isPressed){
        pressCounter--;
        if(pressCounter == 0){
            isPressed = false;
            pressCounter = -1;
        }
    }
    
}

void Button::playSound(){
    //If the sound path was correct, and the buttonSound variable has a
    //sound loaded, then play it
    if (buttonSound.IsValid()) {
        buttonSound.Play();
    }
}

void Button::setPressed(raylib::Vector2 mousePosition){
    //If the mouse is inside the button, set the button as pressed
    if (raylib::Rectangle(mousePosition.x, mousePosition.y, this->width, this->height).CheckCollision(raylib::Mouse::GetPosition())) {
        isPressed = true;
        pressCounter = 1; //You may change that pressCounter variable to a higher number
        //If you wish for it to stay pressed for a longer time
    }
}

Button::~Button(){
    UnloadTexture(image);
    UnloadSound(buttonSound);
}