#pragma once
#include <Windows.h>
#include <string>

extern bool consoleLoopOver;			// for testing
extern bool updateDone;					// used for updating updateGameFeed func

std::string text[];						// game feed array
extern std::string cmd;					// user command input
extern std::string lastString;			// used to empty string
extern std::string badInput;
extern std::string goExitTip;
extern std::string cmdsTip;
extern std::string killingGameText;
//--------------
extern std::string bw_leavePrompt;
extern std::string bw_playPrompt;
extern std::string bw_menuPrompt;
extern std::string bw_cmdPrompt;
extern std::string bw_statsPrompt;
extern std::string bw_clearPrompt;

// not an actual command prompt.
extern std::string gotItPrompt;

extern HANDLE hConsole;

extern int iSecret;	// holds random number for tips.

// reset string arrays
void resetGameFeed();

// display console title
void consoleTitle();

// push text..
void pushSpace();

// will UPDATE the Game Feed
void updateGameFeed();

// will DISPLAY the Game Feed
void displayGameFeed();

// will GENERATE RANDOM NUMBER for hints (uses updateGameFeed())
void TipGenerator();

// shows "command" section NOTE: This will be the UI function
void displayUI();

// Skill Mechanic Functionality
void RunCommandGuide();

// checking all GameInput here
void GameFeedInput();

// initally show user cmds command if they need help.
void DefaultCmdsPromptToFeed();

// calls all functions, starts seed, loops
void runGameFeed();