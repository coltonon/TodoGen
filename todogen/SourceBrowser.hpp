#pragma once
#include "SourceFile.hpp"

class SourceBrowser {
public:
	std::filesystem::path topDirectory;
	std::vector<SourceFile> sourceFiles;
	int totalFilesInDir = 0;
	int totalFilesRead = 0;
	SourceBrowser(const std::filesystem::path& searchPath = std::filesystem::current_path());
};