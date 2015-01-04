#pragma once

#include "HandlerBase.h"
#include "cstring"
#include <cstdio>

HandlerBase* HandlerBase::find(int eType)
{
	if (isTypeValid(eType) == false)
	{
		return nullptr;
	}
	return getMapInstance()[eType];
}

bool HandlerBase::isTypeValid(int eType)
{
	return (eType > PACKET_MIN) && (eType < PACKET_MAX);
}

HandlerBase** HandlerBase::getMapInstance()
{
	static HandlerBase** pHandlerMap = nullptr;

	if (pHandlerMap == nullptr)
	{
		pHandlerMap = new HandlerBase*[PACKET_MAX];
		for (int i = 0; i < PACKET_MAX; i++)
		{
			pHandlerMap[i] = nullptr;
		}
	}
	return pHandlerMap;
}

bool HandlerBase::execute(BYTE *pStream, int nRealPacketLength)
{
	// 패킷이 너무 작거나, 너무 클 때
	if (nRealPacketLength < 2 * sizeof(int) || nRealPacketLength > MAX_LENGTH_SIZE)
	{
		return false;
	}

	int nType, nLength;
	memcpy(pStream, &nType, sizeof(int));
	memcpy(pStream + sizeof(int), &nLength, sizeof(int));

	// 패킷의 명시된 길이와 실제 길이가 맞지 않을 때
	if (nRealPacketLength != nLength + 2 * sizeof(int))
	{
		return false;
	}

	HandlerBase* pPacketHandler = find(nType);

	// 핸들러에 등록되지 않은 패킷일 때
	if (pPacketHandler == nullptr)
	{
		return false;
	}

	return pPacketHandler->Do(pStream + 2 * sizeof(int), nLength);
}