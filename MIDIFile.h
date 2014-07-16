#ifndef __MIDIFILE__
#define __MIDIFILE__

#include <MIDITrack.h>


struct MIDIfile
{
    MIDITrack track;
    unsigned deltaticks, tempo;
    ByteStream fileStream;

    MIDIfile(unsigned deltaticks = 16, unsigned tempo = 1000000)
        : track(), deltaticks(deltaticks), tempo(tempo), fileStream {}
    {
            track.addMetaEvent(0x58,4,  4,2, 24,8);
            // Meta 0x51 (tempo):
            track.addMetaEvent(0x51,3,  tempo>>16, tempo>>8, tempo);
    }
    
    void addLoopStart()  { track.addText(6, "loopStart"); }
    void addLoopEnd()    { track.addText(6, "loopEnd"); }
    
    
    void Finish()
    {
        fileStream.stream.clear();
        fileStream.addBytes(
            // MIDI signature (MThd and number 6)
            "MThd", 0,0,0,6,
            // Format number (1: multiple tracks, synchronous)
            0,0,
            0,1,
            deltaticks    >> 8, deltaticks);
            // Add meta 0x2F to the track, indicating the track end:
            track.addMetaEvent(0x2F, 0);
            // Add the track into the MIDI file:
            fileStream.addBytes("MTrk",
                track.byteStream.stream.size() >> 24,
                track.byteStream.stream.size() >> 16,
                track.byteStream.stream.size() >>  8,
                track.byteStream.stream.size() >>  0);
            fileStream.stream.insert(fileStream.stream.end(), track.byteStream.stream.begin(), track.byteStream.stream.end());
    }
};
#endif
