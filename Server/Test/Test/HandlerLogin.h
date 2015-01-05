#pragma once

#include "HandlerBase.h"

class HandlerLogin : private HandlerBase
{
public :
	REGIST_HANDLE(PACKET_LOGIN, HandlerLogin);
	virtual bool Do(char * const pStream, size_t nLength);
};