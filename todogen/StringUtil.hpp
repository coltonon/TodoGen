#pragma once
#include "TodoGen.hpp"

// todo: Fix s2ws and ws2s to not use codecvt, so this isn't necescary 
#pragma warning(disable: 4996)

class StringUtil {
public:
	// replace backslashes with forward slashes
	static std::wstring FixSlashes(const std::filesystem::path& path) {
		std::wstring pathStr = path.wstring();
		std::replace(pathStr.begin(), pathStr.end(), '\\', '/');
		return pathStr;
	}

	// string to wide string
	static std::wstring s2ws(const std::string& str)
	{
		using convert_typeX = std::codecvt_utf8<wchar_t>;
		std::wstring_convert<convert_typeX, wchar_t> converterX;

		return converterX.from_bytes(str);
	}

	// wide string to string
	static std::string ws2s(const std::wstring& wstr)
	{
		using convert_typeX = std::codecvt_utf8<wchar_t>;
		std::wstring_convert<convert_typeX, wchar_t> converterX;

		return converterX.to_bytes(wstr);
	}
};
