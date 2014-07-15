#ifndef __MIDITRACK__
#define __MIDITRACK__

#include <ByteStream.h>

struct MIDITrack {
	ByteStream byteStream;
	unsigned delay, runningStatus;

	MIDITrack() : byteStream {} , delay {0}, runningStatus {0} {}

	void addVarLen(unsigned t)
	{
		if(t >> 21) byteStream.addBytes(0x80 | ((t >> 21) & 0x7F));
		if(t >> 14) byteStream.addBytes(0x80 | ((t >> 14) & 0x7F));
		if(t >>  7) byteStream.addBytes(0x80 | ((t >>  7) & 0x7F));
		byteStream.addBytes(((t >> 0) & 0x7F));
	}

	void flush() {
		addVarLen(delay);
		delay=0;
	}

	void addDelay(unsigned amount) { delay += amount; }

	template<typename... Args>
		void addEvent(Byte data, Args...args)
		{
			flush();
			if(data != runningStatus) byteStream.addBytes(runningStatus = data);
			byteStream.addBytes(args...);
		}
	void addEvent() { }

	template<typename... Args>
		void addMetaEvent(Byte metatype, Byte nbytes, Args...args)
		{
			flush();
			byteStream.addBytes(0xFF, metatype, nbytes, args...);
		}

	void keyOn(int ch, int n, int p)    { if(n>=0)addEvent(0x90|ch, n, p); }
	void keyOff(int ch, int n, int p)   { if(n>=0)addEvent(0x80|ch, n, p); }
	void keyTouch(int ch, int n, int p) { if(n>=0)addEvent(0xA0|ch, n, p); }

	void control(int ch, int c, int v) { addEvent(0xB0|ch, c, v); }
	void patch(int ch, int patchno)    { addEvent(0xC0|ch, patchno); }
	void wheel(int ch, unsigned value) { addEvent(0xE0|ch, value&0x7F, (value>>7)&0x7F); }

	void addText(int texttype, const char* text)
	{
		addMetaEvent(texttype, std::strlen(text), text);
	}
};

#endif
