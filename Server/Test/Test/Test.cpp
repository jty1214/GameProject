#include <iostream>
#include "HandlerLogin.h"

#include "msgpack.h"
#pragma region ���Ǵ� ��Ŷ ����
#include "..\..\..\Share\packet\PacketLogin.h"
#pragma endregion

using namespace std;

int main() {
	HandlerLogin la;
	int n = 74;

	PacketLogin pkt;
	pkt.sText = "Hello World!";

	// ������ ��Ŷ�� ������ ���� PKT_ID / PKT_LENGTH / BYTE_STREAM ���� ������ �˴ϴ�.
	// STREAM_CONVERT�� pkt�� �����ϸ� pStream�� ���� ������ ����Ʈ ������ ä��ϴ�.
	// �� �� pStream�� ���̴� nLength���� �����ϰ� �ְ� �˴ϴ�.
	// Send�� �ϰ� ���� ������ ��Ŷ�� STREAM_CONVERT�� ����Ʈ�� ��ȯ ��
	// pStream�� nLength��ŭ �����ϸ� �˴ϴ�.

	STREAM_CONVERT(pkt, pStream, nLength);

	// �ݴ�� Recv�� �ϰ� �Ǿ��� ���, pStream�� nLength��ŭ ������ ���� ��, execute�� ȣ���ϼ���.
	// ������ �ڵ鷯�� Do�� ������ �˴ϴ�.
	// PACKET_CONVERT�� �̿��� ��Ŷ���� ��ȯ �� ����ϸ� �˴ϴ�.
	HandlerBase::execute(pStream, nLength);
	
	delete[] pStream;
	
	cout << n << endl;
}
