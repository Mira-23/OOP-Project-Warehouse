#pragma once
#include <iostream>
#include <string>
#include <sstream>
#include <map>
#include <vector>
#include <ctime>
#include <iomanip>
#include <time.h>

/// <summary>
/// A seperate class made for easier implementation of logging changes
/// </summary>
class ChangeLog
{
public:
	void submitChange(std::string command, std::string target);
	void submitChange(std::string command, std::string target, double quantity);

	void printLog(std::string from, std::string to, std::ostream& os) const;
private:
	std::map<std::time_t, std::string> datedMessages;
};

