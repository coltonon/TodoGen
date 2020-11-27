#pragma once
#include <iostream>
#include <string>
#include <filesystem>
#include <vector>
#include <fstream>
#include <algorithm>
#include <sstream>
#include <ctime>
#include <chrono>
#include <functional>
#include <array>
#include <locale>
#include <codecvt>

#include "Rang.hpp"

// version macros
#ifndef TOOL_VERSION
#define TOOL_VERSION 1.0
#endif


// define some color macros 

#ifndef RST
#define RST rang::fg::reset
#endif

#ifndef REND
#define REND rang::fg::reset << std::endl
#endif

#ifndef RCOLOR_LOG
#define RCOLOR_LOG rang::fgB::blue
#endif

#ifndef RCOLOR_DATA
#define RCOLOR_DATA rang::fgB::yellow
#endif

#ifndef RCOLOR_ERR
#define RCOLOR_ERR rang::fgB::red
#endif