#include <iostream>
#include <tuple>
#include <map>

using namespace std;

enum class Problem {
	BAD_HEADER_SIGNATURE,
	BAD_TRACK_SIGNATURE,

	BAD_LENGTH_IN_HEADER,

	BAD_FORMAT,
	BAD_NUMBER_OF_TRACKS,
	BAD_TICKS
	};

std::map<Problem, const char *> problemMap {
	{Problem::BAD_HEADER_SIGNATURE, "BAD_HEADER_SIGNATURE"},
	{Problem::BAD_TRACK_SIGNATURE, "BAD_TRACK_SIGNATURE"},
	
	{Problem::BAD_LENGTH_IN_HEADER, "BAD_LENGTH_IN_HEADER"},

	{Problem::BAD_FORMAT, "BAD_FORMAT"},
	{Problem::BAD_NUMBER_OF_TRACKS, "BAD_NUMBER_OF_TRACKS"},
	{Problem::BAD_TICKS, "BAD_TICKS"}
};

using Byte = unsigned char;

using HeaderString = std::tuple<char, char, char, char>;
using word = unsigned short;
using HeaderInfo = std::tuple<word, word, word>;
using VarLen = std::tuple<unsigned, unsigned>;

HeaderString mthd {'M', 'T', 'h', 'd'};
HeaderString mtrk {'M', 'T', 'r', 'k'};

HeaderString readHeaderString() {
	char c1, c2, c3, c4;
	std::cin >> std::noskipws >> c1 >> c2 >> c3 >> c4;

	HeaderString t {c1, c2, c3 ,c4 };
	return t;
}

void readMTrk() throw (Problem) {
	HeaderString t = readHeaderString();
	if(t != mtrk)
		throw Problem::BAD_TRACK_SIGNATURE;
}

void readMThd() throw (Problem) {
	HeaderString t = readHeaderString();
	if(t != mthd)
		throw Problem::BAD_HEADER_SIGNATURE;
}


unsigned read4() {
	unsigned val=0, out;
	Byte *p, *q;
	std::cin.read((char *)&val, 4);
	p=(Byte*)&val;
	q=(Byte*)&out;
	for(int i=0,j=3; i < 4; i++,j--){ 
		q[i]=p[j];
	}

	return out;
}
unsigned read2() {
	unsigned short val=0, out;
	Byte *p, *q;
	std::cin.read((char *)&val, 2);
	p=(Byte*)&val;
	q=(Byte*)&out;
	for(int i=0,j=1; i < 2; i++,j--){ 
		q[i]=p[j];
	}

	return out;
}

VarLen readN() {
	unsigned val = 0;
	unsigned byteCount=0;
	Byte b;
	do {
		std::cin >> std::noskipws >> b;
		val <<= 8;
		val|=b;
		byteCount++;
	}while(b&0x80);
	return {val, byteCount};
}


HeaderInfo readHeader() throw(Problem) {
	readMThd();

	int length = read4();
	if(length != 6) throw Problem::BAD_LENGTH_IN_HEADER;

	word format;
	word ntracks;
	word division;

	format = read2();
	ntracks = read2();
	division = read2();

	std::cout << int(format) << std::endl;
	std::cout << int(ntracks) << std::endl;
	std::cout << int(division) << std::endl;

	if (format != 0 ) throw Problem::BAD_FORMAT;
	if (ntracks != 1) throw Problem::BAD_NUMBER_OF_TRACKS;
	if (division & 0x80) throw Problem::BAD_TICKS;

	return {format, ntracks, division};
}

unsigned readMetaEvent() {
	Byte type;
	unsigned length;
	unsigned byteLength;

	std::cin >> std::noskipws >> type;
	std::cout << std::hex << int(type) << std::endl;

	auto varLen = readN();
	length = std::get<0>(varLen);
	byteLength = std::get<1>(varLen);

	std::cout << "Length = " << length << std::endl;
	for(unsigned i = 0 ; i < length; i++ ) {
		std::cin >> std::noskipws >> type;
		std::cout << " >> " << type << std::endl;
	}
	std::cout << std::endl;
	return 1 + byteLength + length;

}

const char *control2string(int c) {
	switch(c) {
		case 0x80:
			return "Note-off";
		case 0x90:
			return "Note-off";
		case 0xa0:
			return "";
		case 0xb0:
			return "Control-change";
		case 0xc0:
			return "Program-change";
		case 0xe0:
			return "Pitch-bend";
	}
	cout << "undefined" << endl;
	exit(0);
	return "undefined";
}

int readEvent() {
	auto varLen = readN();
	static unsigned delta;
	delta += std::get<0>(varLen);
	std::cout << dec << "DELTA = " << delta << " ";

	Byte firstByte;
	std::cin >> std::noskipws >> firstByte;

	if(firstByte == 0xff)
	{
		return 1 + readMetaEvent();
	}
	int controlNibble = (firstByte & 0xf0);
	int channelNibble = (firstByte & 0x0f);

	if(controlNibble != 0xf0 ) {
		Byte b1, b2, b3 ;
		switch(controlNibble){
			case 0x80:
			case 0x90:
			case 0xa0:
			case 0xb0:
			case 0xe0:
				std::cin >> std::noskipws >> b1;
				std::cin >> std::noskipws >> b2;
				cout << dec << control2string(int(controlNibble)) << " " << channelNibble << " " << int(b1) << " " << int(b2) << endl;
				return 3;
			case 0xc0:
			case 0xd0:
				std::cin >> std::noskipws >> b1;
				cout << dec << control2string(int(controlNibble)) << " " <<  channelNibble << " " << int(b1) << endl;
				return 2;
		}
	}else {
		cout << "BAD" << endl;
	}

	exit(0);
	return 0;
	
}

void readTrack() {
	readMTrk();
	int length = read4();
	int i = 0;
	while(length) {
		length -= readEvent();
		if(i>19485)break;
		i++;
	}
}


void readMidiFile() {
	readHeader();
	readTrack();
}


int main() {
	try {
		readMidiFile();
	}catch (Problem& p) {
		std::cerr << problemMap[p] << "\n";
	}
	return 0;
}
