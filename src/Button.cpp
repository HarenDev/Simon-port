#include "Button.hpp"

Button::Button(float x, float y, float width, float height, string imagePath, string soundPath) {
    this->x = x;
    this->y = y;
    this->width = width;
    this->height = height;

    isPressed = false;

    //If the image path is correct, then it will load the image
    if (raylib::FileExists(imagePath)){
        image.Load(raylib::Image(imagePath).Resize(width, height));
    }

    //If the sound path is correct, then it will load the sound
    if (raylib::FileExists(soundPath)){
        buttonSound.Load(soundPath);
    }
}

void Button::render(){
    //If the image variable was able to load something, draw that image
    if (image.IsValid()){
        image.Draw(this->x, this->y, WHITE);
    }
    //If the image variable was not able to load something, draw a rectangle in its place
    else {
        raylib::Rectangle(this->x,this->y,this->width,this->height).Draw(RED);
    }

}

void Button::tick(){
    //We will call this function every single frame in Program::Update();
    //and in every call, if isPressed is true then we will decrease 
    //the pressCounter variable 1 by 1 until pressCounter reaches 0, 
    //we will then set the buttin as not pressed
    if(isPressed){
        pressCounter--;
        if(pressCounter == 0){
            isPressed = false;
            pressCounter = -1;
        }
    }
    //FUNFACT; each called frame called can also be known as a "tick"
    //And 60 ticks is the same as 1 second. (That's why they call it 60fps in games)
    //Might differ a bit from one computer to another, but it's a good rule of thumb
}

void Button::playSound(){
    //If the buttonSound variable has a sound loaded, then play it
    if (buttonSound.IsValid()) {
        buttonSound.Play();
    }
}

void Button::setPressed(){
    //If the mouse is inside the button, set the button as pressed
    if (CheckCollisionPointRec(GetMousePosition(),{this->x,this->y,this->width,this->height})) {
        isPressed = true;
        pressCounter = 1; //You may change that pressCounter variable to a higher number
        //If you wish for it to stay pressed for a longer time
    }
}

Button::~Button(){
    //Unload the button resources once it goes out of scope
    UnloadTexture(image);
    UnloadSound(buttonSound);
}