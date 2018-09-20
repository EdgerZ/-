#include "head.h"

//借书功能
int REND(user_t * usert)			//通过索书号来实现借书功能
{
	FILE *user;
	user_t userr;
	FILE *rend;
	book_t s;
	int retpmm = 0, slen = 0, maxnum = 0;

	if ((user = fopen(userfilename, "rb+")) == NULL)
	{
		perror("fopen error");
		return -1;
	}
	switch (usert->force)
	{
	case 2:maxnum = Authoritytwo; break;
	case 3:maxnum = Authoritythree; break;
	case 4:maxnum = Authorityfour; break;
	default:break;
	}
	if (usert->bbn >= maxnum)
	{
		printf("超出可借数量：%d级权限可借书数量为：%d。\n", usert->force, maxnum);
		Press
			getchar();
		fclose(user);
		return -1;
	}

	if ((rend = fopen(filename, "rb+")) == NULL)
	{
		perror("fopen error");
		fclose(rend);
		Press
			getchar();
		return -1;
	}

#if(rmode)
	printf("当前索书号值为：%d\n", BOOKNUM);
#endif
	int stlen = BOOKNUM - Startnum;
	fseek(rend, stlen*(sizeof(book_t)), 0);
	fread(&s, sizeof(book_t), 1, rend);
	s.count--;
	if (s.count < 0)
	{
		printf("此书数量不足！请选择其他书籍！\n");
		fclose(rend);
		fclose(user);
		return -1;
	}
	fseek(rend, -(int)(sizeof(book_t)), 1);
	fwrite(&s, sizeof(book_t), 1, rend);
	//	DATACHANGE(schnum);
#if(rmode)
	fseek(rend, -(int)(sizeof(book_t)), 1);
	fread(&s, sizeof(book_t), 1, rend);
#endif
	if (retpmm = PersonalMessageManagement(usert, 'L', s.num))
	{
		printf("借书失败！\n");
		fclose(user);
		fclose(rend);
		return -1;
	}
	else
	{
		printf("成功!\n");
		printf("书籍信息：NO.%d 书名 : %s 馆藏总量 : %d 可借数量 : %d\n", s.num, s.name, s.tcount, s.count);

		rewind(user);																								//对用户的bnn值进行重写;
		fseek(user, sizeof(user_t)*(usert->num - Startusernum), 0);
		fread(&userr, sizeof(user_t), 1, user);
		userr.bbn++;
		fseek(user, sizeof(user_t)*(usert->num - Startusernum), 0);
		fwrite(&userr, sizeof(user_t), 1, user);
		fclose(user);
		fclose(rend);
		return 0;
	}
}
