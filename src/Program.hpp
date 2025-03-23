#pragma once

#include "Button.hpp"
#include <vector>
#include "raylib-cpp/raylib-cpp.hpp"

using namespace std;

class Program {

    enum GameState{
        StartUp,
        PlayingSequence,
        PlayerInput,
        GameOver
    };

    public:
        //Critical functions for this program
        void Init();
        void Update();
        void Draw();

        //Game-specific functions
        void lightOn(Buttons color);
        void lightOff(Buttons color);
        void generateSequence();
        bool checkUserInput(Buttons c);
        void GameReset();
        void startUpSequence(int count);

    private:
        vector<Buttons> Sequence;

        Button *RedButton;
        Button *BlueButton;
        Button *YellowButton;
        Button *GreenButton;

};