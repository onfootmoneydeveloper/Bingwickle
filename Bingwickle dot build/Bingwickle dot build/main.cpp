/*

	★ BINGWICKLE. Designed by Blake Carrington ★
	  All rights reserved.   -- '' 2024 '' --

*/

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
#include "playBing.h"



/*
	silver, gold, diamond, platn
*/

// lets set up the window for bingwickle.
void generalWindowSetup() {

	disableMouseHighlighting();
	setWindowSize();
	hideTheCursor();
	setWindowTitle();
	removeScrollBar();

	// we call these functions from our
	// setConsole.cpp
}

// initial starting screen.
// introdutory, name of game, developer/date, 
void startUpScreen() {

	// show bingwickle
	cout << "\n\n\n\n\n\n\n\n\n";
	cout << "           ";
	setcolor(white, black);				// <-- set colour
	cout << "Bingwickle v1.0";
	std::this_thread::sleep_for(chrono::seconds(3));
	system("cls"); // clear our screen
	std::this_thread::sleep_for(chrono::seconds(2));

}

// lets get the name of the user. 
// the 'name' will also be used as a password. 
// we will use this name to create a local account for the user.
// if the 'name' is already on the system, we log in.
// else, create new. 


// ** for testing **
void iconDisplay() {
	/*
	makes copies from img to text
	https://manytools.org/hacker-tools/convert-images-to-ascii-art/go/

	makes text to text art
	https://patorjk.com/software/taag/#p=display&f=Graffiti&t=Type%20Something%20
	*/

	std::string icon =	"........................."
						"........................."
						"....///.%%//////..///...."
						"....%//////////.//////..."
						"....%////////////////...."
						".....****************...."
						"....***//////**////***..."
						".....****************...."
						".....%%%**********%%%...."
						".........................";

	const int width = 25;

	for (size_t i = 0; i < icon.length(); i += width) {
		std::cout << icon.substr(i, width) << '\n';
	}

	std::cin.get(); // waits for key press
}


void getUsername() {

	//showTheCursor(); // enable the cursor for this moment.

	// display enter name
	cout << "\n\n\n\n\n\n";
	cout << "          ";
	setcolor(white, black);
	cout << "[ENTER YOUR NAME]" << endl;

	// warning 
	cout << "\n\n";
	cout << "   ";
	setcolor(blue, black);
	cout << "CHANGE AT: C:\\Bingwickle\\Users\\" << endl;

	// get the user's name
	setcolor(white, black);
	cout << "\n\n";
	cout << "            ";
	setcolor(green, black);
	cout << ">  ";
	setcolor(white, black);

	std::getline(std::cin >> std::ws, globalUsername);   // <-- called from global	
}

