#include <iostream>
#include <string>
#include <windows.h>
#include <stdlib.h>
#include <time.h>
#include <thread>
#include <cstring>

#include "setConsole.h"
#include "defs.h"
#include "globals.h"
#include "mainMenu.h"

bool consoleLoopOver = false;			// for testing
bool updateDone = false;		// used for updating updateGameFeed func

std::string text[13] = { "","","","", "","", "","", "","","", "","", };		// game feed array
std::string cmd = "";																						// user command input
std::string lastString = "";																					// used to empty string
std::string badInput = "That is not a command!";
std::string goExitTip = "[TIP]: \"bw_leave\" to leave.";
std::string cmdsTip = "[TIP]: \"bw_cmd\" for help.";
std::string killingGameText = "you killed me.";
//--------------
std::string bw_leavePrompt = "\"bw_leave\" to leave.";
std::string bw_playPrompt = "\"bw_play\" play screen.";
std::string bw_menuPrompt = "\"bw_color\" menu colours.";
std::string bw_cmdPrompt = "\"bw_cmd\" for help.";
std::string bw_statsPrompt = "\"bw_stats\" show stats.";
std::string bw_clearPrompt = "\"bw_clear\" clear mess.";

// not an actual command prompt.
string gotItPrompt = "..got it?";

HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

int iSecret;	// holds random number for tips.

// reset string arrays
void resetGameFeed() {

	for (int i = 0; i < 13; i++) {

		text[i] = "";
	}

}

// display console title
void consoleTitle() {

	if (INVALID_HANDLE_VALUE != hConsole)
	{
		//         pos = {across, up/down}
		COORD pos = { 11, 4 };
		SetConsoleCursorPosition(hConsole, pos);

		cout << "[CONSOLE PROMPT]";

	}
}

// push text..
void pushSpace() {

	for (int i = 0; i < 26; i++) {

		cout << '\n';
	}
}

// will UPDATE the Game Feed
void updateGameFeed() {

	// we make this false to enter the loop
	updateDone = false;

	while (updateDone == false) {

		/*
			FOLLOW PROCEDURE BELOW TO ADD ADDITIONAL SPACES IN GAME FEED.
			MAKE SURE TO + ARRAY SIZE
		*/

#pragma region Index 0 Look
		if (text[0] == "")
		{
			// do nothing

		}

		else {
			text[0] = "";
		}
#pragma endregion 

#pragma region Index 1 Look
		if (text[1] == "") {

			// do nothing
		}

		else {

			text[0] = text[1];
		}
#pragma endregion 

#pragma region Index 2 Look
		if (text[2] == "") {

			// do nothing
		}

		else {

			text[1] = text[2];
		}
#pragma endregion 

#pragma region Index 3 Look
		if (text[3] == "") {

			// do nothing
		}

		else {

			text[2] = text[3];
		}
#pragma endregion  

#pragma region Index 4 Look
		if (text[4] == "") {

			// do nothing
		}

		else {

			text[3] = text[4];
		}
#pragma endregion  

#pragma region Index 5 Look
		if (text[5] == "") {

			// do nothing
		}

		else {

			text[4] = text[5];
		}
#pragma endregion 

#pragma region Index 6 Look
		if (text[6] == "") {

			// do nothing
		}

		else {

			text[5] = text[6];
		}
#pragma endregion 

#pragma region Index 7 Look
		if (text[7] == "") {

			// do nothing
		}

		else {

			text[6] = text[7];
		}
#pragma endregion  

#pragma region Index 8 Look
		if (text[8] == "") {

			// do nothing
		}

		else {

			text[7] = text[8];
		}
#pragma endregion 

#pragma region Index 9 Look
		if (text[9] == "") {

			// do nothing
		}

		else {

			text[8] = text[9];
		}
#pragma endregion 





#pragma region Index 10 Look
		if (text[10] == "") {

			// do nothing
		}

		else {

			text[9] = text[10];
		}
#pragma endregion  

#pragma region Index 11 Look
		if (text[11] == "") {

			// do nothing
		}

		else {

			text[10] = text[11];
		}
#pragma endregion 

#pragma region Index 12 Look
		if (text[12] == "") {

			text[12] = lastString;
		}

		else {

			text[11] = text[12];
			text[12] = lastString;

			setcolor(white, black);
		}
#pragma endregion 


		lastString = "";

		updateDone = true;		// set to TRUE when done.

	}

}

