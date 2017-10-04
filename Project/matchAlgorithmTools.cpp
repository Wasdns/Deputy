#include <stdlib.h>
#include <iostream>
#include "definition.h"
#include "parser.h"
#include "matchAlgorithmTools.h"
using namespace std;

extern students student[310];
extern departments department[25];
extern addmitted addmitted_department[25];

/*
 *  Function Name: deliverStudent
 *  deliver the students to two different classes
 */ 
void matchAlgorithmTools::deliverStudent() {
	// for each of the students
	for (int i = 0; i < 300; i++) {
		// if the student does not choose any departments, 
		// join he/she to the coldStudent
		if (student[i].applications_department_number == 0) {
			coldStudent[coldStudentNumber] = student[i];
			coldStudentNumber++;
			continue;
		} 

		// otherwise, the student has chosen some(>=1) departments,
		// join he/she to the eagerStudent
		eagerStudent[eagerStudentNumber] = student[i];
		eagerStudentNumber++;
	}
}

int matchAlgorithmTools::matchedLevelValue(int k, students student_instance, departments department_instance) {
	parser algorithmParser; 

	return 0;
}

struct department_sorted_t {
	int index;
	int score;
};

department_sorted_t department_sorted[21];

bool cmp(department_sorted_t &department_instance1, department_sorted_t &department_instance2) {
	return department_instance1.score > department_instance2.score;
}

/*
 *  Function Name: calculateDepOrder
 *  calculate the order among departments
 *  based on studentWishes.
 */
void matchAlgorithmTools::calculateDepOrder() {
	// the mechanism of sorting departments
	// studentWishes[department_instance][0] = value => +5*value
	// studentWishes[department_instance][1] = value => +4*value
	// studentWishes[department_instance][2] = value => +3*value
	// studentWishes[department_instance][3] = value => +2*value
	// studentWishes[department_instance][4] = value => +1*value

	// calculate the scores of every departments

	// for each of the departments
	for (int i = 0; i < 20; i++) {
		// initial the department_sorted[i]
		department_sorted[i].index = i;
		department_sorted[i].score = 0;

		int score = 0;
		
		// search studentWishes and calculate score
		for (int j = 0; j < 5; j++) {
			score += studentWishes[i][j]*(5-j);
		}

		// record in department_sorted[i]
		department_sorted[i].score = score;
	}

	// sort the departments based on score
	sort(department_sorted.begin(), department_sorted.end(), cmp);

	// record the order among departments in order[20]
	for (int i = 0; i < 20; i++) {
		order[i] = department_sorted[i].index;
	}
}
