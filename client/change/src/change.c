#include "../../include/myhead.h"

/*修改客户自己的信息：昵称和密码*/
void my_change()
{
    int sign1 = 1;               //循环标志位
    int sign2 = 1;
    
    char input_change[100];      //输入信息
    char change_name[100];       //修改的名字
    char change_passwd[100];     //修改的密码
    char comf_passwd[100];       //确认密码

    while(sign1 == 1)
    {
        printf("which message do you want to change(name/passwd):");
        scanf("%s",input_change);

        if(my_strcmp(input_change,"name") == 0)
        {
            printf("please input your new name:");
	    scanf("%s",change_name);
	    
	    my_strcpy(msg.name,change_name);
	    
	    break;
        }
    
        if(my_strcmp(input_change,"passwd") == 0)
        {
            while(sign2 == 1)
	    {
	        printf("please input your new passwd:");
	        scanf("%s",change_passwd);
	        printf("please comfirm your new passwd:");
	        scanf("%s",comf_passwd);

	        if(strcmp(change_passwd,comf_passwd) == 0)
	        {
	             my_strcpy(msg.passwd,change_passwd);
	             
		     sign1 = 0;
		     sign2 = 0;

	        }
	        
		else
	        {
	             printf("the first is not equal to the second,please input again!\n");
	        }
	    }
        }

	else
	{
	    printf("sorry,input error!please input again!\n");
	}
    }
}
