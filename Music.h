#ifndef __MUSIC__
#define __MUSIC__

#include <map>

enum class Note {
	C,
	Cs,
	D,
	Ds,
	E,
	F,
	Fs,
	G,
	Gs,
	A,
	As,
	B
};

enum class Octave { O0, O1, O2, O3, O4, O5, O6, O7, O8, O9 };

std::map<Note,unsigned> NoteMap {
	{Note::C, 0} ,
	{Note::Cs, 1} ,
	{Note::D, 2} ,
	{Note::Ds, 3} ,
	{Note::E, 4} ,
	{Note::F, 5} ,
	{Note::Fs, 6} ,
	{Note::G, 7} ,
	{Note::Gs, 8} ,
	{Note::A, 9} ,
	{Note::As, 10} ,
	{Note::B, 11}
};


std::map<Octave,unsigned> OctaveMap {
	{Octave::O0, 0} ,
	{Octave::O1, 1} ,
	{Octave::O2, 2} ,
	{Octave::O3, 3} ,
	{Octave::O4, 4} ,
	{Octave::O5, 5} ,
	{Octave::O6, 6} ,
	{Octave::O7, 7} ,
	{Octave::O8, 8} ,
	{Octave::O9, 9} ,
};


#endif
