#pragma once
#include "Generator.hpp"

class MarkDownGenerator : public Generator {
public:
	using Generator::Generator;

	virtual Generator::Info getGenInfo() override {
		Generator::Info genInfo;
		genInfo.name = L"Markdown";
		genInfo.cmdlineNames = { L"-m", L"--markdown" };
		genInfo.description = L"Output results in a Markdown table";
		return genInfo;
	}

	virtual std::wstring getText() override {
		std::wstringstream ss;
		ss << "# Todo Tracker\n\n";
		ss << Generator::GetGenMessage() << "\n\n";

		for (const SourceFile& srcFile : this->pSrcBrowser->sourceFiles) {
			if (srcFile.items.empty()) continue;

			// get the relative path of the selected file
			std::filesystem::path relPath = std::filesystem::relative(srcFile.fileName, this->pSrcBrowser->topDirectory);

			std::wstring fixedPath = StringUtil::FixSlashes(relPath);
			ss << "\n## [" << fixedPath << "](/" << fixedPath << ")\n";

			ss << "|Line|Message|\n|---|---|" << std::endl;
			for (const TodoItem& todo : srcFile.items) {
				ss << "| [" << todo.lineNumber << "](/"<< fixedPath << "#L"<< todo.lineNumber << ") | " << todo.message.substr(0, todo.message.size() - 1) << " |" << std::endl;
			}
		}

		return ss.str();
	}


	virtual bool isOutputSupported() override { return true; }

	virtual std::filesystem::path getOutputDirectory() override {
		return std::filesystem::absolute(this->pSrcBrowser->topDirectory.wstring() + L"/docs/");
	}

	virtual std::wstring getOutputFilename() override {
		return L"todo.md";
	}
	
};