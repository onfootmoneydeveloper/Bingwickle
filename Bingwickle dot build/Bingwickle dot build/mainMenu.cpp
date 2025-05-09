#pragma once
#pragma warning(disable : 4244) //_CRT_LOSS_OFDATA_NO_WARNINGS
#pragma warning(disable : 6387) //_SPECIFICATION_FOR_FUNCITION 'MEMCPY'

#include <iostream>
#include <conio.h>
#include <string>
#include <Windows.h>
#include <conio.h>
#include <mmsystem.h>
#include <cstdlib>
#include <thread>
#include <array>

#include "setConsole.h"
#include "globals.h"
#include "defs.h"
#include "commandLPrmpt.h"
#include "playBing.h"


// all properties of our main menu.
// 1. main main list, 
// 2. main main selcted list, 
// 3. size of list, 
// 4. size of list -1, 
// 5. counter, 
// 6. active checker

std::string mainMenuItem[4] = { "PLAY", "CONSOLE" ,"SETTINGS", "EXIT" };
std::string mainMenuItemSelected[4] = { "   PLAY", "   CONSOLE", "   SETTINGS", "   EXIT", };

// song list
std::string songList[5] = { "SLAs?", "Morning", "", "", "", };

int mainMenuSize = end(mainMenuItem) - begin(mainMenuItem);
int menuSizeMinusOneForArrayReference = mainMenuSize - 1;
int counterForMainMenu = 0;
bool isMainMenuActive = true;


std::string optionMenuItem[5] = { "CURSOR ", "SOUND", "SNAP" ,"CREDITS", "GO BACK" };
std::string optionMenuItemSelected[5] = { "    CURSOR ", "    SOUND", "    SNAP", "    CREDITS", "    GO BACK" };
int optionMenuSize = end(optionMenuItem) - begin(optionMenuItem);
int optionSizeMinusOneForArrayReference = optionMenuSize - 1;
int counterForOptionMenu = 0;
bool isOptionMenuActive = false;

bool cursorOff = true;

bool redColorOn = false;
bool blueColorOn = false;
bool purpleColorOn = false;
bool yellowColorOn = false;
bool greenColorOn = true;           // as green is on by default
bool aquaColorOn = false;

// push our mainmenu down!
void pushMenuToCentre() {
    std::cout << "\n\n\n\n\n\n\n";
}

// push our optionsmenu down!
void pushOptionsMenuToCentre() {
    std::cout << "\n\n\n\n\n\n";
}

// toggle for on/off buttons for cursor
void cursorToggleIcon() {
    
    if (cursorOff == false) {

        std::cout << optionMenuItemSelected[0] << " (";
        setcolor(green, black);
        std::cout << "-";
        setcolor(white, black); 
        std::cout << ")" << endl;

    }

    else {

        std::cout << optionMenuItemSelected[0] << " (";
        setcolor(red, black);
        std::cout << "x";
        setcolor(white, black);
        std::cout << ")" << endl;

    }
}

// toggle for on/off buttons for sound
void soundToggleIcon() {

    if (soundOn == true) {

        std::cout << optionMenuItemSelected[1] << " (";
        setcolor(green, black);
        std::cout << "-";
        setcolor(white, black);
        std::cout << ")" << endl;

    }

    else {

        std::cout << optionMenuItemSelected[1] << " (";
        setcolor(red, black);
        std::cout << "x";
        setcolor(white, black);
        std::cout << ")" << endl;

    }
}


// this is the default screen that we only call once.
void DisplayDefaultMenu() {

    system("cls");      // before we show menu, we clear console
    setcolor(white, black); // setting our default colour here


    pushMenuToCentre();
    std::cout << "             "; // <<   CHANGE SPACE IF SELECTED
    std::cout << mainMenuItemSelected[0] << endl;
    std::cout << endl;
    std::cout << "                ";
    std::cout << mainMenuItem[1] << endl;
    std::cout << endl;
    std::cout << "                ";
    std::cout << mainMenuItem[2] << endl;
    std::cout << endl;
    std::cout << "                ";
    std::cout << mainMenuItem[3] << endl;

}

