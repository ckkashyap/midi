#include <iostream>
#include <tuple>
#include <map>


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
	std::cin >> c1 >> c2 >> c3 >> c4;

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
		std::cin >> b;
		val <<= 8;
		val|=b;
		byteCount++;
	}while(b&0xf0);
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

	std::cin >> type;
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

int readEvent() {
	auto varLen = readN();
	unsigned delta = std::get<0>(varLen);
	std::cout << "DELTA = " << delta << std::endl;

	Byte firstByte;
	std::cin >> firstByte;

	switch(firstByte) {
		case 0xff:
			return 1 + readMetaEvent();

	}

	exit(0);
}

void readTrack() {
	readMTrk();
	int length = read4();
	int i = 0;
	while(length) {
		length -= readEvent();
		if(i>2)break;
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
