#pragma once

#include "HandlerBase.h"

class HandlerLogin : HandlerBase
{
public :
	REGIST_HANDLE(PACKET_LOGIN, HandlerLogin);
	virtual bool Do(BYTE *pStream, int nLength);
};