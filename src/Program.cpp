#include "Program.hpp"

Program::Program(){
    RedButton = new Button(GetScreenWidth()/2-20,GetScreenHeight()/2-260,302,239,"images/BlueButton.png","sounds/YellowButton.mp3");
	BlueButton = new Button(GetScreenWidth()/2+35,GetScreenHeight()/2-10,236,290,"images/Rebutton.mp4","sounds/YellowButton.mp3");
	YellowButton = new Button(GetScreenWidth()/2-260,GetScreenHeight()/2+40,287,239,"images/RedButton.png","sounds/YellowButton.mp3");
	GreenButton = new Button(GetScreenWidth()/2-260,GetScreenHeight()/2-260,234,294,"images/RedButton.png","sounds/YellowButton.mp3");

    //Load the glowing images for the buttons
	//We use raylib::Image in order to resize it correctly before Loading as a Texture
	redLight.Load(raylib::Image("images/BlueLight.png").Resize(376, 329));
    blueLight.Load(raylib::Image("images/GreenLight.png").Resize(309, 376));
    yellowLight.Load(raylib::Image("images/YellowLight.png").Resize(374, 318));
    greenLight.Load(raylib::Image("images/RedLight.png").Resize(315, 356));

	//Load other images
	logo.Load(raylib::Image("images/Logo.png").Resize(330,330));
	logoLight.Load(raylib::Image("images/LogoLight.png").Resize(330,330));
	startUpScreen.Load(raylib::Image("images/StartScreen.png").Resize(1024,768));
	gameOverScreen.Load(raylib::Image("images/GameOverScreen.png").Resize(1024,768));
    background.Load(raylib::Image::GradientRadial(GetScreenWidth(), GetScreenHeight(), 0.5f, Color{50, 50, 50, 255}, Color{15, 15, 15, 255}));

    //Load Music
	backgroundMusic.Load("sounds/BackgroundMusic.mp3");
	backgroundMusic.SetLooping(true);
	backgroundMusic.Play();
    
}

void Program::Update(){
	//Needed for continuous audio playback in Raylib
	backgroundMusic.Update();

    //We will tick the buttons, aka constantly update them
	//while expecting input from the user to see if anything changed
	if(gameState == PlayerInput){
		RedButton->tick();
		BlueButton->tick();
		YellowButton->tick();
		GreenButton->tick();

		//If the amount of user input equals the sequence limit
		//that means the user has successfully completed the whole
		//sequence and we can proceed with the next level
		if(userIndex == sequenceLimit){
			generateSequence();
			userIndex = 0;
			showingSequenceDuration = 0;
			gameState = PlayingSequence;
		}
	}

	//This will take care of turning on the lights after a few
	//ticks so that they dont stay turned on forever or too long
	if(lightDisplayDuration > 0){
		lightDisplayDuration--;
		if(lightDisplayDuration <= 0){
			lightOff(Red);
			lightOff(Blue);
			lightOff(Yellow);
			lightOff(Green);
		}
	}
}

void Program::Draw(){
    background.Draw();

    RedButton->render();
    BlueButton->render();
    YellowButton->render();
    GreenButton->render();

    //This whole if statement will take care of showing
	//the sequence to the user before accepting any input
	if(gameState == PlayingSequence){
		showingSequenceDuration++;
		if(showingSequenceDuration == 120){
			color = Sequence[userIndex];
			lightOn(color);
			lightDisplayDuration = 30;
		}
	
		if(showingSequenceDuration == 140){
			lightOff(color);
			showingSequenceDuration = 60;
			userIndex++;
		}
		if(userIndex == sequenceLimit){
			lightOff(color);
			userIndex = 0;
			gameState = PlayerInput;
		}
	}

    //StartUP (You dont need to pay much attention to this)
	//(This is only to create a animation effect at the start of the game)
	if(gameState == StartUp){
		showingSequenceDuration++;
		startUpSequence(showingSequenceDuration);
	}

	//If the statements to see see if the buttons should be lit up
	//If they are then we will draw the glowing images on top of them
	if (RedButton->GetIsLightUp()) {
		redLight.Draw(GetScreenWidth()/2-60, GetScreenHeight()/2-305);
	}
	if (BlueButton->GetIsLightUp()) {
		blueLight.Draw(GetScreenWidth()/2+5, GetScreenHeight()/2-60);
	} 
	if (YellowButton->GetIsLightUp()) {
		yellowLight.Draw(GetScreenWidth()/2-300, GetScreenHeight()/2+5);
	} 
	if (GreenButton->GetIsLightUp()) {
		greenLight.Draw(GetScreenWidth()/2-307, GetScreenHeight()/2-295);
	}

	//Part of the Start Up
	if(logoIsReady){
		logo.Draw(GetScreenWidth()/2-160,GetScreenHeight()/2-150);
	}

	//Draw the game over screen
	if(gameState == GameOver){
		gameOverScreen.Draw(0,0);
	}

	//This will draw the "Press to Start" screen at the beginning
	else if(!idle && gameState == StartUp){
		startUpScreen.Draw(20,0);
	}
}

//--------------------------------------------------------------
void Program::GameReset(){
	//This function will reset the game to its initial state
	lightOff(Red);
	lightOff(Blue);
	lightOff(Yellow);
	lightOff(Green);
	Sequence.clear();
	generateSequence();
	userIndex = 0;
	gameState = PlayingSequence;
	showingSequenceDuration = 0;
}

