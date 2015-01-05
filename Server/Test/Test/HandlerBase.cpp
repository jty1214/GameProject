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

bool HandlerBase::execute(char * const pStream, size_t nRealPacketLength)
{
	// ��Ŷ�� �ʹ� �۰ų�, �ʹ� Ŭ ��
	if (nRealPacketLength < sizeof(int) + sizeof(size_t) || nRealPacketLength > MAX_LENGTH_SIZE)
	{
		return false;
	}

	int nType;
	size_t nLength;
	memcpy(&nType, pStream, sizeof(int));
	memcpy(&nLength, pStream + sizeof(int), sizeof(size_t));

	// ��Ŷ�� ��õ� ���̿� ���� ���̰� ���� ���� ��
	if (nRealPacketLength != nLength + sizeof(int) + sizeof(size_t))
	{
		return false;
	}

	HandlerBase* pPacketHandler = find(nType);

	// �ڵ鷯�� ��ϵ��� ���� ��Ŷ�� ��
	if (pPacketHandler == nullptr)
	{
		return false;
	}

	return pPacketHandler->Do(pStream + sizeof(int) + sizeof(size_t), nLength);
}