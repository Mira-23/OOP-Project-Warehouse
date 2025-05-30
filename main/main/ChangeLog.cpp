#include "ChangeLog.h"

void ChangeLog::submitChange(std::string command, std::string product)
{
	std::string line = command + " product " + product;
	std::time_t currentTime = std::time(0);

	std::tm daymonthYear;
	localtime_s(&daymonthYear, &currentTime);

	daymonthYear.tm_hour = 0;
	daymonthYear.tm_min = 0;
	daymonthYear.tm_sec = 0;

	std::time_t onlyDate = mktime(&daymonthYear);

	datedMessages.insert({ currentTime, line });
}

void ChangeLog::submitChange(std::string command, std::string product, double quantity)
{
	std::string line = command + " product " + product + " by quantity: " + std::to_string(quantity);

	std::time_t currentTime = std::time(0);

	std::tm daymonthYear;
	localtime_s(&daymonthYear, &currentTime);

	daymonthYear.tm_hour = 0;
	daymonthYear.tm_min = 0;
	daymonthYear.tm_sec = 0;

	std::time_t onlyDate = mktime(&daymonthYear);

	datedMessages.insert({ onlyDate, line });
}

void ChangeLog::printLog(std::string from, std::string to) const
{
	struct tm fromDate;
	fromDate.tm_hour = 0;
	fromDate.tm_min = 0;
	fromDate.tm_sec = 0;

	struct tm toDate;
	toDate.tm_hour = 0;
	toDate.tm_min = 0;
	toDate.tm_sec = 0;

	std::istringstream ss1(from);
	ss1 >> std::get_time(&fromDate, "%d/%m/%Y");

	std::istringstream ss2(to);
	ss2 >> std::get_time(&toDate, "%d/%m/%Y");

	std::time_t fromTime = mktime(&fromDate);
	std::time_t toTime = mktime(&toDate);

	//this is bad practice. but I am unable to type out the entire type of this
	for (auto& m : datedMessages)
	{
		std::tm daymonthYear;
		localtime_s(&daymonthYear, &(m.first));

		if (m.first >= fromTime && m.first <= toTime)
		{
			std::cout << daymonthYear.tm_mday << "/" << daymonthYear.tm_mon + 1 << "/" << daymonthYear.tm_year + 1900 << " " << m.second << std::endl;
		}
	}
}
