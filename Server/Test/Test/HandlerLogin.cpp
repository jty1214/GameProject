#include "HandlerLogin.h"
#include <cstdio>

DEFINE_HANDLE(PACKET_LOGIN, HandlerLogin);

bool HandlerLogin::Do(BYTE *pStream, int nLength)
{
	// 패킷 내용을 분석한다.
	// 패킷이 잘못 세팅되서 보내진 경우에는 false를, 정상적인 처리가 완료된 경우 true를 반환한다.

	return true;
}