#include <stdlib.h>
#include <iostream>
#include <algorithm>
#include <cstring>
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

/*
 *  Function Name: matchedLevelValue
 *  TODO
 */ 
int matchAlgorithmTools::matchedLevelValue(int k, students student_instance, departments department_instance) {
	parser parse;
	
	int dep_weekdays_begin[200]; 
	int dep_weekdays_end[200]; 
	int stu_weekdays_begin[200]; 
	int stu_weekdays_end[200]; 

	memset(dep_weekdays_begin, 0, sizeof(dep_weekdays_begin));
	memset(dep_weekdays_end, 0, sizeof(dep_weekdays_end));
	memset(stu_weekdays_begin, 0, sizeof(stu_weekdays_begin));
	memset(stu_weekdays_end, 0, sizeof(stu_weekdays_end));

	int dep_weekday_num = 0; 
	int stu_weekday_num = 0; 

	int wish_num = 0; 
	
	dep_weekday_num = department_instance.event_schedules_number;
	stu_weekday_num = student_instance.free_time_number;
	
	wish_num = student_instance.applications_department_number;
	
	for (int i = 0; i < dep_weekday_num; i++) {
		int Weekday = 0, StartTime = 0, EndTime = 0;

		Weekday = parse.parseWeekday(department_instance.event_schedules[i]);
		StartTime = parse.parseStartTime(department_instance.event_schedules[i]);
		EndTime = parse.parseEndTime(department_instance.event_schedules[i]);

		dep_weekdays_begin[i] = Weekday*24*60+StartTime;
		dep_weekdays_end[i] = Weekday*24*60+EndTime;
	}
	
	for (int i = 0; i < stu_weekday_num; i++) {
		int Weekday = 0, StartTime = 0, EndTime = 0;

		Weekday = parse.parseWeekday(student_instance.free_time[i]);
		StartTime = parse.parseStartTime(student_instance.free_time[i]);
		EndTime = parse.parseEndTime(student_instance.free_time[i]);

		stu_weekdays_begin[i] = Weekday*24*60+StartTime;
		stu_weekdays_end[i] = Weekday*24*60+EndTime;
	}
	
	double values = -1, match_tags = 0;
	int times = 0; 
	
	for (int i = 0; i < dep_weekday_num; i++) {
		int mark = 0; 
		int match_times = 0;
		int total_times = dep_weekdays_end[i]-dep_weekdays_begin[i];
		
		for (int j = 0; j < stu_weekday_num; j++) {	 
			if (dep_weekdays_begin[i] >= stu_weekdays_begin[j] && dep_weekdays_end[i] <= stu_weekdays_end[j] || match_times >= total_times) {
				mark = 1; 
				break;
			} else if (dep_weekdays_begin[i] <= stu_weekdays_begin[j] && stu_weekdays_begin[j] <= dep_weekdays_end[i]) {
				if (stu_weekdays_end[j] >= dep_weekdays_end[i]) {
					match_times += (dep_weekdays_end[i]-stu_weekdays_begin[j]);
				} else {
					match_times += (stu_weekdays_end[j]-stu_weekdays_begin[j]);
				}
			} else if(stu_weekdays_begin[j] <= dep_weekdays_begin[i] && dep_weekdays_begin[i] <= stu_weekdays_end[j]) {
				match_times += (stu_weekdays_end[j]-dep_weekdays_begin[i]);
			} else {
				continue;
			}
		}
		
		// percent1: for each event, if the stu_match_time/event_total_time >= 60%,
		// add 1 to match times
		double percent1 = 0;
		percent1 = (double)(match_times*100/total_times);
		
		if (mark == 1) {
			times++;
		} else if (percent1 >= 60) {
			times++;
		}
	}
	
	double percent2 = (double)(times*100/dep_weekday_num);
	
	double matchValue = 0;

	// percent2: stu_match_times/dep_total_times
	if (percent2 <= 70){
		matchValue = 4;
	} else {
		for (int i = 0; i < department_instance.tag_number; i++) {
			for (int j = 0; j < student_instance.tag_number; j++) {
				if (department_instance.tags[i] == student_instance.tags[j]) {
					match_tags++;
				}
			} 
		}
	}

	if (matchValue == 0) {
		matchValue = (percent2*stu_weekday_num)/100;
	}

	if (student_instance.applications_department_number != 0) {
		values = (2/student_instance.applications_department_number)*(5-k)*(5-k)+matchValue;
		if (department_instance.tag_number != 0) {
			values += (match_tags/department_instance.tag_number)*50;
		}
	}
	
	return values; 
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
	sort(department_sorted, department_sorted+20, cmp);

	// record the order among departments in order[20]
	for (int i = 0; i < 20; i++) {
		order[i] = department_sorted[i].index;
	}
}
