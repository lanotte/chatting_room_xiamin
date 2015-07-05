#include "../../include/myhead.h"

int my_strcmp(char *src,char *dest)
{
    while(*src == *dest && *src != '\0' && *dest != '\0')
    {
        src++;
	dest++;
    }
    return *src - *dest;
}
