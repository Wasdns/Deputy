#ifndef MATCHALGO_H
#define MATCHALGO_H

extern students student[310];
extern departments department[25];
extern addmitted addmitted_department[25];

class matchAlgorithm {
public:
	matchAlgorithm() { 
		unlucky_student_number = 0;
		unlucky_department_number = 0;
	};

	// the key algorithm
	void algorithm();
	
	// the results:
	// (1)unlucky students;
	// (2)unlucky departments.
	int unlucky_student_number;
	int unlucky_department_number;
	string unlucky_student[310];
	string unlucky_department[25];
};

#endif
