#include "TodoItem.hpp"
#include "StringUtil.hpp"

std::vector<TodoItem> TodoItem::getTodos(const std::filesystem::path& filePath, LangDef language) {
	// output vector of todo items
	std::vector<TodoItem> items;

	// open the file
	std::ifstream stream(filePath);

	// postfixes to append to the end of a comment
	const static std::vector<std::wstring> postFixes = {
		L"todo:", L" todo:", L" todo :"
	};

	// keep track of line numbers
	int lineNumber = 1;
	for (std::string line; std::getline(stream, line); lineNumber++) {
		std::wstring uline = StringUtil::s2ws(line);

		// foreach prefix in the lang
		for (const std::wstring& commentPrefix : language.prefixes) {
			// if the line doesn't start with a comment, continue
			if (uline.find(commentPrefix) == std::wstring::npos) continue;

			// lowercase the string to look for the full comment
			std::wstring lowerLine = uline;
			std::transform(lowerLine.begin(), lowerLine.end(), lowerLine.begin(), ::tolower);

			// foreach postfix:
			for (const std::wstring& commentPostfix : postFixes) {
				// append the prefix and postfix
				std::wstring query = commentPrefix + commentPostfix;

				// look for the comment start
				std::size_t foundPos = lowerLine.find(query);
				if (foundPos != std::wstring::npos) {

					std::wstring message = uline.substr(foundPos + query.length() + 1);
					items.push_back({ message, lineNumber });
				}
			}
		}
	}
	return items;
}