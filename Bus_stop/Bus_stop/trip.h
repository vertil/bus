#pragma once
//#include <time.h>

class trip
{
public:
	
	int startHour;
	int startMin;
	int endHour;
	int endMin;
	int totalTime;
	int totalStart;
	int totalEnd;
	void calTotalTime();
	friend bool operator==(const trip &a, const trip &b);

};

