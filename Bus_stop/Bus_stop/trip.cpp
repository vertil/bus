#include "trip.h"

void trip::calTotalTime()
{
	
	this->totalStart = this->startHour * 60 + this->startMin;
	this->totalEnd = this->endHour * 60 + this->endMin;
	this->totalTime = (this->endHour * 60 + this->endMin) - (this->startHour * 60 + this->startMin);
}

bool operator==(const trip &a, const trip &b)
{
	return (a.endHour == b.endHour && a.endMin == b.endMin && a.startHour == b.startHour && a.startMin == b.startMin);
}


