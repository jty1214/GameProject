#pragma once

#include "HandlerBase.h"

class HandlerLogin : HandlerBase
{
	REGIST_HANDLE(PACKET_LOGIN, HandlerLogin);	
public :
	CONSTRUCT_HANDLE(PACKET_LOGIN, HandlerLogin);
public :
	virtual bool Do(BYTE *pStream, int nLength);
};