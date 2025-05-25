#pragma once

// https://stackoverflow.com/questions/9961949/playsound-in-c-console-application
// pragma: https://stackoverflow.com/questions/5776910/what-does-pragma-once-mean-in-c
// You will need to link winmm.lib in both Release and Debug configurations. 
// Alternatively, you can add: 

#pragma comment(lib, "winmm.lib") 

#include <Windows.h>
#include <mmsystem.h>
#include "audio.h"
#include <string>


// toggles song 0
bool isSLAsOn = true;		// on my default

// toggles song 1
bool isDebriefOn = false;

// ticket sound 
bool ticketSoundPlay = false;

int trackNumber = 0;


// play our initial start up sound.
void playThemeSong() {

	PlaySound(TEXT("theme_sfx.wav"), NULL, SND_FILENAME | SND_ASYNC);
}


void playTicketSound() {

	PlaySound(TEXT("ticket_sfx.wav"), NULL, SND_FILENAME | SND_ASYNC);
}

void playMergeSound() {

	PlaySound(TEXT("merge_sfx.wav"), NULL, SND_FILENAME | SND_ASYNC);

}

void playExitSound() {

	PlaySound(TEXT("exit_sfx.wav"), NULL, SND_FILENAME | SND_ASYNC);

}

void playBadInputSound() {

	PlaySound(TEXT("noref_sfx.wav"), NULL, SND_FILENAME | SND_ASYNC);

}

void playLoadSound() {

	PlaySound(TEXT("play_sfx.wav"), NULL, SND_FILENAME | SND_ASYNC);

}

void playStatsSound() {

	PlaySound(TEXT("stats_sfx.wav"), NULL, SND_FILENAME | SND_ASYNC);

}


// stop the sound
void muteSound() {

	PlaySound(NULL, 0, 0);

}