// check what menu color is active
void MenuColor() {

    if (aquaColorOn == true) {

        std::cout << "             "; // <<   ** USE THIS ABOVE SELECTED ITEMS.**
        setcolor(aqua, black);
        std::cout << ">";
        setcolor(white, black);

    }

    else if (greenColorOn == true) {
        std::cout << "             "; // <<   ** USE THIS ABOVE SELECTED ITEMS.**
        setcolor(green, black);
        std::cout << ">";
        setcolor(white, black);

    }

    else if (redColorOn == true) {

        std::cout << "             "; // <<   ** USE THIS ABOVE SELECTED ITEMS.**
        setcolor(red, black);
        std::cout << ">";
        setcolor(white, black);

    }

    else if (blueColorOn == true) {

        std::cout << "             "; // <<   ** USE THIS ABOVE SELECTED ITEMS.**
        setcolor(blue, black);
        std::cout << ">";
        setcolor(white, black);

    }

    else if (purpleColorOn == true) {

        std::cout << "             "; // <<   ** USE THIS ABOVE SELECTED ITEMS.**
        setcolor(purple, black);
        std::cout << ">";
        setcolor(white, black);

    }

    else if (yellowColorOn == true) {

        std::cout << "             "; // <<   ** USE THIS ABOVE SELECTED ITEMS.**
        setcolor(yellow, black);
        std::cout << ">";
        setcolor(white, black);

    }

}

// check what menu color is active (option menu!)
void OptionMenuColor() {

    if (aquaColorOn == true) {

        std::cout << "           "; // <<   ** USE THIS ABOVE SELECTED ITEMS.**
        setcolor(aqua, black);
        std::cout << ">";
        setcolor(white, black);

    }

    else if (greenColorOn == true) {
        std::cout << "           "; // <<   ** USE THIS ABOVE SELECTED ITEMS.**
        setcolor(green, black);
        std::cout << ">";
        setcolor(white, black);

    }

    else if (redColorOn == true) {

        std::cout << "           "; // <<   ** USE THIS ABOVE SELECTED ITEMS.**
        setcolor(red, black);
        std::cout << ">";
        setcolor(white, black);

    }

    else if (blueColorOn == true) {

        std::cout << "           "; // <<   ** USE THIS ABOVE SELECTED ITEMS.**
        setcolor(blue, black);
        std::cout << ">";
        setcolor(white, black);

    }

    else if (purpleColorOn == true) {

        std::cout << "           "; // <<   ** USE THIS ABOVE SELECTED ITEMS.**
        setcolor(purple, black);
        std::cout << ">";
        setcolor(white, black);

    }

    else if (yellowColorOn == true) {

        std::cout << "           "; // <<   ** USE THIS ABOVE SELECTED ITEMS.**
        setcolor(yellow, black);
        std::cout << ">";
        setcolor(white, black);

    }

}

