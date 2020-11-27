#include "SourceBrowser.hpp"
#include "ProgramOptions.hpp"


void showHelpScreen() {

	// show options
	std::wcout << rang::fgB::magenta << "Options:" << REND;
	std::wcout << rang::fgB::green << "Short\tLong\t\tDesc" << REND;

	std::wcout << "-h\t--help\t\tShows this help screen" << std::endl;
	std::wcout << "-w\t--write\t\tWrites the output data to a predetermined file" << std::endl;
	std::wcout << "-g\t--git\t\tSame as -m & -w, useful for Visual Studio build events" << std::endl;

	std::wcout << std::endl << rang::fgB::magenta << "Generators:" << REND;
	std::wcout << rang::fgB::green << "Short\tLong\t\tDesc" << REND;

	for (Generator* pGen : Generator::Generators) {
		Generator::Info info = pGen->getGenInfo();
		std::wcout << info.cmdlineNames[0] << "\t" << info.cmdlineNames[1] << "\t";
		if (info.cmdlineNames[1].length() > 4) std::wcout << "\t";
		std::wcout << info.description << std::endl;
	}
}


#if defined(__unix__) || defined(__unix) || defined(__linux__)
int main(int argc, char** argv) {
	CliArgs args;
	args.reserve(argc);
	for (int i = 0; i < argc; i++) args.push_back(StringUtil::s2ws(argv[i]));
#else

int wmain(int argc, wchar_t** argv) {
	_setmode(_fileno(stdout), _O_WTEXT);
	CliArgs args(argc, argv);
#endif

	std::wcout << rang::fgB::cyan << "Todo Generator " << RCOLOR_LOG << "v" << TOOL_VERSION << REND << std::endl;

	if (args.hasFlag(L"-h", L"--help")) {
		showHelpScreen();
		return 0;
	}

	if (args.hasFlag(L"-g", L"--git")) {
		if (!args.hasFlag(L"-m", L"--markdown")) args.push_back(L"-m");
		if (!args.hasFlag(L"-w", L"--write")) args.push_back(L"-w");
	}

	// todo: Let the user input a custom path
	std::filesystem::path selectedDir = std::filesystem::current_path();
	ProgramOptions options(args, selectedDir);
	std::wcout << options << std::endl;

	// ctor will perform everything
	SourceBrowser srcBrowser(selectedDir);

	// todo: Add some docs here
	std::wcout << RCOLOR_DATA << "\t" << srcBrowser.totalFilesInDir << RCOLOR_LOG << " Total files found" << REND;
	std::wcout << RCOLOR_DATA << "\t" << srcBrowser.totalFilesRead << RCOLOR_LOG << " Files with supported extensions read" << REND;
	std::wcout << RCOLOR_DATA << "\t" << srcBrowser.sourceFiles.size() << RCOLOR_LOG << " Files with TODO items" << REND;
	std::wcout << std::endl;

	

	for (Generator* pGen : Generator::Generators) {
		if (pGen->active) {
			pGen->attach(&srcBrowser);
			std::wstring data = pGen->getText();

			if (options.verbose || pGen->getGenInfo().name == L"Console") std::wcout << data << std::endl;

			if (options.writeToFile) {
				options.writeDataToFile(data, pGen);
			}
		}
	}
	

	std::wcout << RCOLOR_LOG << "TodoGen finished" << REND;
	return 0;
}
