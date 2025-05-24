#pragma once

#include <iostream>
#include <windows.h>
#include <thread>
#include <string>
#include <filesystem>
#include <fstream>

// calling headers
#include "setConsole.h"
#include "globals.h"
#include "audio.h"
#include "mainMenu.h"
#include "commandLPrmpt.h"

// This is a declaration of your variable, which tells the linker this value
// is found elsewhere.  Anyone who wishes to use it must include global.h,
// either directly or indirectly.

// We define global variables here only.

#pragma region
extern HANDLE hInput;
#pragma endregion HANDLE

// refernece
extern int number;

// lets count daily tickets
extern int dailyTicketCount;

// just testing it out
void playTestToExit();

// print daily tickets to MM
void printAtPosition(int x, int y, const std::string& text);

// play func
void play();

// save ticket locally
void saveTicket();

// store daily point
void saveDailyTicketPoint();

// get ticket counts
void loadTicketCountsFromFile();

// merge daily to total
void mergeDailyIntoTotal();

// loading screen
void bouncingDot(int row, int startCol, int endCol, int durationMs = 3000, int delayMs = 100);

// used for merge
void slapConsoleWindowAnimation(int impact = 30, int wobble = 6, int wobbleTimes = 6, int delayMs = 20);