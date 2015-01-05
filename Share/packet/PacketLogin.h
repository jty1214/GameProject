#pragma once

#include <string>

struct PacketLogin
{
	const static int ID = PACKET_LOGIN;
	std::string sText;

	MSGPACK_DEFINE(sText);
};