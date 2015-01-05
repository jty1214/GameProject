#include <iostream>
#include "HandlerLogin.h"

#include "msgpack.h"
#pragma region 사용되는 패킷 선언
#include "..\..\..\Share\packet\PacketLogin.h"
#pragma endregion

using namespace std;

int main() {
	HandlerLogin la;
	int n = 74;

	PacketLogin pkt;
	pkt.sText = "Hello World!";

	// 실제로 패킷을 전송할 때는 PKT_ID / PKT_LENGTH / BYTE_STREAM 으로 전달이 됩니다.
	// STREAM_CONVERT는 pkt을 전달하면 pStream에 위의 내용대로 바이트 정보를 채웁니다.
	// 이 때 pStream의 길이는 nLength에서 저장하고 있게 됩니다.
	// Send를 하고 싶을 때에는 패킷을 STREAM_CONVERT로 바이트로 변환 후
	// pStream을 nLength만큼 전송하면 됩니다.

	STREAM_CONVERT(pkt, pStream, nLength);

	// 반대로 Recv를 하게 되었을 경우, pStream을 nLength만큼 정보를 받은 후, execute를 호출하세요.
	// 정해진 핸들러의 Do로 전달이 됩니다.
	// PACKET_CONVERT를 이용해 패킷으로 변환 후 사용하면 됩니다.
	HandlerBase::execute(pStream, nLength);
	
	delete[] pStream;
	
	cout << n << endl;
}
