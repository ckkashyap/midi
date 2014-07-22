#ifndef __MUSIC__
#define __MUSIC__

#include <map>
#include <vector>
#include <tuple>

namespace Music {

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

std::map<Note, std::tuple<unsigned, std::string>> NoteMap {
	{Note::C, {0, "C"} } ,
	{Note::Cs, {1, "Cs"} } ,
	{Note::D, {2, "D"} } ,
	{Note::Ds, {3, "Ds"} } ,
	{Note::E, {4, "E"} } ,
	{Note::F, {5, "F"} } ,
	{Note::Fs, {6, "Fs"} } ,
	{Note::G, {7, "G"} } ,
	{Note::Gs, {8, "Gs"} } ,
	{Note::A, {9, "A"} } ,
	{Note::As, {10, "As"} } ,
	{Note::B, {11 , "B"} }
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

struct LineItem {
	virtual void print() = 0;
};

struct Pitch : LineItem {
	Note note;
	Octave octave;
	Pitch(Note n, Octave o) : note(n), octave(o) {}

	void print() {
		std::cout << std::get<1>(NoteMap[note]);
	}
};

struct Rest : LineItem {
	unsigned duration;
	Rest(unsigned d) : duration (d) {}

	void print() {
		std::cout << "rest[" << duration << "]";
	}
};

using Line = std::vector<std::shared_ptr<LineItem>>;

inline std::shared_ptr<LineItem> note(Note n, Octave o, unsigned d) {
	return std::shared_ptr<LineItem>(new Pitch(n, o));
}

inline std::shared_ptr<LineItem> rest(unsigned d) {
	return std::shared_ptr<LineItem>(new Rest(d));
}


void printLine(Line l) {
	for(auto& e : l) {
		e->print();	
		std::cout << " ";
	}
	std::cout << std::endl;
}

}

#endif
