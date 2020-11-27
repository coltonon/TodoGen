#pragma once
#include "TodoItem.hpp"

class SourceFile {
public:
	std::filesystem::path fileName;
	std::vector<TodoItem> items;
	LangDef language;

	SourceFile(const std::filesystem::path& file, bool* fileRead = nullptr);
};