#pragma once
#include <cstring>

namespace PDL
{
	int Version = 1;
	class PKT_REQUEST_ENTER_CHANNEL_WRITE
	{
		int world;
		int channel;

		int streamLength;
	public:
		PKT_REQUEST_ENTER_CHANNEL_WRITE()
		{
			streamLength = 0;
		}
		~PKT_REQUEST_ENTER_CHANNEL_WRITE() {}

		int& world()
		{
			return world;
		}

		int& channel()
		{
			return channel;
		}

		int getStreamLength()
		{
			streamLength += sizeof(world);
			streamLength += sizeof(channel);
		}

		void serialize(void* byteStream)
		{
			char* ptr = (char *)byteStream;

			memcpy(ptr, (void *)(&world), sizeof(world));
			ptr += sizeof(world);

			memcpy(ptr, (void *)(&channel), sizeof(channel));
			ptr += sizeof(channel);
		}
	}
}