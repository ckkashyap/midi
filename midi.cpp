#include <iostream>

#include <MIDIFile.h>


int main() {
    // Begin with some chords.
    
    MIDIfile file;
    //file.addLoopStart();
    file.track.keyOn(0, 60, 127);
    file.track.keyOn(9, 70, 127);
    file.track.addDelay(320);
    file.track.keyOn(0, 60, 127);
    file.track.keyOn(9, 70, 127);
    file.track.addDelay(320);
    file.track.keyOn(0, 60, 127);
    file.track.keyOn(9, 70, 127);
    
    
    file.Finish();
    
    FILE* fp = std::fopen("test.mid", "wb");
    std::fwrite(&file.fileStream.stream.at(0), 1, file.fileStream.stream.size(), fp);
    std::fclose(fp);
    

	return 0;
}
