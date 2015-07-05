#include "../../include/myhead.h"

int function()
{
    char cmd[10];

    while(1)
    {
        scanf("%s",cmd);

	if(my_strcmp(cmd,"reg") == 0)
	{
	    return reg;
	    break;
	}

	if(my_strcmp(cmd,"log") == 0)
	{
	    return log;
	    break;
	}

	if(my_strcmp(cmd,"out") == 0)
	{
	    return out;
	    break;
	}
	
	printf("input error!please input again!\n");
    }
}
