#pragma once

#include "GPGame.h"

#include <string>
#include <algorithm>
#include <map>
#include <utility>

enum ServerArguments
{
	IPADDRESS,
	PORT,
	MAX
};

struct _ArgumentPair
{
	std::wstring m_sKey;
	std::wstring m_sValue;

	_ArgumentPair(wchar_t* Key, wchar_t* Value) :
		m_sKey(Key), m_sValue(Value)
	{
		std::transform(m_sKey.begin(), m_sKey.end(), m_sKey.begin(), towupper);
		std::transform(m_sValue.begin(), m_sValue.end(), m_sValue.begin(), towupper);

		std::trim(m_sKey);
		std::trim(m_sValue);
	}
};

struct _ArgumentRegister
{
	typedef bool (*Functor)(std::wstring);
	typedef std::map< std::wstring, Functor > FuncMap;
	
	static FuncMap* getFunctionMap()
	{
		static FuncMap map;
		return &map;
	}

	_ArgumentRegister(std::wstring Key, Functor Func)
	{
		FuncMap* map = getFunctionMap();
		std::transform(Key.begin(), Key.end(), Key.begin(), towupper);
		std::trim(Key);
		map->insert( std::make_pair(Key, Func) );
	}

	static void exec(_ArgumentPair args)
	{
		FuncMap* map = getFunctionMap();
		if (map->find(args.m_sKey) != map->end())
		{
			bool bResult = (*map)[args.m_sKey](args.m_sValue);
			if (bResult == false)
			{
				// Argument 초기화 루틴이 정상적으로 일어나지 않은 경우
			}
		}
		else
		{
			// Argument를 찾지 못한 경우
		}
	}

	static void process(int argc, char* argv[])
	{
		for (int i = 1; i < argc; i++)
		{
			std::wstring str(argv[i], argv[i] + strlen(argv[i]));
			wchar_t* sBuffer = new wchar_t[str.length() + 1];
			wcscpy(sBuffer, str.c_str());

			wchar_t *sLHS, *sRHS;

			int index = 0;
			for (wchar_t* sTemp = wcstok(sBuffer, L"="); sTemp; sTemp = wcstok(NULL, L"="))
			{
				std::wstring sTempStr(sTemp);
				trim(sTempStr);
				wchar_t* sTempBuffer = new wchar_t[sTempStr.length() + 1];
				wcscpy(sTempBuffer, sTempStr.c_str());
				sTempBuffer[sTempStr.length()] = L'\0';

				switch (index)
				{
				case 0:
					sLHS = sTempBuffer;
					break;
				case 1:
					sRHS = sTempBuffer;
					break;
				default :
					delete[] sTempBuffer;
					// a = b = c처럼 입력한게 아닐까?
					break;
				}

				index++;
			}

			if (index == 2)
			{
				exec(_ArgumentPair(sLHS, sRHS));
			}
			else
			{
				//괴상한 모양일 것이다. 여기 들어오는걸 체크하면 될거임
			}

			delete[] sLHS;
			delete[] sRHS;
		}
	}
};

#define DECLARE_ARGUMENT_OPTION(ID, FN) \
bool FN(std::wstring);\
_ArgumentRegister __ARGMACRO_##FN(ID, FN);