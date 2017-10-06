#ifndef MATCHALGOTOOLS_H
#define MATCHALGOTOOLS_H
#include <cstring>

extern students student[310];
extern departments department[25];
extern addmitted addmitted_department[25];

class matchAlgorithmTools {
public:
	matchAlgorithmTools() { 
		lowBound = 25;
		coldStudentNumber = 0;
		eagerStudentNumber = 0; 
		memset(studentDepValues, 0, sizeof(studentDepValues));
		memset(studentWishes, 0, sizeof(studentWishes));
		memset(order, 0, sizeof(order));
	};

	// deliver the students to eagerStudent class or coldStudent class
	void deliverStudent();

	// calculate a value between a student and a department
	// k means the number of student wish
	int matchedLevelValue(int k, students student_instance, departments department_instance);

	// calculate department order, stored in order[20].
	void calculateDepOrder();

	// the students who want department and the students who do not want department
	int eagerStudentNumber, coldStudentNumber;
	students eagerStudent[310], coldStudent[310];

	// studentDepValues[student_instance_idx][department_instance_idx] = 
	//     matchedLevelValue(student_instance, department_instance)
	int studentDepValues[310][25];

	// studentWishes[department_number][the_number_of_first/second/.../fifth_student_wishes]
	// in order to calculate the order among departments
	int studentWishes[25][10];

	// the order among departments, 0/first: department D009, 1/second: department D005...
	int order[20]; 

	// the lowbound
	int lowBound;
};

#endif
