#pragma once
#include "TodoGen.hpp"
#include <fcntl.h>

class PrintBool {
public:
	bool value;

	PrintBool(bool v) : value(v) {}

	/*friend std::ostream& operator<<(std::ostream& os, const PrintBool& obj) {
		if (obj.value) return os << rang::fgB::green << "TRUE" << rang::fg::reset;
		return os << rang::fgB::red << "FALSE" << rang::fg::reset;
	}*/

	friend std::wostream& operator<<(std::wostream& wos, const PrintBool& obj) {
		if (obj.value) return wos << rang::fgB::green << wchar_t(0x2713) << rang::fg::reset;
		return wos << rang::fgB::red << wchar_t(0x274C) << rang::fg::reset;
	}
};