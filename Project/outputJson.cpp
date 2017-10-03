#include <stdlib.h>
#include <iostream>
#include <jsoncpp/json/json.h>
#include "outputJson.h"
#include "definition.h"
using namespace std;

extern addmitted addmitted_department[25];

/*
 *  Function Name: output
 *	Used to output JSON to the assigned file
 */
bool outputJsonFile::output(const char* jsonFile, int unlucky_student_number, string unlucky_student[310], addmitted addmitted_department[25], int unlucky_department_number, string unlucky_department[25]) {
	Json::Value root;

	// unlucky students
	for (int i = 0; i < unlucky_student_number; i++) {
		root["unlucky_student"].append(Json::Value(unlucky_student[i]));
	}

	// admitted
	Json::Value addmittedJson;
	for (int i = 0; i < 20; i++) {
		Json::Value addmittedJson_instance;
		
		// append student number
		int totalNumber = addmitted_department[i].number;
		for (int j = 0; j < totalNumber; j++) {
			addmittedJson_instance["member"].append(Json::Value(addmitted_department[i].student_number[j]));
		}

		// append department number
		addmittedJson_instance["department_no"].append(Json::Value(addmitted_department[i].department_number));

		// append addmittedJson_instance to addmittedJson
		addmittedJson.append(Json::Value(addmittedJson_instance));
	}

	// link addmittedJson to root
	root["addmitted"] = Json::Value(addmittedJson);

	// unlucky departments
	for (int i = 0; i < unlucky_department_number; i++) {
		root["unlucky_department"].append(Json::Value(unlucky_department[i]));
	}

	// output to .json file
	Json::StyleWriter jsonWriter;

	ofstream outputstream;
	outputstream.open(jsonFile);
	outputstream << jsonWriter.write(root);
	outputstream.close();

	return true;
}