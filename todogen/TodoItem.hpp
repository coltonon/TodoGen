#pragma once
#include "TodoGen.hpp"
#include "LangDef.hpp"

class TodoItem {
public:
	std::wstring message;
	int lineNumber;

	static std::vector<TodoItem> getTodos(const std::filesystem::path& filePath, LangDef language);
};