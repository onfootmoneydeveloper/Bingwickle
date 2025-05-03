#pragma once
#include <string>
#include <Windows.h>

// This is a declaration of your variable, which tells the linker this value
// is found elsewhere.  Anyone who wishes to use it must include global.h,
// either directly or indirectly.

// We define global variables here only.

#pragma region
extern HANDLE hInput;
#pragma endregion HANDLE

// main player username
extern std::string globalUsername;

// define time
extern time_t t;

// local now time
extern tm* now;

// hours and mins
extern int globbalHour, globalMinute;

// checks the state of the game, set to false by default (as program has just run.)
// made true when hit exit button 
extern bool gameOver;

// for play button
extern bool gameActive;

// for console button
extern bool consoleActive;

// toggles sound
extern bool soundOn;