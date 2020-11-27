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
		ss << L"# Todo Tracker\n\n";
		ss << Generator::GetGenMessage() << "\n\n";

		for (const SourceFile& srcFile : this->pSrcBrowser->sourceFiles) {
			if (srcFile.items.empty()) continue;

			// get the relative path of the selected file
			std::filesystem::path relPath = std::filesystem::relative(srcFile.fileName, this->pSrcBrowser->topDirectory);

			std::wstring fixedPath = StringUtil::FixSlashes(relPath);
			ss << L"\n## [" << fixedPath << "](" << fixedPath << ")\n";

			for (const TodoItem& todo : srcFile.items) {
				ss << L"|Line|Message|\n|---|---|\n";
				ss << L"| [" << todo.lineNumber << L"]("<< fixedPath << L"#L"<< todo.lineNumber << L") | " << todo.message << " |\n";
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