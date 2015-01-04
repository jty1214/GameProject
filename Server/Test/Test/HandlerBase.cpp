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
	// ��Ŷ�� �ʹ� �۰ų�, �ʹ� Ŭ ��
	if (nRealPacketLength < 2 * sizeof(int) || nRealPacketLength > MAX_LENGTH_SIZE)
	{
		return false;
	}

	int nType, nLength;
	memcpy(pStream, &nType, sizeof(int));
	memcpy(pStream + sizeof(int), &nLength, sizeof(int));

	// ��Ŷ�� ��õ� ���̿� ���� ���̰� ���� ���� ��
	if (nRealPacketLength != nLength + 2 * sizeof(int))
	{
		return false;
	}

	HandlerBase* pPacketHandler = find(nType);

	// �ڵ鷯�� ��ϵ��� ���� ��Ŷ�� ��
	if (pPacketHandler == nullptr)
	{
		return false;
	}

	return pPacketHandler->Do(pStream + 2 * sizeof(int), nLength);
}