//--------------------------------------------------------------
void Program::generateSequence(){

	//This function will generate a random number between 0 and 3
	int random = GetRandomValue(0,3);
	
	//Depending on the random number, we will add a button to the sequence
	if(random == 0){
		Sequence.push_back(Red);
	}
	else if(random == 3){
		Sequence.push_back(Yellow);
	}

	//We will adjust the sequence limit to the new size of the Sequence list
	sequenceLimit = Sequence.size();
}
//--------------------------------------------------------------
bool Program::checkPlayerInput(Buttons input){
	//This function will varify if the user input matches the color
	//of the sequence at the current index
	if(Sequence[userIndex] == input){
		return true;
	}
	else{
		return false;
	}
}
//--------------------------------------------------------------
void Program::lightOn(Buttons color){
	//This function will take care of toggling the "isLightUp" variable to
	//true for the button that matches the color, and also play the button sound
	if(color == Red){
		RedButton->toggleLightOn();
	}
	else if(color == Blue){
		BlueButton->toggleLightOn();
	}
	else if(color == Yellow){
		YellowButton->toggleLightOn();
        YellowButton->playSound();
	}
	else if(color == Green){
		GreenButton->toggleLightOn();
	}
}

//--------------------------------------------------------------
void Program::lightOff(Buttons color){
	//This function will take care of toggling the "isLightUp" variable to false
	if(color == Red){
		RedButton->toggleLightOff();
	}
	else if(color == Blue){
		BlueButton->toggleLightOff();
	}
	else if(color == Yellow){
		YellowButton->toggleLightOff();
	}
	else if(color == Green){
		GreenButton->toggleLightOff();
	}
}


void Program::keyPressed(){
	//As long as we're not in Idle OR the gameState is GameOver;
	//AND we press the SPACEBAR, we will reset the game
	if((!idle || gameState == GameOver) && IsKeyPressed(KEY_SPACE)){
		GameReset();
	}
}


void Program::mousePressed(){
	//If we're not in Idle and the gameState equals PlayerInput,
	//We will pay attention to the mousePresses from the user
	if(!idle && gameState == PlayerInput && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){
		//We mark the pressed button as "pressed"
		RedButton->setPressed();
		BlueButton->setPressed();
		YellowButton->setPressed();
		GreenButton->setPressed();

		//We check which button got pressed
		if(RedButton->wasPressed()){
			color = Red;
		}
		else if(BlueButton->wasPressed()){
			color = Blue;
		}
		else if(YellowButton->wasPressed()){
			color = Yellow;
		}
		else if(GreenButton->wasPressed()){
			color = Green;
		}
		//Light up the pressed button for a few ticks
		lightOn(color);
		lightDisplayDuration = 15;
			//If the user input is correct, we can continue checking
			if(checkPlayerInput(color)){
				userIndex++;
			}
			//If not, then we will terminate the game by 
			//putting it in the GameOver state.
			else{
				gameState = GameOver;
			}
	}
}

void Program::CheckInput(){
	//We group the keyboard and mouse methods here to simplify checking
	keyPressed();
	mousePressed();
}

//You may honestly ignore this function, shouldnt be something you need
//to change or anything. It's only for the start up animation. But ofc,
//If you wish to make something out of it or make it better, be my guest.
void Program::startUpSequence(int count){
	
	if(count < 200){
		GreenButton->toggleLightOn();
	}
	else if(count >= 200 && count < 260){
		GreenButton->toggleLightOff();
		RedButton->toggleLightOn();
	}
	else if(count >= 260 && count < 320){
		RedButton->toggleLightOff();
		BlueButton->toggleLightOn();
	}
	else if(count >= 320 && count < 380){
		BlueButton->toggleLightOff();
		YellowButton->toggleLightOn();
	}
	else if(count >= 380 && count < 440){
		YellowButton->toggleLightOff();
	}
	else if(count >= 440 && count < 500){
		GreenButton->toggleLightOn();
		RedButton->toggleLightOn();
		YellowButton->toggleLightOn();
		BlueButton->toggleLightOn();
	}
	else if(count >= 500 && count < 560){
		GreenButton->toggleLightOff();
		RedButton->toggleLightOff();
		YellowButton->toggleLightOff();
		BlueButton->toggleLightOff();
	}
	else if(count >= 560){
		showingSequenceDuration = 400;
	}

	//Logo Drawing
	if(logoIsReady && logoCounter > 0){
		logoCounter--;
		//We use the logoCounter var to increase the opacity in the texture
		logoLight.Draw(GetScreenWidth()/2-160,GetScreenHeight()/2-150, Color{255,255,255,(unsigned char)logoCounter});
	}
	if((count > 375) && !logoIsReady){
		logoCounter++;
		logoLight.Draw(GetScreenWidth()/2-160,GetScreenHeight()/2-150, Color{255,255,255,(unsigned char)logoCounter});
		logo.Draw(GetScreenWidth()/2-160,GetScreenHeight()/2-150, Color{255,255,255,(unsigned char)logoCounter});
	}
	if(logoCounter >=255){
		logoIsReady = true;
		idle = false;
	}
}