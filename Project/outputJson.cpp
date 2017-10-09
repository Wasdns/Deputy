#include <stdlib.h>
#include <fstream>
#include <iostream>
#include <jsoncpp/json/json.h>
#include "definition.h"
#include "outputJson.h"
using namespace std;

extern addmitted addmitted_department[25];

/*
 *  Function Name: output
 *	Used to output JSON to the assigned file
 */
bool outputJsonFile::output(const char* jsonFile, int unlucky_student_number, string unlucky_student[310], addmitted addmitted_department[25], int unlucky_department_number, string unlucky_department[25]) {
	Json::Value root;

	// unlucky students
	Json::Value unluckyStudentJson;
	unluckyStudentJson.resize(0);
	for (int i = 0; i < unlucky_student_number; i++) {
		unluckyStudentJson.append(Json::Value(unlucky_student[i]));
	}

	root["unlucky_student"] = Json::Value(unluckyStudentJson);

	// admitted
	Json::Value addmittedJson;
	for (int i = 0; i < 20; i++) {
		Json::Value addmittedJson_instance;
		
		// append student number
		Json::Value addmittedDepartmentMember;
		addmittedDepartmentMember.resize(0);

		int totalNumber = addmitted_department[i].number;
		for (int j = 0; j < totalNumber; j++) {
			addmittedDepartmentMember.append(Json::Value(addmitted_department[i].student_number[j]));
		}

		addmittedJson_instance["member"] = addmittedDepartmentMember;

		// department number
		addmittedJson_instance["department_no"] = Json::Value(addmitted_department[i].department_number);

		// append addmittedJson_instance to addmittedJson
		addmittedJson.append(Json::Value(addmittedJson_instance));
	}

	// link addmittedJson to root
	root["addmitted"] = Json::Value(addmittedJson);

	// unlucky departments
	Json::Value unluckyDepartmentJson;
	unluckyDepartmentJson.resize(0);
	
	for (int i = 0; i < unlucky_department_number; i++) {
		unluckyDepartmentJson.append(Json::Value(unlucky_department[i]));
	}

	root["unlucky_department"] = Json::Value(unluckyDepartmentJson);

	// output to .json file
	Json::StyledWriter jsonWriter;

	fstream outputStream(jsonFile);
	outputStream << jsonWriter.write(root);
	outputStream.close();

	return true;
}
