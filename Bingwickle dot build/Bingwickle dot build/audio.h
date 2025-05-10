#pragma once

#include <windows.h>



// song1 checker
extern bool isDebriefOn;

// toggles sound
extern bool isSLAsOn;

// ticket sound 
extern bool ticketSoundPlay;

extern int trackNumber;

// play start out
void playSong0();

// mute sound
void muteSound();

// song 1 call
void playSong1();

// ticket sound
void playTicketSound();







// [code notes]
// 
// no need to use #ifndef AND pragma once. 
// 
//#ifndef AUDIO_H
//#define AUDIO_H
//#endif