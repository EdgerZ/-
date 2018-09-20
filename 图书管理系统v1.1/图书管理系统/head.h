#define _CRT_SECURE_NO_WARNINGS
#define filename "library.lib"
#define datafilename "message.lib"
#define userfilename "user.lib"
#define Deletefilename "DeleteMessage.lib"
#define Startnum 10000
#define Startusernum 10000
#define Press	printf("————回车继续————");
#define Borrowtime 7
#define rmode 1
#define Authoritytwo 1
#define Authoritythree 2
#define Authorityfour 3
#define rootpswd "root"
#define Sleeptime 500
#define Round 1


#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include <conio.h>

#ifndef __HEAD_H__
#define __HEAD_H__

typedef struct Book
{
	int num;
	char name[50];
	int tcount;
	int count;
}book_t;

typedef struct UserName
{
	int num;
	char name[50];
	int loginauthorize;									//用户是否有权登陆；
	int bbn;
	char pswd[50];
	int force;
}user_t;

typedef struct L_Rtime
{
	int year;
	int month;
	int day;
	int hour;
	int min;
	int sec;
}lrtime_t;

typedef struct L_R										//用来存放用户借存信息；
{
	int bnum;
	char lr;
	lrtime_t  lrt;
	int useful;													//用来判断是否为有用信息（需要打印）；
}lr_t;

typedef struct DeleteBookMessage			    //用来存放删除信息;
{
	book_t bookmessage;
	lrtime_t time;
	int useful;
}dbm_t;

#endif`
 extern int BOOKNUM;								//定义BOOKNUM用来存放借出的书籍；

extern int MaxBookNum;

int  USERREG(void);									//声明用户注册函数；

int SearchNum(void);									//声明按书号搜索

int SearchName(void);									//声明按书名搜索

void Loadin(void);										//声明信息录入函数,遍历书籍信息时若发现书号为0的空位则先检测是否有重复，没有则优先填补空位；

int  REND(user_t *);										//声明借书函数

void PrintUserInfo(void);								//打印用户信息

int PersonalMessageManagement(user_t * , char,int);							//个人租借信息

int CheckMessage(user_t*);							//检查即将到期的书籍；

void PrintBorrowedBook(user_t * usert);		//打印用户已借信息;

int ReturnBook(user_t *, int );						//还书；将书籍信息补回（count+1)；

int DeleteMessage(int);									//	删除书籍信息，即将需要删除的信息所有内容赋值0，且在1 1 1 1时跳过所有编号为0的信息，管理员目录中出现删除指令和打印所有删除过的信息指令，若原位置依然为空则直接补回原位，若原位已经有值则在文件末尾顺位补充信息；

lrtime_t * my_GetCurrentTime(void);			//获取当前时间;

void PrintDeleteMessage();							//打印所有删除记录;

void Face();													//登陆界面;

