#include "ProgramOptions.hpp"


ProgramOptions::ProgramOptions(const CliArgs& cliArgs, const std::filesystem::path selectedDir) {
	this->args = cliArgs;
	this->selectedDirectory = selectedDir;
	this->writeToFile = this->args.hasFlag(L"-w", L"--write");
	this->verbose = this->args.hasFlag(L"-v", L"--verbose");

	for (Generator* pGen : Generator::Generators) {
		Generator::Info genInfo = pGen->getGenInfo();
		if (this->args.hasFlag(genInfo.cmdlineNames[0], genInfo.cmdlineNames[1])) {
			pGen->active = true;
		}
	}

	ProgramOptions::defaultInstance = this;
}

std::wostream& operator<<(std::wostream& wos, const ProgramOptions& obj) {
	wos << RCOLOR_LOG << "Program Settings:" << REND;
	wos << RCOLOR_LOG << "Selected Directory: " << rang::fgB::yellow << obj.selectedDirectory << REND;

	for (Generator* pGen : Generator::Generators) {
		Generator::Info info = pGen->getGenInfo();
		wos << RCOLOR_LOG << "Generate " << info.name << ": ";// << PrintBool(pGen->active) << REND;
		std::wcout << PrintBool(pGen->active);
		wos << REND;
	}
	wos << RCOLOR_LOG << "Write to File: " << PrintBool(obj.writeToFile) << REND;
	return wos;
}


void ProgramOptions::writeDataToFile(const std::wstring& data, Generator* pGenerator) {
	std::filesystem::path outputPath = std::filesystem::absolute(pGenerator->getOutputDirectory().wstring() + L"/" + pGenerator->getOutputFilename());
	std::wcout << RCOLOR_LOG << "Output file: " << RCOLOR_DATA << outputPath << REND;

	std::filesystem::path queryDirectory = outputPath.parent_path();
	if (!std::filesystem::exists(queryDirectory)) {
		std::wcout << RCOLOR_ERR << "Output directory " << RCOLOR_DATA << queryDirectory << RCOLOR_ERR <<
			" does not exist, creating." << REND;
		if (!std::filesystem::create_directory(queryDirectory)) {
			std::wcout << RCOLOR_ERR << "Could not create directory" << REND;
			return;
		}
	}

	// todo: Output as wide to avoid this translation?
	std::ofstream ofs(outputPath);
	if (!ofs.good()) {
		std::wcout << RCOLOR_ERR << "Could not open output file!" << REND;
		return;
	}
	ofs << StringUtil::ws2s(data);
	ofs.close();
	std::wcout << RCOLOR_LOG << "Output file written" << REND;
}

ProgramOptions* ProgramOptions::defaultInstance = nullptr;

Nullable<ProgramOptions*> ProgramOptions::GetInstance() {
	if (ProgramOptions::defaultInstance == nullptr) return { false };
	return { ProgramOptions::defaultInstance };
}