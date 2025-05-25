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
void playThemeSong();

// mute sound
void muteSound();

// ticket sound
void playTicketSound();

// merge sound
void playMergeSound();

// exit sound
void playExitSound();

// bad input sound
void playBadInputSound();

// play load sound
void playLoadSound();

// play stats sound
void playStatsSound();







// [code notes]
// 
// no need to use #ifndef AND pragma once. 
// 
//#ifndef AUDIO_H
//#define AUDIO_H
//#endif