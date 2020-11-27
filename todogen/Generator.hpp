#pragma once
#include "SourceBrowser.hpp"
#include "StringUtil.hpp"

class Generator {
protected:
	SourceBrowser* pSrcBrowser = nullptr;
public:
	struct Info {
		std::wstring name;
		std::array<std::wstring, 2> cmdlineNames;
		std::wstring description;
	};

	Generator(){}
	// ctor
	bool active = false;
	void attach(SourceBrowser* browser) { this->pSrcBrowser = browser; }

	// override this func in each inherited class
	virtual std::wstring getText() = 0;
	virtual bool isOutputSupported() = 0;

	virtual Info getGenInfo() = 0;

	// todo: add docs
	virtual std::filesystem::path getOutputDirectory() { return std::filesystem::path(); }
	virtual std::wstring getOutputFilename() { return NULL; }

	// static funcs for getting code generation time
	static std::wstring GetTimeStr();
	static std::wstring GetGenMessage();
	static std::vector<Generator*> Generators;
};