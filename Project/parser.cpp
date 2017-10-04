#include <stdlib.h>
#include <iostream>
#include <sstream>
#include "definition.h"
#include "parser.h"
using namespace std;

extern students student[310];
extern departments department[25];
extern addmitted addmitted_department[25];

// string example: 'Wed.16:00~18:00'

/*
 *  Function Name: parseWeekday
 *  parse the weekday(eg.Sunday:0, Monday:1, ...) from string
 */
int parser::parseWeekday(string free_time) {
	int weekday = -1;
	string weekday_str = "";

	// for each char in free_time
	for (int i = 0; i < free_time.length(); i++) {
		if (free_time[i] == '.') break;
		// join the current char to weekday
		weekday += free_time[i];
	}

	stringstream ss;
	ss << weekday_str;
	ss >> weekday;

	return weekday;
}

/*
 *  Function Name: parseStartTime
 *  parse the start time(min) from string
 */
int parser::parseStartTime(string free_time) {
	int start_time = -1;
	int start_time_hour = -1;
	int start_time_minute = -1;
	// is the point('.') occurred?
	bool isPointOccurred = false;
	// is the partition char(':') occurred?
	bool isPartitionCharOccurred = false;
	string start_time_str_prefix = "";
	string start_time_str_suffix = "";

	// for each char in free_time
	for (int i = 0; i < free_time.length(); i++) {
		// if the current char == '.', mark the isPointOccurred as true
		if (free_time[i] == '.') {
			isPointOccurred = true;
			continue;
		}

		// if the point has not occured, continue
		if (!isPointOccurred) continue;

		// if the current char == '~', break
		if (free_time[i] == '~') break; 

		// if the current char == ':', mark the isPartitionCharOccurred as true
		if (free_time[i] == ':') {
			isPartitionCharOccurred = true;
			continue;
		}

		// if the isPartitionCharOccurred == false, 
		// join the char to start_time_str_prefix
		if (!isPartitionCharOccurred) {
			start_time_str_prefix += free_time[i];
		} else { // otherwise, join to start_time_str_suffix
			start_time_str_suffix += free_time[i];
		}
	}
	
	stringstream ss;
	ss << start_time_str_prefix;
	ss >> start_time_hour;
	ss << start_time_str_suffix;
	ss >> start_time_minute;

	// calculate total minutes
	start_time = start_time_hour*60+start_time_minute;
	return start_time;
}

/*
 *  Function Name: parseEndTime
 *  parse end time(min) from string
 */
int parser::parseEndTime(string free_time) {
	int end_time = -1;
	int end_time_hour = -1;
	int end_time_minute = -1;
	// is the '~' occurred?
	bool isPointOccurred = false;
	// is the partition char(':') occurred?
	bool isPartitionCharOccurred = false;
	string end_time_str_prefix = "";
	string end_time_str_suffix = "";

	for (int i = 0; i < free_time.length(); i++) {
		// if the current char == '~', mark the isPointOccurred as true
		if (free_time[i] == '~') {
			isPointOccurred = true;
			continue;
		}
		
		// if '~' has not occured, continue
		if (!isPointOccurred) continue;

		// if the current char == ':', mark the isPartitionCharOccurred as true
		if (free_time[i] == ':') {
			isPartitionCharOccurred = true;
			continue;
		}

		// if the isPartitionCharOccurred == false, 
		// join the char to end_time_str_prefix
		if (!isPartitionCharOccurred) {
			end_time_str_prefix += free_time[i];
		} else { // otherwise, join to end_time_str_suffix
			end_time_str_suffix += free_time[i];
		}
	}

	stringstream ss;
	ss << end_time_str_prefix;
	ss >> end_time_hour;
	ss << end_time_str_suffix;
	ss >> end_time_minute;

	// calculate total minutes
	end_time = end_time_hour*60+end_time_minute;
	return end_time;
}
