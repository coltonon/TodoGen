#include "SourceBrowser.hpp"
#include "ProgramOptions.hpp"

SourceBrowser::SourceBrowser(const std::filesystem::path& searchPath)
{
	this->topDirectory = searchPath;

	// foreach recursive
	for (const std::filesystem::directory_entry& dirEntry : 
		std::filesystem::recursive_directory_iterator(this->topDirectory))
	{
		// inc the total file counter
		this->totalFilesInDir++;

		if (dirEntry.is_regular_file() && dirEntry.path().has_extension()) {
			// create a bool to determine if the file has a supported extension and was read
			bool fileRead = false;

			// ctor will perform everything
			SourceFile srcFile(dirEntry.path(), &fileRead);

			// inc the totalFilesRead num if it was read
			if (fileRead) this->totalFilesRead++;

			if (fileRead && ProgramOptions::GetInstance()()->verbose) {
				std::wcout << L"Reading File: " << dirEntry.path() << std::endl;
			}

			// if there were Todo items found, push it into the vector
			if (!srcFile.items.empty())
				this->sourceFiles.push_back(srcFile);
		}
	}
}