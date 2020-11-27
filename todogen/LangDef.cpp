#include "LangDef.hpp"

std::vector<LangDef> LangDef::LangDefs = 
{
	{
		L"C++",
		{L".cpp", L".hpp"},
		{L"//"}
	},
	{
		L"C",
		{L".c", L".h"},
		{L"//"}
	}
};

Nullable<LangDef> LangDef::findLanguage(const std::filesystem::path& filePath) 
{
	if (!filePath.has_extension()) return { false };
	std::wstring fileExtension = filePath.extension().wstring();

	for (const LangDef& lang : LangDef::LangDefs) {
		for (const std::wstring& ext : lang.extensions) {
			if (ext == fileExtension) return lang;
		}
	}
	return { false };
}
