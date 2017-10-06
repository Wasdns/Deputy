#include <stdlib.h>
#include <iostream>
#include <sstream>
#include <algorithm>
#include <assert.h>
#include "definition.h"
#include "matchAlgorithmTools.h"
#include "matchAlgorithm.h"
using namespace std;

extern students student[310];
extern departments department[25];
extern addmitted addmitted_department[25];

struct student_sorted_t {
	int index;
	int value;
};

student_sorted_t student_sorted[310];

bool cmp(student_sorted_t &student_instance1, student_sorted_t student_instance2) {
	return student_instance1.value > student_instance2.value;
}

void matchAlgorithm::algorithm() {
	matchAlgorithmTools algorithmTool;
	// deliver the students to the two classes
	algorithmTool.deliverStudent();

	/*
	 * The following codes are used to: 
	 *
	 * 1.update studentWishes to calculate the order among departments.
	 *
	 * 2.calculate studentDepValues(student vs department) to find out
	 *   that if the student is matched against the department or not.
	 *   And for the following codes(i.e.L79), the studentDepValues is
	 *   used to help the department choose students.
	 * 
	 */
	
	for (int i = 0; i < algorithmTool.eagerStudentNumber; i++) {
		// current index of eagerStudents
		int currentStudent = i;

		// the total number of departments that chosen by the current student
		int depTotal = algorithmTool.eagerStudent[currentStudent].applications_department_number;
		
		// j: the number of departments
		// k: the number of student wishes

		// for each of the departments
		for (int j = 0; j < 20; j++) {
			int currentDepartment = j;
			// the number of current department 
			string currentDepartment_str = department[currentDepartment].department_number;

			// check if the department is the chosen one or not
			for (int k = 0; k < depTotal; k++) {
				// the k wish of current student
				string kwish = algorithmTool.eagerStudent[currentStudent].applications_department[k];
				
				// if matched, means student "py" department
				if (kwish == currentDepartment_str) {
					// add 1 to studentWishes[department_number: currentDepartment][wishes: k]
					algorithmTool.studentWishes[currentDepartment][k]++;

					// calculate the value between current student and current department
					// based on k(the current number of wishes) and the student instance 
					// and the department instance  
					int stuDepValue = algorithmTool.matchedLevelValue(k, algorithmTool.eagerStudent[currentStudent], department[currentDepartment]);
					assert(stuDepValue != -1);
					// record the stuDepValue calculated by matchedLevelValue(...)
					// in studentDepValues[student_instance_index][department_instance_index]
					algorithmTool.studentDepValues[currentStudent][currentDepartment] = stuDepValue;

					break;
				}
			}
		}
	}

	/*
	 * The following codes are used to: 
	 *
	 * calculate the chosen order among departments, 
	 * eg.department A before department B.
	 * 
	 * StudentWishes => Order
	 *
	 */
	algorithmTool.calculateDepOrder();

	/*
	 * The following codes are used to:
	 *
	 * With the order among the departments, we 
	 * select the current department and help 
	 * this department to choose students based
	 * on the value(student vs currentDepartment).
	 *
	 * Then we pick out the unlucky students and 
	 * unlucky departments for outputing JSON 
	 * results.
	 * 
	 */

	// the total number of departments is 20
	for (int i = 0; i < 20; i++) {
		// for each of the departments(in turn)

		// the index of current department, based on the calculated order
		int currentDepartment = algorithmTool.order[i];
		// the name of current department
		addmitted_department[currentDepartment].department_number = department[currentDepartment].department_number;
		// initial the total number of addmitted students
		addmitted_department[currentDepartment].number = 0;

		// the limitation of current department
		int limitation = department[currentDepartment].member_limit;

		// sort the students with regard to the values

		// for each of the students
		for (int j = 0; j < 300; j++) {
			// the index of currentStudent
			int currentStudent = j;
			// the value between currentStudent and currentDepartment
			int currentValue = algorithmTool.studentDepValues[currentStudent][currentDepartment];

			// at the first time, mark the isChosenByDepartment as false
			if (i == 0) {
				student[currentStudent].isChosenByDepartment = false;
			}

			student_sorted[j].index = currentStudent;
			student_sorted[j].value = currentValue;
		}

		// sort the students based on the value(students vs currentDepartment)
		sort(student_sorted, student_sorted+310, cmp);

		// the current department chooses "limitation"(eg.10-15) students
		int k = 0, currentStuIdx = 0;
		while (k < limitation) {
			int index = student_sorted[currentStuIdx].index;
			int value = student_sorted[currentStuIdx].value;

			// if the current student is been chosen by another department
			if (student[index].isChosenByDepartment == true) {
				// ignore the current student
				currentStuIdx++;
				continue;
			}
			// if the value of current student == 0, end this process
			if (value == 0) break;

			// passed the abovementioned two examinations, join the student
			// to the current department
			student[index].isChosenByDepartment = true;
			int numberTmp = addmitted_department[currentDepartment].number;
			addmitted_department[currentDepartment].student_number[numberTmp] = student[index].student_number;
			addmitted_department[currentDepartment].number++;

			currentStuIdx++;
			k++;
		}

		// if the department does not receive any students
		if (addmitted_department[currentDepartment].number == 0) {
			// join it to unlucky_department
			unlucky_department[unlucky_department_number++] = department[currentDepartment].department_number;
		} 
		// the total number of unlucky departments
		unlucky_department_number--;
	}

	// search for unlucky students
	for (int i = 0; i < 300; i++) {
		// if the student has not been chosen by any departments
		if (student[i].isChosenByDepartment == false) {
			unlucky_student[unlucky_student_number++] = student[i].student_number;
		}
	}
	// the total number of unlucky students
	unlucky_student_number--;
}
