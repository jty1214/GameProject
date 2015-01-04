#pragma once

#include "../../../Share/PacketHandlerType.inl"
#include <cstdio>

const int MAX_LENGTH_SIZE = 32768;

#define BYTE char

#define DEFINE_HANDLE( Type, TypeName ) \
	TypeName TypeNameType;\

#define CONSTRUCT_HANDLE( Type, TypeName ) \
	TypeName() \
	{\
		registHandle();\
	}

#define REGIST_HANDLE( Type, TypeName ) \
	virtual void registHandle() \
	{\
		eType = Type;\
		HandlerBase::getMapInstance()[Type] = this;\
	}

class HandlerBase
{
protected :
	PacketHandlerType eType;
	virtual void registHandle() = 0;
	virtual bool Do(BYTE *pStream, int nLength) = 0;

private :
	static bool isTypeValid(int eType);
	static HandlerBase* find(int eType);
public :
	static HandlerBase** getMapInstance();
	static bool execute(BYTE *pStream, int nRealPacketLength);
};