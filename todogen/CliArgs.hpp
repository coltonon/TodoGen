#pragma once
#include "TodoGen.hpp"

class CliArgs : public std::vector<std::wstring> {
public:
	using std::vector<std::wstring>::vector;
	CliArgs(int argc, wchar_t** argv) {
		this->reserve(argc);
		for (int i = 0; i < argc; i++) this->push_back(argv[i]);
	}

	bool hasFlag(const std::wstring& str) {
		return std::find(this->begin(), this->end(), str) != this->end();
	}

	bool hasFlag(const std::wstring& shortFlag, const std::wstring& longFlag) {
		return this->hasFlag(shortFlag) || this->hasFlag(longFlag);
	}


};