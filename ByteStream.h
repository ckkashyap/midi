#ifndef __BYTESTREAM__
#define __BYTESTREAM__

#include <vector>

using Byte = unsigned char;

struct ByteStream {

	std::vector<Byte> stream;


	ByteStream() : stream {} {}

	void addBytes()
	{
	}

	template<typename... U>
		void addBytes(Byte b, U... args)
		{
			stream.push_back(b);
			addBytes(args...);
		}

	template<typename... U>
		void addBytes(const std::string str, U... args)
		{
			stream.insert(stream.end(), str.begin(), str.end());
			addBytes(args...);
		}

};
#endif
