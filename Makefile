all: midi readMIDI
	./midi
	cp test.mid ~/Downloads

readMIDI: readMIDI0.cpp
	g++ -std=c++11 readMIDI0.cpp -o readMIDI

midi: midi.cpp *.h
	g++ -I. -std=c++11 midi.cpp -o midi

clean:
	rm -f midi *.mid readMIDI