// will DISPLAY the Game Feed
void displayGameFeed() {

	// This function will display the entire game feed array. 

	if (INVALID_HANDLE_VALUE != hConsole)
	{
		//         pos = {across, up/down}
		COORD pos = { 0, 7 };
		SetConsoleCursorPosition(hConsole, pos);
	}

	// displays the current array
	for (int i = 0; i < 13; i++) {


		// we check if this text[] is currently a 'tip'
		if (text[i] == goExitTip || text[i] == cmdsTip) {

			setcolor(green, black); // set to green

		}

		// we check if we kill the game
		else if (text[i] == killingGameText) {

			setcolor(red, black); // set to red
		}

		cout << "     " << text[i] << '\n';

		setcolor(white, black);


	}
}

// will GENERATE RANDOM NUMBER for hints (uses updateGameFeed())
void TipGenerator() {

	/* initialize random seed: */
	/* generate secret number between 1 and 200: */

	// Re-implementation to Switch case if causing issues

	iSecret = rand() % 41 + 1;

	// "hint" test
	switch (iSecret) {
	case 5:
		lastString = goExitTip;
		updateGameFeed();
		break;
	case 10:
		lastString = cmdsTip;
		updateGameFeed();
		break;
	default:
		break;

	}


}

// shows "command" section NOTE: This will be the UI function
void displayUI() {

	if (INVALID_HANDLE_VALUE != hConsole)
	{
		//         pos = {across, up/down}
		COORD pos = { 0, 25 };
		SetConsoleCursorPosition(hConsole, pos);

	}
}

// Skill Mechanic Functionality
void RunCommandGuide() {

	// Come up with a way to place these into a loop (numbered)

	// 1 ** show how to exit
	system("cls");
	pushSpace();
	lastString = bw_leavePrompt;
	updateGameFeed();
	displayGameFeed();
	displayUI();
	std::this_thread::sleep_for(chrono::seconds(1));


	// 2 ** show how to go back to play screen
	system("cls");
	pushSpace();
	lastString = bw_playPrompt;
	updateGameFeed();
	displayGameFeed();
	displayUI();
	std::this_thread::sleep_for(chrono::seconds(1));

	// 3 ** show how to change menu colours
	system("cls");
	pushSpace();
	lastString = bw_menuPrompt;
	updateGameFeed();
	displayGameFeed();
	displayUI();
	std::this_thread::sleep_for(chrono::seconds(1));

	// 4 ** show how to bring up commands
	system("cls");
	pushSpace();
	lastString = bw_cmdPrompt;
	updateGameFeed();
	displayGameFeed();
	displayUI();
	std::this_thread::sleep_for(chrono::seconds(1));

	// 5 ** show how to get stats
	system("cls");
	pushSpace();
	lastString = bw_statsPrompt;
	updateGameFeed();
	displayGameFeed();
	displayUI();
	std::this_thread::sleep_for(chrono::seconds(1));

	// 6 ** show how to clear console
	system("cls");
	pushSpace();
	lastString = bw_clearPrompt;
	updateGameFeed();
	displayGameFeed();
	displayUI();
	std::this_thread::sleep_for(chrono::seconds(1));

	// 7 ** show how to clear console
	system("cls");
	pushSpace();
	lastString = gotItPrompt;
	updateGameFeed();
	displayGameFeed();
	displayUI();
	std::this_thread::sleep_for(chrono::seconds(1));

}

