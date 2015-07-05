#ifndef _MYHEAD_H_
#define _MYHEAD_H_

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <netdb.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <pthread.h>
#include <time.h>

#define portnumber 3333

struct message
{
    int action;
    int action1;
    long int ID;

    char name[20];
    char toname[20];
    char msg[100];
    char passwd[20];

    int sec;              //时间变量
    int min;
    int hor;
    int day;
    int mon;
    int year;

    struct message *next;
};

struct message msg;

enum           //枚举 宏
{
    reg,
    log,
    out,
    log_ok,
    admin_log_ok,
    log_error,
    have_log,
    reg_ok,
    passwd_error,
    ID_error,
    change_ok,
    change_error,
    say,
    say_all,
    show,
    send_face,
    change,
    see_record,
    quit,
    quit_ok,
    ban,
    ban_tell_all,
    solve_ban,
    solve_error,
    kick,
    kick_ok,
    unonline_msg
};

int sockfd;      //客户端，服务器发送接受消息的标志
int fd;
int flag;

char my_expression[20];    //定义表情
char seder_name[20];       //登录执行命令的人

extern void read_message(void *arg); //外部声明

#endif
