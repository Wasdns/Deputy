// main.c
#include <stdlib.h>
#include <iostream>
#include "definition.h"
#include "jsonHandler.h"
#include "outputJson.h"
using namespace std;

extern students student[310];
extern departments department[25];
extern addmitted addmitted_department[25];

int main() {
	jsonHandler jsonHandler_instance;
	if (jsonHandler_instance.processJSON("test/input_data.json")) {
		for (int i = 0; i < 300; i++) {
			cout << "==================================================" << endl;
			cout << "student.student_number:" << student[i].student_number << endl;
			cout << "student.applications_department_number:" << student[i].applications_department_number << endl;
			cout << "student.applications_department[last]:" << student[i].applications_department[student[i].applications_department_number-1] << endl;
			cout << "student.tag_number:" << student[i].tag_number << endl;
			cout << "student.tags[last]:" << student[i].tags[student[i].tag_number-1] << endl;
			cout << "student.free_time_number:" << student[i].free_time_number << endl;
			cout << "student.free_time[last]:" << student[i].free_time[student[i].free_time_number-1] << endl;
			cout << "==================================================" << endl;
		} 

		cout << "End of parsing students" << endl;

		for (int i = 0; i < 20; i++) {
			cout << "==================================================" << endl;
			cout << "department.department_number:" << department[i].department_number << endl;
			cout << "department.member_limit:" << department[i].member_limit << endl;
			cout << "department.tag_number:" << department[i].tag_number << endl;
			cout << "department.tags[last]:" << department[i].tags[department[i].tag_number-1] << endl;
			cout << "department.event_schedules_number:" << department[i].event_schedules_number << endl;
			cout << "department.event_schedules[last]:" << department[i].event_schedules[department[i].event_schedules_number-1] << endl;
			cout << "==================================================" << endl;
		}
	} else {
		cout << "Error: JSON file processing error!" << endl;
		return 1;
	}
	return 0;
}
