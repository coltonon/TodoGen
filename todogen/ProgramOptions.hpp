#pragma once
#include "TodoGen.hpp"
#include "Nullable.hpp"
#include "CliArgs.hpp"
#include "PrintBool.hpp"
#include "Generator.hpp"

class ProgramOptions {
private:
	static ProgramOptions* defaultInstance;
	CliArgs args;
public:
	std::filesystem::path selectedDirectory;
	bool writeToFile;
	bool verbose;

	void writeDataToFile(const std::wstring& data, Generator* pGenerator);

	ProgramOptions(const CliArgs& cliArgs, const std::filesystem::path selectedDir);

	friend std::wostream& operator<<(std::wostream& os, const ProgramOptions& obj);

	static Nullable<ProgramOptions*> GetInstance();
};
