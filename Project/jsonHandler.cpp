#include <stdlib.h>
#include <fstream>
#include <iostream>
#include <jsoncpp/json/json.h>
#include "definition.h"
#include "jsonHandler.h"
using namespace std;

extern students student[310];
extern departments department[25];
extern addmitted addmitted_department[25];

/* 
 *  Function Name: processJSON
 *  Used to process input JSON file 
 */
bool jsonHandler::processJSON(const char* jsonFile) {
	Json::Reader reader;
	Json::Value root;

	// open the JSON file
	ifstream stream;
	stream.open(jsonFile, ios::binary);

	int studentNumber = 300, departmentNumber = 20;

	if (reader.parse(stream, root)) {
		// the input student number != 300, raise exception
		if (root["students"].size() != studentNumber) {
			cout << "Error: Student Number doesn't match!" << endl;
			return false;
		}
		
		// the input department number != 20, raise exception
		if (root["departments"].size() != departmentNumber) {
			cout << "Error: Department Number doesn't match!" << endl;
			return false;
		}

		string student_number;
		int applications_department_number, tag_number, free_time_number;

		// initial each of the students
		for (int i = 0; i < studentNumber; i++) {
			// for each of the instances, initialing corresponding fields
			student_number = root["students"][i]["student_no"].asString();
			student[i].student_number = student_number;

			applications_department_number = root["students"][i]["applications_department"].size();
			student[i].applications_department_number = applications_department_number;

			tag_number = root["students"][i]["tags"].size();
			student[i].tag_number = tag_number;

			free_time_number = root["students"][i]["free_time"].size();
			student[i].free_time_number = free_time_number;

			// initialing the applications_department of each of the students
			for (int j = 0; j < applications_department_number; j++) {
				student[i].applications_department[j] = root["students"][i]["applications_department"][j].asString();
			}

			// initialing the tag of each of the students
			for (int j = 0; j < tag_number; j++) {
				student[i].tags[j] = root["students"][i]["tags"][j].asString();
			}

			// initialing the free_time of each of the students
			for (int j = 0; j < free_time_number; j++) {
				student[i].free_time[j] = root["students"][i]["free_time"][j].asString();
			}
		}

		string department_number;
		int member_limit = 0, event_schedules_number;
		tag_number = 0;

		// initialing each of the departments
		for (int i = 0; i < departmentNumber; i++) {
			// for each of the instances, initialing corresponding fields
			department_number = root["departments"][i]["department_no"].asString();
			department[i].department_number = department_number;

			member_limit = root["departments"][i]["member_limit"].asInt();
			department[i].member_limit = member_limit;

			tag_number = root["departments"][i]["tags"].size();
			department[i].tag_number = tag_number;

			event_schedules_number = root["departments"][i]["event_schedules"].size();
			department[i].event_schedules_number = event_schedules_number;

			// initialing the tag of each of the departments
			for (int j = 0; j < tag_number; j++) {
				department[i].tags[j] = root["departments"][i]["tags"][j].asString();
			}

			// initialing the event_schedules of each of the departments
			for (int j = 0; j < event_schedules_number; j++) {
				department[i].event_schedules[j] = root["departments"][i]["event_schedules"][j].asString();
			}
		}
	} else { // raise parsing error
		cout << "Error: Reader parsing error!" << endl;
		cout << reader.getFormattedErrorMessages() << endl; 
		return false;
	}

	stream.close();

	return true;
}
