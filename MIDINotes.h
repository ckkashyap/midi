#ifndef MIDINOTE
#define MIDINOTE

#include <Music.h>

unsigned getMIDINoteNumber(Music::Note n, Music::Octave o) {
	unsigned noteNumber = std::get<0>(Music::NoteMap[n]);
	unsigned octaveNumber = Music::OctaveMap[o];

	return ((12 * octaveNumber) + noteNumber);
}

#endif
