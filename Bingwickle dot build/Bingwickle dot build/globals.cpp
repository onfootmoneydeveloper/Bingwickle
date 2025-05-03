#pragma once 
#pragma warning(disable : 4996) //_CRT_SECURE_NO_WARNINGS

#include "globals.h"
#include <string>
#include <Windows.h>

// checking time
#include <ctime>
#include <chrono>
#include <iostream>


// This is the definition of your variable.  It can only happen in one place.
// You must include global.h so that the compiler matches it to the correct
// one, and doesn't implicitly convert it to static.

// We define global variables here only.

#pragma region 
HANDLE hInput = GetStdHandle(STD_INPUT_HANDLE);
#pragma endregion HANDLE

// main player username
std::string globalUsername = "";

// define time
time_t t = time(0);

// local now time
tm* now = localtime(&t);

// hours and mins
int globbalHour = 9, globalMinute = 00;

// checks the state of the game, set to false by default (as program has just run.)
// made true when hit exit button 
bool gameOver = false;


// this tracks the "play" button
bool gameActive = false;

// this tracks "console" button
bool consoleActive = false;

// toggles sound
bool soundOn = true;