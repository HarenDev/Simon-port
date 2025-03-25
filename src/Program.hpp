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

        raylib::Texture background;
        raylib::Texture redLight;
		raylib::Texture blueLight;
		raylib::Texture yellowLight;
		raylib::Texture greenLight;
		raylib::Texture logo;
		raylib::Texture logoLight;
		raylib::Texture startUpScreen;
		raylib::Texture gameOverScreen;

        //Few variables we'll need
        raylib::Music backgroundMusic;
		int sequenceLimit = 1;
		int userIndex = 1;
		int showingSequenceDuration = 0;
		int lightDisplayDuration = -1;
		Buttons color;
		GameState gameState;
		bool logoIsReady = false;
		int logoCounter = 0;
		bool idle = true;

};