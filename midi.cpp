#include <iostream>

#include <MIDIFile.h>
#include <MIDINotes.h>


int main() {
    // Begin with some chords.
    
    MIDIfile file;
    //file.addLoopStart();
    file.track.keyOn(0, Octave::O4, Note::C, 127);
    file.track.addDelay(320);
    file.track.keyOff(0, Octave::O4, Note::C, 127);
    file.track.keyOn(0, Octave::O4, Note::D, 127);
    file.track.addDelay(320);
    file.track.keyOff(0, Octave::O4, Note::D, 127);
    file.track.keyOn(0, Octave::O4, Note::E, 127);
    file.track.addDelay(320);
    file.track.keyOff(0, Octave::O4, Note::E, 127);
    file.track.keyOn(0, Octave::O5, Note::C, 127);
    file.track.addDelay(320);
    file.track.keyOn(0, Octave::O5, Note::D, 127);
    file.track.addDelay(320);
    file.track.keyOn(0, Octave::O5, Note::E, 127);
    file.track.addDelay(320);



    //file.track.keyOn(9, 70, 127);
    //file.track.addDelay(320);
    //file.track.keyOn(0, 60, 127);
    //file.track.keyOn(9, 70, 127);
    //file.track.addDelay(320);
    //file.track.keyOn(0, 60, 127);
    //file.track.keyOn(9, 70, 127);
    
    
    file.Finish();
    
    FILE* fp = std::fopen("test.mid", "wb");
    std::fwrite(&file.fileStream.stream.at(0), 1, file.fileStream.stream.size(), fp);
    std::fclose(fp);
    

	return 0;
}
