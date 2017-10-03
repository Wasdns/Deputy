#ifndef PARSERAW_H
#define PARSERAW_H

extern students student[310];
extern departments department[25];
extern addmitted addmitted_department[25];

class parser {
public:
	parser() { };
	// parse student weekday, 0: Sunday, 1: Monday ... 7: Saturday
	int parseWeekday(string free_time);
	// parse start time, eg. 14:35 => 14*60+35 = 875
	int parseStartTime(string free_time);
	// parse end time, eg. 14:35 => 14*60+35 = 875
	int parseEndTime(string free_time);
};

#endif