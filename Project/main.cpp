// main.c
#include <stdlib.h>
#include <iostream>
#include "jsonHandler.h"
#include "definition.h"
using namespace std;

int main() {
	jsonHandler jsonHandler_instance;
	if (jsonHandler_instance.processJSON("input_data.json")) {
		for (int i = 0; i < 300; i++) {
			cout << "==================================================" << endl;
			cout << "student.student_number:" << student[i].student_number << endl;
			cout << "student.applications_department_number:" << student[i].applications_department_number << endl;
			cout << "student.applications_department[last]:" << student[i].applications_department[student[i].applications_department_number-1] << endl;
			cout << "student.tag_number:" << student[i].tag_number << endl;
			cout << "student.tag[last]:" << student[i].tags[student[i].tag_number-1] << endl;
			cout << "student.free_time_number:" << student[i].free_time_number << endl;
			cout << "student.free_time[last]:" << student[i].free_time[student[i].free_time_number-1] << endl;
			cout << "==================================================" << endl;
		}
	} else {
		cout << "Error: JSON file processing error!";
		return 1;
	}
	return 0;
}