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

int trackNumber = 0;


// play our initial start up sound.
void playSong0() {

	PlaySound(TEXT("SLAs.wav"), NULL, SND_FILENAME | SND_ASYNC);
}

void playSong1() {

	PlaySound(TEXT("Debrief.wav"), NULL, SND_FILENAME | SND_ASYNC);

}

// stop the sound
void muteSound() {

	PlaySound(NULL, 0, 0);

}
