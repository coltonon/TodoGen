#pragma once
#include "Generator.hpp"

class ConsoleGenerator : public Generator {
public:
	using Generator::Generator;

	virtual Generator::Info getGenInfo() override {
		Generator::Info genInfo;
		genInfo.name = L"Console";
		genInfo.cmdlineNames = { L"-c", L"--console" };
		genInfo.description = L"Output results for Console Usage";
		return genInfo;
	}

	virtual std::wstring getText() override {
		std::wstringstream ss;

		for (const SourceFile& srcFile : this->pSrcBrowser->sourceFiles) {
			if (srcFile.items.empty()) continue;

			// get the relative path of the selected file
			std::filesystem::path relPath = std::filesystem::relative(srcFile.fileName, this->pSrcBrowser->topDirectory);

			ss << "File: " << StringUtil::FixSlashes(relPath) << std::endl;

			for (const TodoItem& todo : srcFile.items) {
				ss << "\tLine: " << todo.lineNumber << ": " << todo.message << std::endl;
			}
		}

		return ss.str();
	}


	bool isOutputSupported() override {
		return false;
	}

};