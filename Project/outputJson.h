#ifndef OUTPUTJSON_H
#define OUTPUTJSON_H
#include <stdlib.h>
#include <iostream>
using namespace std;

extern addmitted addmitted_department[25];

class outputJsonFile {
public:
	outputJsonFile() { };
	bool output(const char* jsonFile, int unlucky_student_number, string unlucky_student[310], addmitted addmitted_department[25], int unlucky_department_number, string unlucky_department[25]);
};

#endif OUTPUTJSON_H
