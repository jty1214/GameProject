#include "HandlerLogin.h"

#include "msgpack.h"
#pragma region ���Ǵ� ��Ŷ ����
#include "..\..\..\Share\packet\PacketLogin.h"
#pragma endregion
DEFINE_HANDLE(PACKET_LOGIN, HandlerLogin);

bool HandlerLogin::Do(char * const pStream, size_t nLength)
{
	PACKET_CONVERT(pStream, nLength, PacketLogin, pkt);

	std::string sText = pkt.sText;

	// ��Ŷ ������ �м��Ѵ�.
	// ��Ŷ�� �߸� ���õǼ� ������ ��쿡�� false��, �������� ó���� �Ϸ�� ��� true�� ��ȯ�Ѵ�.

	return true;
}