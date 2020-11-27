#pragma once
#include "TodoGen.hpp"
#include "Nullable.hpp"

class LangDef {
public:
	std::wstring name;
	std::vector<std::wstring> extensions;
	std::vector<std::wstring> prefixes;

	static std::vector<LangDef> LangDefs;
	static Nullable<LangDef> findLanguage(const std::filesystem::path& filePath);
};