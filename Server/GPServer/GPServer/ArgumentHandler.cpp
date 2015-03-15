#include "GPGame.h"

#include "ArgumentHandler.h"
#include "GVariable.h"

DECLARE_ARGUMENT_OPTION(L"LogServer", Argument_LogServer)
bool Argument_LogServer(std::wstring value)
{
	wchar_t sBuffer[1024];
	wcscpy(sBuffer, value.c_str());
	sBuffer[value.length()] = L'\0';

	wchar_t* cashedLogServerIP = nullptr;
	wchar_t* cashedLogServerPort = nullptr;

	ServerArguments index = ServerArguments::IPADDRESS;
	for (wchar_t* sTemp = wcstok(sBuffer, L";"); sTemp != NULL; sTemp = wcstok(NULL, L";"))
	{
		std::wstring sTempStr(sTemp);
		trim(sTempStr);
		wchar_t* sTempBuffer = new wchar_t[sTempStr.length() + 1];
		wcscpy(sTempBuffer, sTempStr.c_str());
		sTempBuffer[sTempStr.length()] = L'\0';

		switch (index)
		{
		case ServerArguments::IPADDRESS:
			cashedLogServerIP = sTemp;
			break;
		case ServerArguments::PORT:
			cashedLogServerPort = sTemp;
			break;
		default:
			delete[] sTempBuffer;
			break;//인자가 너무 많다!!
		}
		
		index = (ServerArguments)((__int32)index + 1);
	}

	if (index == ServerArguments::MAX)
	{
		gLogServerIP = cashedLogServerIP;
		gLogServerPort = cashedLogServerPort;
		return true;
	}

	delete[] cashedLogServerIP;
	delete[] cashedLogServerPort;
	return false;
}

DECLARE_ARGUMENT_OPTION(L"AccountServer", Argument_AccountServer)
bool Argument_AccountServer(std::wstring value)
{
	wchar_t sBuffer[1024];
	wcscpy(sBuffer, value.c_str());
	sBuffer[value.length()] = L'\0';

	wchar_t* cashedAccountServerIP = nullptr;
	wchar_t* cashedAccountServerPort = nullptr;

	ServerArguments index = ServerArguments::IPADDRESS;
	for (wchar_t* sTemp = wcstok(sBuffer, L";"); sTemp != NULL; sTemp = wcstok(NULL, L";"))
	{
		std::wstring sTempStr(sTemp);
		trim(sTempStr);
		wchar_t* sTempBuffer = new wchar_t[sTempStr.length() + 1];
		wcscpy(sTempBuffer, sTempStr.c_str());
		sTempBuffer[sTempStr.length()] = L'\0';

		switch (index)
		{
		case ServerArguments::IPADDRESS:
			cashedAccountServerIP = sTemp;
			break;
		case ServerArguments::PORT:
			cashedAccountServerPort = sTemp;
			break;
		default:
			delete[] sTempBuffer;
			break;//인자가 너무 많다!!
		}

		index = (ServerArguments)((__int32)index + 1);
	}
	if (index == ServerArguments::MAX)
	{
		gAccountServerIP = cashedAccountServerIP;
		gAccountServerPort = cashedAccountServerPort;
		return true;
	}

	delete[] cashedAccountServerIP;
	delete[] cashedAccountServerPort;
	return false;
}

DECLARE_ARGUMENT_OPTION(L"ChannelServer", Argument_ChannelServer)
bool Argument_ChannelServer(std::wstring value)
{
	wchar_t sBuffer[1024];
	wcscpy(sBuffer, value.c_str());
	sBuffer[value.length()] = L'\0';

	wchar_t* cashedChannelServerIP = nullptr;
	wchar_t* cashedChannelServerPort = nullptr;

	ServerArguments index = ServerArguments::IPADDRESS;
	for (wchar_t* sTemp = wcstok(sBuffer, L";"); sTemp != NULL; sTemp = wcstok(NULL, L";"))
	{
		std::wstring sTempStr(sTemp);
		trim(sTempStr);
		wchar_t* sTempBuffer = new wchar_t[sTempStr.length() + 1];
		wcscpy(sTempBuffer, sTempStr.c_str());
		sTempBuffer[sTempStr.length()] = L'\0';

		switch (index)
		{
		case ServerArguments::IPADDRESS:
			cashedChannelServerIP = sTemp;
			break;
		case ServerArguments::PORT:
			cashedChannelServerPort = sTemp;
			break;
		default:
			delete[] sTempBuffer;
			break;//인자가 너무 많다!!
		}

		index = (ServerArguments)((__int32)index + 1);
	}
	if (index == ServerArguments::MAX)
	{
		gChannelServerIP = cashedChannelServerIP;
		gChannelServerPort = cashedChannelServerPort;
		return true;
	}

	delete[] cashedChannelServerIP;
	delete[] cashedChannelServerPort;
	return false;
}

DECLARE_ARGUMENT_OPTION(L"GameServer", Argument_GameServer)
bool Argument_GameServer(std::wstring value)
{
	wchar_t sBuffer[1024];
	wcscpy(sBuffer, value.c_str());
	sBuffer[value.length()] = L'\0';

	wchar_t* cashedGameServerIP = nullptr;
	wchar_t* cashedGameServerPort = nullptr;

	ServerArguments index = ServerArguments::IPADDRESS;
	for (wchar_t* sTemp = wcstok(sBuffer, L";"); sTemp != NULL; sTemp = wcstok(NULL, L";"))
	{
		std::wstring sTempStr(sTemp);
		trim(sTempStr);
		wchar_t* sTempBuffer = new wchar_t[sTempStr.length() + 1];
		wcscpy(sTempBuffer, sTempStr.c_str());
		sTempBuffer[sTempStr.length()] = L'\0';

		switch (index)
		{
		case ServerArguments::IPADDRESS:
			cashedGameServerIP = sTemp;
			break;
		case ServerArguments::PORT:
			cashedGameServerPort = sTemp;
			break;
		default:
			delete[] sTempBuffer;
			break;//인자가 너무 많다!!
		}

		index = (ServerArguments)((__int32)index + 1);
	}
	if (index == ServerArguments::MAX)
	{
		gGameServerIP = cashedGameServerIP;
		gGameServerPort = cashedGameServerPort;
		return true;
	}

	delete[] cashedGameServerIP;
	delete[] cashedGameServerPort;
	return false;
}

