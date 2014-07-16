#ifndef MIDINOTE
#define MIDINOTE

#include <Music.h>

unsigned getMIDINoteNumber(Note n, Octave o) {
	unsigned noteNumber = NoteMap[n];
	unsigned octaveNumber = OctaveMap[o];

	return ((12 * octaveNumber) + noteNumber);
}

#endif
