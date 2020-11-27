#pragma once
#include "Generator.hpp"
#include "json.hpp"

class JsonGenerator : public Generator {
public:
	using Generator::Generator;

	virtual Generator::Info getGenInfo() override {
		Generator::Info genInfo;
		genInfo.name = L"JSON";
		genInfo.cmdlineNames = { L"-j", L"--json" };
		genInfo.description = L"Output results as a JSON object";
		return genInfo;
	}

	std::wstring getText() override {
		nlohmann::json rootJsonObj;
		rootJsonObj["time"] = StringUtil::ws2s(Generator::GetTimeStr());

		for (const SourceFile& srcFile : this->pSrcBrowser->sourceFiles) {
			if (srcFile.items.empty()) continue;

			// get the relative path of the selected file
			std::filesystem::path relPath = std::filesystem::relative(srcFile.fileName, this->pSrcBrowser->topDirectory);

			nlohmann::json fileJsonObject;
			fileJsonObject["filename"] = StringUtil::ws2s(StringUtil::FixSlashes(relPath));

			for (const TodoItem& todo : srcFile.items) {
				nlohmann::json todoJsonObject;
				todoJsonObject["line"] = todo.lineNumber;
				todoJsonObject["message"] = StringUtil::ws2s(todo.message);
				fileJsonObject["todos"].push_back(todoJsonObject);
			}
			rootJsonObj["files"].push_back(fileJsonObject);
		}

		return StringUtil::s2ws(rootJsonObj.dump(4));
	}


	virtual bool isOutputSupported() override { return true; }

	virtual std::filesystem::path getOutputDirectory() override {
		return this->pSrcBrowser->topDirectory;
	}
	virtual std::wstring getOutputFilename() override {
		return L"todo.json";
	}

};