// user set up
void setUpUserPath() {

	int loginCountNumber = 0;

	// used to create our directory "ourDirectory"
	namespace ourDirectoryToV1 = std::filesystem; 
	namespace ourDirectoryToTickets = std::filesystem;

	// lets check if this user exists already
	std::filesystem::path bingwicklePath = std::string("C:\\Bingwickle\\Users\\" + globalUsername + "\\v1\\");


	bool filepathExists = std::filesystem::exists(bingwicklePath);



	//        [  ACCOUNT  SET   UP  ]
	// if path DOES NOT EXIST, we create a set up
	// 1. add the file directory set up here
	// 2. alert user that we are doing this as they are new
	// 3. put fresh 0'd data in new files
	// 4. (welcome to bingwickle, Setting up files, Done.)

	// [9:00AM CHECK!]  if its past 9:00am AND pathway check.
	// NOTE: Users will be unable to create an account before 9:00AN.

	if (((now->tm_hour > globbalHour) || (now->tm_hour == globbalHour && now->tm_min >= globalMinute)) && (!std::filesystem::is_directory(bingwicklePath.parent_path()))) {
	
		system("cls");


		// setting up local files.
		cout << "\n\n\n\n\n\n\n\n\n";
		cout << "          ";
		setcolor(white, black);				// <-- set colour
		cout << "Setting up files..";
		std::this_thread::sleep_for(chrono::seconds(1));
		system("cls"); // clear our screen
		std::this_thread::sleep_for(chrono::seconds(1));


		// we create the file directory
		ourDirectoryToV1::create_directories("C:\\Bingwickle\\Users\\" + globalUsername + "\\v1\\");
		ourDirectoryToTickets::create_directories("C:\\Bingwickle\\Users\\" + globalUsername + "\\tickets\\");

		// we write some files to the directory
		//std::ofstream outfileCurrentXp("C:\\Bingwickle\\Users\\" + globalUsername + "\\v1\\currentExp.txt");
		std::ofstream outfileXpTill("C:\\Bingwickle\\Users\\" + globalUsername + "\\v1\\loginCount.txt");
		std::ofstream outfileDailyTicketCount("C:\\Bingwickle\\Users\\" + globalUsername + "\\v1\\dailyTicketCount.txt");
		//std::ofstream outfileXpRemaining("C:\\Bingwickle\\Users\\" + globalUsername + "\\v1\\expRemaining.txt");
		std::ofstream outfileTotalTicketsCount("C:\\Bingwickle\\Users\\" + globalUsername + "\\v1\\totalTicketCount.txt");
		//std::ofstream outfileCurrentLvl("C:\\Bingwickle\\Users\\" + globalUsername + "\\v1\\currentLvl.txt");
		std::ofstream outfileTicketsHistory("C:\\Bingwickle\\Users\\" + globalUsername + "\\tickets\\ticket_data.txt");


		// since this is the first logim, here's your first login point


		outfileXpTill << loginCountNumber;	 // writes the number to the file


		// Lets remind the user that they have just 
		// recieved +1 login?

		cout << "\n\n\n\n\n\n\n\n\n";
		cout << "         ";
		setcolor(yellow, black);				// <-- set colour
		cout << "Creation Reward: +1";
		std::this_thread::sleep_for(chrono::seconds(2));
		system("cls"); // clear our screen
		std::this_thread::sleep_for(chrono::seconds(1));



		// then we close all these files.
		//outfileXpTill.close();
		outfileDailyTicketCount.close();
		//outfileXpRemaining.close();
		outfileTotalTicketsCount.close();
		//outfileCurrentLvl.close();
		outfileTicketsHistory.close();


		// load main menu here.


	}


	//      [  ACCOUNT   LOG  IN   ]
	// other wise, load current user
	// 1. welcome back message
	// 2. alert user we are loading their stats
	// 3. must now pull data from ALL files


	else {

		// [9:00AM CHECK!]  if its past 9:00am
		if ((now->tm_hour > globbalHour) || (now->tm_hour == globbalHour && now->tm_min >= globalMinute)) {

			system("cls");

			// fetching ALL local data

			cout << "\n\n\n\n\n\n\n\n\n";
			cout << "           ";
			setcolor(white, black);				// <-- set colour
			cout << "Fetching data..";
			std::this_thread::sleep_for(chrono::seconds(1));
			system("cls"); // clear our screen
			std::this_thread::sleep_for(chrono::seconds(1));


			// Lets remind the user that they have just 
			// recieved +1 login?

			cout << "\n\n\n\n\n\n\n\n\n";
			cout << "           ";
			setcolor(yellow, black);				// <-- set colour
			cout << "Login Reward: +1";
			std::this_thread::sleep_for(chrono::seconds(2));
			system("cls"); // clear our screen
			std::this_thread::sleep_for(chrono::seconds(1));

			// [  ENTERING GAME   ]
			// below, we will write the logic where we pull the encrpt data 
			// the .txt files 


			// then we will display the menu: 



		
		}


		// NOT PAST 9:00AM
		else {

			system("cls");

			cout << "\n\n\n\n\n\n\n\n\n";
			cout << "        ";
			setcolor(white, black);				// <-- set colour
			cout << "Work starts at ";
			setcolor(red, black);
			cout << "9:00AM";
			setcolor(white, black);
			cout << "." << endl;
			getchar();
			system("cls"); // clear our screen
			exit(0);
		}


	}


	//outfile << "DA FINAL" << std::endl;

}


// get +1 whenever you log in
void incrementLoginCount() {

	std::string filePath = "C:\\Bingwickle\\Users\\" + globalUsername + "\\v1\\loginCount.txt";

	int loginCount = 0;

	std::ifstream infile(filePath);
	if (infile) {
		if (!(infile >> loginCount)) {
			loginCount = 0; // fallback if file is empty or corrupt
		}
		infile.close();
	}
	else {
		// Try to create the file if it doesn't exist
		std::ofstream createFile(filePath);
		if (createFile) {
			createFile << 0;
			createFile.close();
			loginCount = 0;
		}
		else {
			std::cerr << "Failed to open or create file: " << filePath << std::endl;
			return;
		}
	}

	loginCount++;

	std::ofstream outfile(filePath);
	if (outfile) {
		outfile << loginCount;
		outfile.close();
	}
	else {
		std::cerr << "Failed to open file for writing: " << filePath << std::endl;
	}
}


int main() {

	generalWindowSetup();		// run initial console defaults.

	playSong0();			// when WIN is set, play start up. **TURN ON IN AUDIO.CPP**

	//startUpScreen();			//(REMOVE to skip load)
	getUsername();			//(REMOVE to skip load)
	setUpUserPath();			//(REMOVE to skip load)

	incrementLoginCount();	// <--- whenever you login, get +1

	// menu/game loop

	do {
		
		if (gameActive == false) {	// if we're not in-game, show main menu

			DisplayDefaultMenu();
			drawMenu();

		}

		else if (gameActive == true) {	// if we're in game, show the game

			play();
			

		}

	} while (1);

	system("pause");		// <--- for testing
	exit(0);

}