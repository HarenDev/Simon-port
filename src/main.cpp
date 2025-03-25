/*
Raylib example file.
This is an example main file for a simple raylib project.
Use this as a starting point or replace it with your code.

by Jeffery Myers is marked with CC0 1.0. To view a copy of this license, visit https://creativecommons.org/publicdomain/zero/1.0/

*/

#include "raylib-cpp/raylib-cpp.hpp"
#include "Program.hpp"

#include "resource_dir.h"	// utility header for SearchAndSetResourceDir

int main ()
{
	//Match the openFrameworks version
	SetTargetFPS(100);

	//Initialize audio device to play sound files
	InitAudioDevice();

	// Create the window and OpenGL context & tell the window to use vsync and work on high DPI displays
	raylib::Window window(1024, 768, "Simon");

	// Utility function from resource_dir.h to find the resources folder and set it as the current working directory so we can load from it
	SearchAndSetResourceDir("resources");

	//Initialize the program
	Program simon;
	
	// game loop
	while (!WindowShouldClose())		// run the loop untill the user presses ESCAPE or presses the Close button on the window
	{
		//Check for player input every frame
		simon.CheckInput();

		//Update program logic every frame
		simon.Update();

		BeginDrawing();
		//Draw every frame
		simon.Draw();

		EndDrawing();
	}

	// cleanup
	// unload our texture so it can be cleaned up
	
	CloseAudioDevice();

	// destroy the window and cleanup the OpenGL context
	CloseWindow();
	return 0;
}
