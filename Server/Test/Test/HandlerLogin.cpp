#include "HandlerLogin.h"
#include <cstdio>

DEFINE_HANDLE(PACKET_LOGIN, HandlerLogin);

bool HandlerLogin::Do(BYTE *pStream, int nLength)
{
	// ��Ŷ ������ �м��Ѵ�.
	// ��Ŷ�� �߸� ���õǼ� ������ ��쿡�� true��, �������� ó���� �Ϸ�� ��� true�� ��ȯ�Ѵ�.

	return true;
}