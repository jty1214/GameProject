#pragma once

#include "../../../Share/PacketHandlerType.inl"
#include <cstdio>

const int MAX_LENGTH_SIZE = 32768;

#define BYTE char

#define DEFINE_HANDLE( Type, TypeName ) \
	TypeName TypeNameType;\

#define REGIST_HANDLE( Type, TypeName ) \
	TypeName() \
	{\
		eType = Type;\
		HandlerBase::pHandlerMap[Type] = this;\
	}

class HandlerBase
{
protected :
	PacketHandlerType eType;
	virtual bool Do(BYTE *pStream, int nLength) = 0;

private :
	static bool isTypeValid(int eType);
	static HandlerBase* find(int eType);
public :
	static HandlerBase* pHandlerMap[PACKET_MAX];
	static bool execute(BYTE *pStream, int nRealPacketLength);
};