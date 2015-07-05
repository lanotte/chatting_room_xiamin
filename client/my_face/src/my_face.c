#include "../../include/myhead.h"

int my_face()
{
    char input_face[10];
    char temp[10];

    while(1)
    {
        system("reset");

	printf("              &&&&&~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~&&&&&\n");
        printf("              &     please choose your favorite look        &\n");
        printf("              &^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^&\n");
        printf("              &           1.^_^     2.^V^    3.*_*          &\n");
        printf("              &                                             &\n");
        printf("              &           4.(^~^)   5.~_~    6.^0^          &\n");
        printf("              &                                             &\n");
        printf("              &           7.~_~|||  8.(^U^)  9.>_<          &\n");
        printf("              &                                             &\n");
        printf("              &__________~~~~~~~~~~~~~~~~~~~~~~~~~__________&\n");
        printf("\n");
        printf("              which expression do you want to send:");
        scanf("%s",input_face);

        if(my_strcmp(input_face,"1") == 0)        //错误：如果是整型，改成if(input_face == 1)
        {
            my_strcpy(my_expression,"^_^");
	    break;
        }

        if(my_strcmp(input_face,"2") == 0)
        {
            my_strcpy(my_expression,"^v^");
	    break;
        }

        if(my_strcmp(input_face,"3") == 0)
        {
            my_strcpy(my_expression,"*_*");
	    break;
        }
    
        if(my_strcmp(input_face,"4") == 0)
        {
            my_strcpy(my_expression,"(^~^)");
	    break;
        }
    
        if(my_strcmp(input_face,"5") == 0)
        {
            my_strcpy(my_expression,"~_~");
	    break;
        }
    
        if(my_strcmp(input_face,"6") == 0)
        {
            my_strcpy(my_expression,"^0^");
	    break;
        }
        
	if(my_strcmp(input_face,"7") == 0)
        {
            my_strcpy(my_expression,"~_~|||");
	    break;
        }
    
        if(my_strcmp(input_face,"8") == 0)
        {
            my_strcpy(my_expression,"(^U^)");
	    break;
        }
    
        if(my_strcmp(input_face,"9") == 0)
        {
            my_strcpy(my_expression,">_<");
	    break;
        }

	else
	{
	    printf("there is not this expression!please input again!\n");
	    printf("do you want to continue to send face?");
	    scanf("%s",temp);

	    if(strcmp(temp,"y") == 0 || strcmp(temp,"Y") == 0)
	    {
	        ;
	    }

	    if(strcmp(temp,"n") == 0 || strcmp(temp,"N") == 0)
	    {
	        return -1;
	    }
	}
    }
}
