#include "head.h"

 lrtime_t * my_GetCurrentTime()
{
	lrtime_t * timet;
	timet = malloc(sizeof(lrtime_t));
	time_t t;
	struct tm * qt;
	 
	time ( &t );
	qt = localtime(&t);

	timet->year = qt->tm_year + 1900;
	timet->month = qt->tm_mon + 1;
	timet->day = qt->tm_mday;
	timet->hour = qt->tm_hour;
	timet->min = qt->tm_min;
	timet->sec = qt->tm_sec;

	return timet;
}