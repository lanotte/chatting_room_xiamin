#include "../../include/myhead.h"

void my_time(struct message *temp)
{
    time_t timep;
    struct tm *p;
    time(&timep);
    p = localtime(&timep);

    temp->year = 1900 + p->tm_year;
    temp->mon = 1 + p->tm_mon;
    temp->day = p->tm_mday;
    
    temp->hor = p->tm_hour;
    temp->min = p->tm_min;
    temp->sec = p->tm_sec;
}
