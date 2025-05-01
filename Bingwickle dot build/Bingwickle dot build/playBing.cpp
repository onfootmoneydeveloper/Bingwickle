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

void playTestToExit() {
	exit(0);
}

void play() {

	system("cls"); 

	std::string input;
	int number;



	cout << "\n\n\n\n";
	COORD pos = { 3, 20 };
	SetConsoleCursorPosition(hConsole, pos);

	cout << "   ";
	std::cout << "Reference:\n";

	while (true) {
		std::cout << "> ";
		std::cin >> input;

		if (input == "done") {
			gameActive = false;
			break;
		}

		try {
			number = std::stoi(input);
			std::cout << "You entered: " << number << std::endl;
			// Do something with 'number' here
		}
		catch (std::invalid_argument&) {
			std::cout << "Numbers only, unless you're 'done'.\n";
		}
	}

	std::cout << "Exiting play function.\n";
}


// when yo hit play - GET all stats, display stats
// current stats: 

/*

	currentEXP
	currentLVL
	dailyTicketCount
	expRemaining
	loginCount
	ticketCount

	shave down to: 

	total EXP						the total amount of experience points you have
	current Level					your current level based on your experience
	daily Ticket count				how many tickets you have logged in a day
	logInCount						how many times you have logged in ( ++ at file set up)
	totalTicketCount				how many tickets you have done OVERALL

	ticketCount_date_here			e.g ticketCount_29_04_2025 <-- will create new files each day, 
									so if you log on the day after, Bingwickle will create
									ticketCount_30_04_2025. The file will hold the list of "references" 
									that you have actioned or completed, like this: 
									
									1938394
									1937835
									1955...

									Duplicates will be ignored with a messaged (ticket already been actioned)

*/