// this is the MAIN MENU list
void DisplayMainMenu() {

    // we apply the ScreenSettings again before we display, 
    // just in case of 
    // any interruptions outside of the program

    // disable mouse highlighting on console
    //disableMouseHighlighting();

    // Maximize button disabled
    //disableMaximize();

    // setting the window title
    //setWindowTitle();

    // remove scrollbar
    //removeScrollBar();

    if (cursorOff == true) {

        hideTheCursor();
    }



    /*

        This function will be called to display a specifc "state" in the menu system.
        each time the function is called, it display the state depending on the value
        of counterMainMenu. starting at 0 and cannot get any higher that our INDEX RANGE.

        If you add a new item in an array, this will increase the value of the maxsize for
        that menu, so you can ignore the if/else if statement below.

        You WILL, need to update each case (1-x) to display what you want each time.


        // cout << "size is: " << mainMenuSize;


     */




     // **THIS DOES NOT NEED TO BE TOUCHED DUE TO MAIN MENU SIZE**
     // we check to make sure the counter does not go over the max
    if (counterForMainMenu >= mainMenuSize) {

        counterForMainMenu--;
    }

    // make sure we dont go below zero
    else if (counterForMainMenu < 0) {
        counterForMainMenu = 0;
    }



    // now we check what number our conter is at. Each time we click the key, we 
    // either ++ or -- out counter, this lets us know where (IN THE ARRAY) we are. 
    // so if we're at 1, then show me the mainMenuItemSelected[1] index. And so on.

    // When you update these cases, it would look like this: 
    /*



        system("cls");

        std::cout << "\n\n\n\n\n\n\n";
        std::cout << "             "; //
        std::cout << mainMenuItemSelected[0] << endl;
        std::cout << endl;
        std::cout << "                ";
        std::cout << mainMenuItem[1] << endl;
        std::cout << endl;
        std::cout << "                ";
        std::cout << mainMenuItem[2] << endl;
        std::cout << endl;
        std::cout << "                ";
        std::cout << mainMenuItem[3] << endl;



        std::cout << endl;                          //<--- added!**
        std::cout << "                ";
        std::cout << mainMenuItem[4] << endl;


        ** for whatever the case "value" (say 3), you will only display that array
        * as a mainMenuItemSelected. Anything else is from mainMenuItem with spacings.
        *
        *
        *
        *

        // USE THIS ABOVE SELECTED ITEMS
        std::cout << "             "; // <<   ** USE THIS ABOVE SELECTED ITEMS.**
        setcolor(green, black);
        std::cout << ">";
        setcolor(white, black);
        // ONLY USE ME ABOVE SELECTED ITEMS



    */

    switch (counterForMainMenu) {


        // **each case is an indication of which location we are in the ARRAY. **

    case 0:

        system("cls");  // clear console.
        pushMenuToCentre();

        // USE THIS ABOVE SELECTED ITEMS
        MenuColor();
        // ONLY USE ME ABOVE SELECTED ITEMS

        std::cout << mainMenuItemSelected[0] << endl;
        std::cout << endl;
        std::cout << "                ";
        std::cout << mainMenuItem[1] << endl;
        std::cout << endl;
        std::cout << "                ";
        std::cout << mainMenuItem[2] << endl;
        std::cout << endl;
        std::cout << "                ";
        std::cout << mainMenuItem[3] << endl;

        break;

    case 1:

        system("cls");
        pushMenuToCentre();
        std::cout << "                ";
        std::cout << mainMenuItem[0] << endl;
        std::cout << endl;


        // USE THIS ABOVE SELECTED ITEMS
        MenuColor();
        // ONLY USE ME ABOVE SELECTED ITEMS


        std::cout << mainMenuItemSelected[1] << "" << endl;  // EXCLAMATION
        std::cout << endl;
        std::cout << "                ";
        std::cout << mainMenuItem[2] << endl;
        std::cout << endl;
        std::cout << "                ";
        std::cout << mainMenuItem[3] << endl;







        /*

            NUDGE REMINDR.
             * we want to be able to detect (when hovered) that the user
             * has not yet nudged their current progress!

        */

        std::cout << "\n\n";
        std::cout << "      ";
        setcolor(yellow, black);
        std::cout << "let's use commands!" << endl;
        setcolor(white, black);
        std::cout << endl;


        break;

    case 2:

        system("cls");
        pushMenuToCentre();
        std::cout << "                ";
        std::cout << mainMenuItem[0] << endl;
        std::cout << endl;
        std::cout << "                ";
        std::cout << mainMenuItem[1] << endl;
        std::cout << endl;


        // USE THIS ABOVE SELECTED ITEMS
        MenuColor();
        // ONLY USE ME ABOVE SELECTED ITEMS


        std::cout << mainMenuItemSelected[2] << endl;
        std::cout << endl;
        std::cout << "                ";
        std::cout << mainMenuItem[3] << endl;

        break;

    case 3:

        system("cls");
        pushMenuToCentre();
        std::cout << "                ";
        std::cout << mainMenuItem[0] << endl;
        std::cout << endl;
        std::cout << "                ";
        std::cout << mainMenuItem[1] << endl;
        std::cout << endl;
        std::cout << "                ";
        std::cout << mainMenuItem[2] << endl;
        std::cout << endl;


        // USE THIS ABOVE SELECTED ITEMS
        MenuColor();
        // ONLY USE ME ABOVE SELECTED ITEMS


        std::cout << mainMenuItemSelected[3] << endl;









        /*

            NUDGE REMINDR.
             * we want to be able to detect (when hovered) that the user
             * has not yet nudged their current progress!

        */

        std::cout << "\n\n";
        std::cout << "          ";
        setcolor(red, black);
        std::cout << "until next time?" << endl;
        setcolor(white, black);
        std::cout << endl;

        break;

    default:
        break;
    }

}

// show if option item is currently in BETA
void optionInBeta() {

    std::cout << optionMenuItemSelected[2] << " (";
    setcolor(yellow, black);
    std::cout << "beta";
    setcolor(white, black);
    std::cout << ")" << endl;

}

