#pragma once

#include "HandlerBase.h"
#include <cstring>

HandlerBase* HandlerBase::pHandlerMap[];

HandlerBase* HandlerBase::find(int eType)
{
	if (isTypeValid(eType) == false)
	{
		return nullptr;
	}
	return pHandlerMap[eType];
}

bool HandlerBase::isTypeValid(int eType)
{
	return (eType > PACKET_MIN) && (eType < PACKET_MAX);
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