// checking all GameInput here
void GameFeedInput() {

	// head back to main 
	if (cmd == "bw_leave") {

		consoleActive = false;
		isMainMenuActive = true;

		// 1 ** show how to exit
		system("cls");
		pushSpace();
		resetGameFeed();
		lastString = "leaving...";
		updateGameFeed();
		displayGameFeed();
		displayUI();
		std::this_thread::sleep_for(chrono::seconds(1));

		// WE WILL LOAD THE MAIN MENU HERE

		resetGameFeed();
		DisplayDefaultMenu();  // called once.
		drawMenu();

	}

	// return to main play screen
	else if (cmd == "bw_play") {

		lastString = "playing...";
		updateGameFeed();
		std::this_thread::sleep_for(chrono::milliseconds(500));

		// WE WILL LOAD THE PLAY SCREEN HERE
	}

	// turn menu marker red
	else if (cmd == "bw_red") {

		redColorOn = true;
		// turn off everything else.
		greenColorOn = false;
		aquaColorOn = false;
		blueColorOn = false;
		purpleColorOn = false;
		yellowColorOn = false;
		lastString = "menu color changed: red.";
		updateGameFeed();
		std::this_thread::sleep_for(chrono::milliseconds(500));

		// WE WILL LOAD THE PLAY SCREEN HERE
	}

	// turn menu marker blue
	else if (cmd == "bw_blue") {

		blueColorOn = true;
		greenColorOn = false;
		aquaColorOn = false;
		redColorOn = false;
		purpleColorOn = false;
		yellowColorOn = false;

		lastString = "menu color changed: blue.";
		updateGameFeed();
		std::this_thread::sleep_for(chrono::milliseconds(500));

		// WE WILL LOAD THE PLAY SCREEN HERE
	}

	// turn menu marker purple
	else if (cmd == "bw_purple") {

		purpleColorOn = true;
		greenColorOn = false;
		aquaColorOn = false;
		redColorOn = false;
		blueColorOn = false;
		yellowColorOn = false;

		lastString = "menu color changed: purple.";
		updateGameFeed();
		std::this_thread::sleep_for(chrono::milliseconds(500));

		// WE WILL LOAD THE PLAY SCREEN HERE
	}

	// turn menu marker aqua
	else if (cmd == "bw_aqua") {

		aquaColorOn = true;
		greenColorOn = false;
		redColorOn = false;
		blueColorOn = false;
		purpleColorOn = false;
		yellowColorOn = false;

		lastString = "menu color changed: aqua.";
		updateGameFeed();
		std::this_thread::sleep_for(chrono::milliseconds(500));

		// WE WILL LOAD THE PLAY SCREEN HERE
	}

	// turn menu marker green
	else if (cmd == "bw_green") {

		greenColorOn = true;
		aquaColorOn = false;
		redColorOn = false;
		blueColorOn = false;
		purpleColorOn = false;
		yellowColorOn = false;

		lastString = "menu color changed: green.";
		updateGameFeed();
		std::this_thread::sleep_for(chrono::milliseconds(500));

		// WE WILL LOAD THE PLAY SCREEN HERE
	}

	// turn menu marker yellow
	else if (cmd == "bw_yellow") {

		yellowColorOn = true;
		greenColorOn = false;
		aquaColorOn = false;
		redColorOn = false;
		blueColorOn = false;
		purpleColorOn = false;

		lastString = "menu color changed: yellow.";
		updateGameFeed();
		std::this_thread::sleep_for(chrono::milliseconds(500));

		// WE WILL LOAD THE PLAY SCREEN HERE
	}

	// show list of current commands
	else if (cmd == "bw_cmd") {

		resetGameFeed();
		RunCommandGuide();
	}

	// show player stats
	else if (cmd == "bw_stats") {

		lastString = "bw_stats not ready.";
		updateGameFeed();
		std::this_thread::sleep_for(chrono::milliseconds(500));
	}

	// clear the console window
	else if (cmd == "bw_clear") {

		resetGameFeed();
	}

	// shut down bingwickle (kill it!)
	else if (cmd == "bw_kill") {

		// 1 ** show how to exit
		system("cls");
		pushSpace();
		resetGameFeed();
		lastString = killingGameText;
		updateGameFeed();
		displayGameFeed();
		displayUI();
		std::this_thread::sleep_for(chrono::seconds(2));
		exit(0);
	}

	// check if user typed anything at all
	else if (cmd == "") {


		int randomNothing = rand() % 3 + 1;

		switch (randomNothing) {

		case 1:

			lastString = "you said nothing.";
			break;
		case 2:
			lastString = "huh?";
			break;
		case 3:
			lastString = "that's not a command.";
			break;
		default:
			break;
		}



		updateGameFeed();

	}

	// otherwise, it was not a command (acts as "default") for switch-case
	else {

		// [**************IMPLEMENT RANDOM ERROR MESSAGES**************]
		//lastString = badInput;

		string holdcommand = "";

		holdcommand = "sorry but '" + cmd + "' means nothing.";

		lastString = holdcommand;

		updateGameFeed();
	}
}

// initally show user cmds command if they need help.
void DefaultCmdsPromptToFeed() {

	system("cls");
	pushSpace();
	lastString = cmdsTip;
	updateGameFeed();
	displayGameFeed();
	displayUI();

}

// calls all functions, starts seed, loops
void runGameFeed() {

	system("cls");
	std::this_thread::sleep_for(chrono::seconds(1));

	// begin random seed
	unsigned srand((int)time(NULL));

	pushSpace();
	DefaultCmdsPromptToFeed();  // show initial tip for bw_cmd

	while (consoleActive == true) {

		setcolor(white, black);

		consoleTitle();

		//display gameFeed
		displayGameFeed();


		cout << "\n\n\n\n";

		if (INVALID_HANDLE_VALUE != hConsole)
		{
			COORD pos = { 3, 20 };
			SetConsoleCursorPosition(hConsole, pos);

			cout << "   ";
			cout << "command: ";
			getline(cin, cmd);		// user input
		}

		// checks what you type
		GameFeedInput();

		// generates random number for hint
		TipGenerator();

		system("cls");
	}

	
}