#pragma once
// Utilities.h

#include <functional>
#include <iostream>
#include <time.h>

/////////////////////////////////////////////////////////////////////
// lambdas that provide mildly useful local processing

/////////////////////////////////////////////////////////////////////
// lambdas that provide mildly useful local processing
/*
* Maintenance History :
*= = == == == == == == == == == == == == ==
*ver 1.0 : 30 Jam 17
* -first release
*ver 1.1 : 08 Feb 17
* added method - trim method to trim left and right whitespace of a string
* added method - time_t makeTime(int year, int mon, int day, int hour, int min, int sec)
*/


std::function<void()> putLine = []() { std::wcout << "\n"; };

std::function<void(size_t)> putLines = [](size_t n) {
  for (size_t i = 0; i < n; ++i)
    putLine();
};

std::function<void(const std::string&, char)> titleCore = [](const std::string& msg, char underline = '-') {
  std::cout << "\n  " << msg.c_str();
  std::wcout << "\n " << std::string(msg.size() + 2, underline).c_str();
};

std::function<void(const std::string&)> Title = [](const std::string& msg) { titleCore(msg, '='); };

std::function<void(const std::string&)> subTitle = [](const std::string& msg) { titleCore(msg, '-'); };

std::string trim(const std::string& str,
	const std::string& whitespace = " \n")
{
	const auto strBegin = str.find_first_not_of(whitespace);
	if (strBegin == std::string::npos)
		return ""; // no content

	const auto strEnd = str.find_last_not_of(whitespace);
	const auto strRange = strEnd - strBegin + 1;

	return str.substr(strBegin, strRange);
}

time_t makeTime(int year, int mon, int day, int hour, int min, int sec) {
	struct tm y2k = { 0 };
	y2k.tm_hour = hour;
	y2k.tm_sec = sec;
	y2k.tm_min = min;
	y2k.tm_mday = day;
	y2k.tm_mon = mon;
	y2k.tm_year = year;
	time_t ret = mktime(&y2k);
	return ret;
}