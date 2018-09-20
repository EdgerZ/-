#define _CRT_SECURE_NO_WARNINGS
#define filename "library.lib"
#define datafilename "message.lib"
#define userfilename "user.lib"
#define Deletefilename "DeleteMessage.lib"
#define Startnum 10000
#define Startusernum 10000
#define Press	printf("���������س�������������");
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
	int loginauthorize;									//�û��Ƿ���Ȩ��½��
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

typedef struct L_R										//��������û������Ϣ��
{
	int bnum;
	char lr;
	lrtime_t  lrt;
	int useful;													//�����ж��Ƿ�Ϊ������Ϣ����Ҫ��ӡ����
}lr_t;

typedef struct DeleteBookMessage			    //�������ɾ����Ϣ;
{
	book_t bookmessage;
	lrtime_t time;
	int useful;
}dbm_t;

#endif`
 extern int BOOKNUM;								//����BOOKNUM������Ž�����鼮��

extern int MaxBookNum;

int  USERREG(void);									//�����û�ע�ắ����

int SearchNum(void);									//�������������

int SearchName(void);									//��������������

void Loadin(void);										//������Ϣ¼�뺯��,�����鼮��Ϣʱ���������Ϊ0�Ŀ�λ���ȼ���Ƿ����ظ���û�����������λ��

int  REND(user_t *);										//�������麯��

void PrintUserInfo(void);								//��ӡ�û���Ϣ

int PersonalMessageManagement(user_t * , char,int);							//���������Ϣ

int CheckMessage(user_t*);							//��鼴�����ڵ��鼮��

void PrintBorrowedBook(user_t * usert);		//��ӡ�û��ѽ���Ϣ;

int ReturnBook(user_t *, int );						//���飻���鼮��Ϣ���أ�count+1)��

int DeleteMessage(int);									//	ɾ���鼮��Ϣ��������Ҫɾ������Ϣ�������ݸ�ֵ0������1 1 1 1ʱ�������б��Ϊ0����Ϣ������ԱĿ¼�г���ɾ��ָ��ʹ�ӡ����ɾ��������Ϣָ���ԭλ����ȻΪ����ֱ�Ӳ���ԭλ����ԭλ�Ѿ���ֵ�����ļ�ĩβ˳λ������Ϣ��

lrtime_t * my_GetCurrentTime(void);			//��ȡ��ǰʱ��;

void PrintDeleteMessage();							//��ӡ����ɾ����¼;

void Face();													//��½����;