// this is the OPTIONS MENU
void DisplayOptionsMenu() {

    // we apply the ScreenSettings again before we display, 
    // just in case of 
    // any interruptions outside of the program

    // disable mouse highlighting on console
    //disableMouseHighlighting();

    // Maximize button disabled
    //disableMaximize();

    // setting the window title
    //setWindowTitle();

    // remove scrollbar
    //removeScrollBar();

    if (cursorOff == true) {

        hideTheCursor();
    }


    if (counterForOptionMenu >= optionMenuSize) {

        counterForOptionMenu--;
    }

    // make sure we dont go below zero
    else if (counterForOptionMenu < 0) {
        counterForOptionMenu = 0;
    }

    switch (counterForOptionMenu) {


        // **each case is an indication of which location we are in the ARRAY. **

    case 0: // CURSOR SELECTED

        system("cls");  // clear console.
        pushOptionsMenuToCentre();


        // USE THIS ABOVE SELECTED ITEMS
        OptionMenuColor();
        // ONLY USE ME ABOVE SELECTED ITEMS

        cursorToggleIcon();
        //std::cout << optionMenuItemSelected[0] << endl;
        std::cout << endl;
        std::cout << "               ";
        std::cout << optionMenuItem[1] << endl;
        std::cout << endl;
        std::cout << "               ";
        std::cout << optionMenuItem[2] << endl;
        std::cout << endl;
        std::cout << "               ";
        std::cout << optionMenuItem[3] << endl;
        std::cout << endl;
        std::cout << "               ";
        std::cout << optionMenuItem[4] << endl;

        break;

    case 1: // SOUND SELECTED

        system("cls");
        pushOptionsMenuToCentre();
        std::cout << "               ";
        std::cout << optionMenuItem[0] << endl;
        std::cout << endl;


        // USE THIS ABOVE SELECTED ITEMS
        OptionMenuColor();
        // ONLY USE ME ABOVE SELECTED ITEMS

        soundToggleIcon();
        //std::cout << optionMenuItemSelected[1] << " (-)" << endl;
        std::cout << endl;
        std::cout << "               ";
        std::cout << optionMenuItem[2] << endl;
        std::cout << endl;
        std::cout << "               ";
        std::cout << optionMenuItem[3] << endl;
        std::cout << endl;
        std::cout << "               ";
        std::cout << optionMenuItem[4] << endl;


        // SOUND DESCRIPTION : NOW PLAYING
        if ((isSLAsOn == true) && (isDebriefOn == false)) {
            std::cout << "\n\n";
            std::cout << "      ";
            setcolor(yellow, black);
            std::cout << "[1/2] now playing: " << songList[0] << endl;
            setcolor(white, black);
            std::cout << endl;
        }

        else if ((isSLAsOn == false) && (isDebriefOn == true)) {
            std::cout << "\n\n";
            std::cout << "     ";
            setcolor(yellow, black);
            std::cout << "[2/2] now playing: " << songList[1] << endl;
            setcolor(white, black);
            std::cout << endl;
        }
        

        break;

    case 2: // SNAP SELECTED

        system("cls");
        pushOptionsMenuToCentre();
        std::cout << "               ";
        std::cout << optionMenuItem[0] << endl;
        std::cout << endl;
        std::cout << "               ";
        std::cout << optionMenuItem[1] << endl;
        std::cout << endl;


        // USE THIS ABOVE SELECTED ITEMS
        OptionMenuColor();
        // ONLY USE ME ABOVE SELECTED ITEMS

        optionInBeta();
        //std::cout << optionMenuItemSelected[2] << endl;
        std::cout << endl;
        std::cout << "               ";
        std::cout << optionMenuItem[3] << endl;
        std::cout << endl;
        std::cout << "               ";
        std::cout << optionMenuItem[4] << endl;



        // SNAP DES/MESSAGE


        /*if (snapWasPressed == true) {

            std::cout << "\n\n";
            std::cout << "          ";
            setcolor(yellow, black);
            std::cout << "snapped!" << endl;
            setcolor(white, black);
            std::cout << endl;
            snapWasPressed = false;
        }*/

        break;

    case 3: // CREDITS SELECTED

        system("cls");
        pushOptionsMenuToCentre();
        std::cout << "               ";
        std::cout << optionMenuItem[0] << endl;
        std::cout << endl;
        std::cout << "               ";
        std::cout << optionMenuItem[1] << endl;
        std::cout << endl;
        std::cout << "               ";
        std::cout << optionMenuItem[2] << endl;
        std::cout << endl;


        // USE THIS ABOVE SELECTED ITEMS
        OptionMenuColor();
        // ONLY USE ME ABOVE SELECTED ITEMS


        std::cout << optionMenuItemSelected[3] << endl;
        std::cout << endl;
        std::cout << "               ";
        std::cout << optionMenuItem[4] << endl;

        // CREDITS DESCRIPTION

        std::cout << "\n\n";
        std::cout << "            ";
        setcolor(yellow, black);
        std::cout << "who made this?" << endl;
        setcolor(white, black);
        std::cout << endl;

        break;

    case 4: // GO BACK SELECTED

        system("cls");
        pushOptionsMenuToCentre();
        std::cout << "               ";
        std::cout << optionMenuItem[0] << endl;
        std::cout << endl;
        std::cout << "               ";
        std::cout << optionMenuItem[1] << endl;
        std::cout << endl;
        std::cout << "               ";
        std::cout << optionMenuItem[2] << endl;
        std::cout << endl;
        std::cout << "               ";
        std::cout << optionMenuItem[3] << endl;
        std::cout << endl;

        // USE THIS ABOVE SELECTED ITEMS
        OptionMenuColor();
        // ONLY USE ME ABOVE SELECTED ITEMS


        std::cout << optionMenuItemSelected[4] << endl;

        break;

    default:
        break;
    }

}

