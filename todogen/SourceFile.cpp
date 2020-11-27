#include "SourceFile.hpp"

SourceFile::SourceFile(const std::filesystem::path& file, bool* fileRead) {
	this->fileName = file;

	Nullable<LangDef> lang = LangDef::findLanguage(this->fileName);
	if (lang.isValid) {
		this->language = lang();

		if (fileRead != nullptr) *fileRead = true;
		this->items = TodoItem::getTodos(this->fileName, this->language);
	}
}