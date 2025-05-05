#pragma once
#include <string>
#include <Windows.h>

// declare all menu item arrays

// all properties of our main menu.
// 1. main main list, 
// 2. main main selcted list, 
// 3. size of list, 
// 4. size of list -1, 
// 5. counter, 
// 6. active checker

std::string mainMenuItem[];
std::string mainMenuItemSelected[];
std::string songList[];
extern int mainMenuSize;
extern int menuSizeMinusOneForArrayReference;
extern int counterForMainMenu;
extern bool isMainMenuActive;


std::string optionMenuItem[];
std::string optionMenuItemSelected[];
extern int optionMenuSize;
extern int optionSizeMinusOneForArrayReference;
extern int counterForOptionMenu;
extern bool isOptionMenuActive;

extern bool cursorOff;

extern bool redColorOn;
extern bool blueColorOn;
extern bool purpleColorOn;
extern bool yellowColorOn;
extern bool greenColorOn;           // as green is on by default
extern bool aquaColorOn;


// push our mainmenu down!
void pushMenuToCentre();

// push our optionsmenu down!
void pushOptionsMenuToCentre();

// this is the default screen that we only call once.
void DisplayDefaultMenu();

// check what menu color is active
void MenuColor();

// check what menu color is active (option menu!)
void OptionMenuColor();

// this is the MAIN MENU list
void DisplayMainMenu();

// this is the OPTIONS MENU
void DisplayOptionsMenu();

// shows our infomation page
void showInfo();

// draw our main menu
void drawMenu();