// shows our infomation page
void showInfo() {


    system("cls");

    // Bingwickle was designed to make the boring seem a little more fun. Designed
    // by Blake Carrington, published by ONFOOTMONEY©. 
    // Follow @bingwickle for future updates (if there's every any!)

   /* std::string InfoMessage =   "           BINGWICKLEBUDDY\n\n"
                                "     DESIGNED BY BLAKE CARRINGTON\n\n"
                                "      PUBLISHED BY ONFOOTMONEY©\n\n"
                                "      (AT)BINGWICKLE FOR UPDATES\n";*/

    std::string InfoMessage =   "               CREDITS\n\n\n"
                                "     Dev/Design: 079 Blake\n"
                                "          Music: 079 Blake\n\n"
                                "    Built with: C++ (visual studio)\n\n"
                                "            Version: v1.0.0\n\n"
                                "    (c) 2025 079 Blake.\n\n"
                                "                   No Stealing. \n";

    // credit list: 
  // developer: 
  // music
  // icon artist: 
  // project: Bingwickle - ticket exp counter game
  // built with: C++ (visual studio)
  // testers: 
  // Version: v1.0.0
  // (c) 2025 079 Blake. Steal and I'll cry.


    int x = 0;

    // center the info message
    std::cout << "\n\n\n";


    while (InfoMessage[x] != '\0')
    {

        setcolor(white, black);  // set to white as default


        // the x = value is where the colour begins. 
        // to where the colour ends
        if (x >= 12 && x <=21) {
            setcolor(white, black);
        }

        cout << InfoMessage[x];
        Sleep(30 + rand() % 30);
        x++;

        //getchar();
        //cout << x;
    };


    Sleep(350);
    cout << "\n\n";
    cout << "             ";
    setcolor(red, black);
    cout << "PRESS ENTER";
    setcolor(white, black);

    // might change this to time
    getchar();

}

