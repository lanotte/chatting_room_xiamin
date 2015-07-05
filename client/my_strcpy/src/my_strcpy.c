#include "../../include/myhead.h"

void my_strcpy(char *src,char *dest)
{
    while(*dest != '\0')
    {
        *src = *dest;
	src++;
	dest++;
    }
    *src = '\0';
}
