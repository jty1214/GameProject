#pragma once

#include "pkt.inl"
#include <cstdio>

const int MAX_LENGTH_SIZE = 32768;

#include "handler.macro"
#include "packer.macro"

class HandlerBase
{
protected :
	PacketHandlerType eType;
	virtual bool Do(char * const pStream, size_t nLength) = 0;

private :
	static bool isTypeValid(int eType);
	static HandlerBase* find(int eType);
public :
	static HandlerBase* pHandlerMap[PACKET_MAX];
	static bool execute(char * const pStream, size_t nRealPacketLength);
};