// draw our main menu
void drawMenu() {

    int c = 0;

    do {

        c = 0;

        if (isMainMenuActive == true) {
            DisplayMainMenu();
        }

        else if (isOptionMenuActive == true) {

            DisplayOptionsMenu();
        }

        //cout << "\n\n\n\n";
        //std::cout << "opts value is " << counterForOptionMenu << endl;
        //std::cout << "opts menu size " << optionSizeMinusOneForArrayReference << endl;

        //std::cout << "main value is " << counterForMainMenu << endl;
        //std::cout << "main menu size " << menuSizeMinusOneForArrayReference << endl;

        switch ((c = _getch())) {

        case KEY_UP:

            // switch case for main menu
            switch (isMainMenuActive) {

            case true:

                if (counterForMainMenu == 0)
                {
                    counterForMainMenu = 0;
                }

                else {

                    counterForMainMenu--;
                }





                //cout << "value: " << counterForMainMenu;
                //std::this_thread::sleep_for(chrono::seconds(1));

                break;
            case false:
                break;
            }

            // switch case for options menu
            switch (isOptionMenuActive) {

            case true:
                counterForOptionMenu--;
                break;
            case false:
                break;
            }

            break;

        case KEY_DOWN:

            // switch case for main menu
            switch (isMainMenuActive) {

            case true:
                

                if (counterForMainMenu == 3) {
                    counterForMainMenu = 3;
                }

                else {
                    counterForMainMenu++;
                }


                //cout << "value: " << counterForMainMenu;
                //std::this_thread::sleep_for(chrono::seconds(1));

                break;
            case false:
                break;
            }

            // switch case for options menu
            switch (isOptionMenuActive) {

            case true:
                counterForOptionMenu++;
                break;
            case false:
                break;
            }

            break;

        case KEY_LEFT:

            if (counterForOptionMenu == 1 && isOptionMenuActive == true && isDebriefOn == true) {
                trackNumber--;
                muteSound();
                playSong0();
                isSLAsOn = true;
                isDebriefOn = false;
            }

            break;

        case KEY_RIGHT:

            if (counterForOptionMenu == 1 && isOptionMenuActive == true && isSLAsOn == true) {
                trackNumber++;
                muteSound();
                playSong1();
                isSLAsOn = false;
                isDebriefOn = true;
            }



            break;

        case KEY_ENTER:

            // if we hit 'enter' on the exit button.
            if ((counterForMainMenu) == (menuSizeMinusOneForArrayReference)) {

                exit(0);
            }

            // if we hit 'enter' on the PLAY button
            else if ((counterForMainMenu == 0) && (isMainMenuActive == true)) {

                isOptionMenuActive = false;
                isMainMenuActive = false;
                counterForMainMenu = 0;
                counterForOptionMenu = 0;
                gameActive = true; // now in-game

            }


            // if we hit 'CONSOLE'
            else if ((counterForMainMenu == 1) && (isMainMenuActive == true)) {

                isOptionMenuActive = false;
                isMainMenuActive = false;
                counterForMainMenu = 0;
                counterForOptionMenu = 0;
                consoleActive = true; // now in console
                runGameFeed();

            }

            // we reset so we dont hit back in this else case. checks for "settings" hit
            else if (counterForMainMenu == 2) {

                isOptionMenuActive = true;
                isMainMenuActive = false;
                counterForMainMenu = 0;
                counterForOptionMenu = 0;
                system("cls");
                std::this_thread::sleep_for(chrono::seconds(1)); // menu pause
            }

            // we check if we hit the "go back" button on the options menu
            else if ((counterForOptionMenu) == (optionSizeMinusOneForArrayReference)) {

                isOptionMenuActive = false;
                isMainMenuActive = true;
                counterForMainMenu = 0;
                counterForOptionMenu = 0;
                system("cls");
                std::this_thread::sleep_for(chrono::seconds(1)); // menu pause

            }

            // check if we hit the "cursor" button
            else if (counterForOptionMenu == 0 && isOptionMenuActive == true) {

                switch (cursorOff) {
                case true:
                    cursorOff = false;
                    hideTheCursor();

                    break;
                case false:
                    cursorOff = true;
                    hideTheCursor();
                    break;
                }
            }

            // check if we hit "SOUND" button (off) (ON SLAs)
            else if (counterForOptionMenu == 1 && isOptionMenuActive == true && isSLAsOn == true) {

                muteSound();
                isSLAsOn = false;
                soundOn = false;
            
            }

            // check if we hit "SOUND" button (off) (ON DEBRIEF)
            else if (counterForOptionMenu == 1 && isOptionMenuActive == true && isDebriefOn == true) {

                muteSound();
                isDebriefOn = false;
                soundOn = false;

            }

            // check if we hit "SOUND" button (on)
            else if (counterForOptionMenu == 1 && isOptionMenuActive == true && isSLAsOn == false) {

                playSong0();
                isSLAsOn = true;
                soundOn = true;

            }

            // check if we hit "enter" on SNAP
            else if (counterForOptionMenu == 2) {

                snapWasPressed = true;
                removeScrollBar();
                playSnapAnimationROAM();
                playRiseAndSlamAnimationROAM();
                disableMouseHighlighting();
                disableMaximize();
            }

            // check if we hit "enter" on CREDITS
            else if (counterForOptionMenu == 3) {
                showInfo();
            }


            // to stop showing the cursor in the menu
            if (isOptionMenuActive == true && isMainMenuActive == false) {
                hideTheCursor();
                if (isOptionMenuActive == false && isMainMenuActive == true) {
                    hideTheCursor();

                }
            }

            break;

        case KEY_ESCAPE:
            break;

        case KEY_DOT:
            break;

        default:
            break;

        }

    } while ((gameOver == false) && (gameActive == false) && (consoleActive == false));

    

}