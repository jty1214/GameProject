#pragma once

#include <algorithm> 
#include <functional> 
#include <cctype>
#include <locale>

namespace std
{
	// trim from start
	static inline std::wstring &ltrim(std::wstring &s) {
		s.erase(s.begin(), std::find_if(s.begin(), s.end(), std::not1(std::ptr_fun<int, int>(std::isspace))));
		return s;
	}

	// trim from end
	static inline std::wstring &rtrim(std::wstring &s) {
		s.erase(std::find_if(s.rbegin(), s.rend(), std::not1(std::ptr_fun<int, int>(std::isspace))).base(), s.end());
		return s;
	}

	// trim from both ends
	static inline std::wstring &trim(std::wstring &s) {
		return ltrim(rtrim(s));
	}
}