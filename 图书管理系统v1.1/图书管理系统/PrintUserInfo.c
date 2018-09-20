#include "head.h"

void PrintAllLR(int num)
{
	FILE * palr;
	FILE *user;
	user_t usert;
	lr_t lr;
	int i = 0;

	if ((user= fopen(userfilename, "rb")) == NULL)
	{
		perror("fopen error");
		Press
			getchar();
		return;																		
	}
	fseek(user, sizeof(user_t)*(num - Startusernum), 0);
	fread(&usert, sizeof(user_t), 1, user);
	fclose(user);

	if ((palr = fopen(usert.name, "rb")) == NULL)
	{
		perror("fopen error");
		Press
			getchar();
		return ;																		
	}
	rewind(palr);
	while (1)																						//打印用户的所有借还书记录;
	{
		i++;
		memset(&lr, 0, sizeof(lr_t));
		fread(&lr, sizeof(lr_t), 1, palr);
		if (feof(palr))break;
		printf("记录%d：书号NO.%d\t%c\t%d/%d/%d\t记录有效性：%d\n", i, lr.bnum, lr.lr, lr.lrt.year, lr.lrt.month + 1, lr.lrt.day, lr.useful);
	}
	Press
		getchar();
	fclose(palr);
	return;
}


int ChangeExecutiveAuthority(int num)
{
	FILE *cea;
	user_t usert;
	int level=0;

	if ((cea = fopen(userfilename, "rb+")) == NULL)
	{
		perror("fopen error");
		Press
			getchar();
		return -1;																		//返回-1权限更改失败:
	}
	fseek(cea, (num - Startusernum)*sizeof(user_t), 0);
	fread(&usert, sizeof(user_t), 1, cea);
#if(rmode)
	printf("用户信息为：NO.%d\t用户名：%s\t登录权限：%d\t用户权限：%d\n", usert.num, usert.name, usert.loginauthorize, usert.force);
#endif
	printf("需要将用户NO.%d权限更改为：(当前用户操作权限为%d)(输入小于5的正整数）\n",num,usert.force);
	scanf("%d", &level);
	getchar();
	if (level>=0 && level <5)
	{
		usert.force = level;
		fseek(cea, (num - Startusernum)*sizeof(user_t), 0);
		fwrite(&usert, sizeof(user_t), 1, cea);
		printf("当前操作权限为：%d\n", usert.force);
		Press
			getchar();
		fclose(cea);
		return 0;																		//返回0权限更改成功；
	}
	else
	{
		printf("输入的权限有误\n");
		fclose(cea);
		Press
			getchar();
		return -1;
	}
}

int ChangeLoginAuthority(int num)
{
	FILE *cla;
	user_t usert;
	int level = 0;

	if ((cla = fopen(userfilename, "rb+")) == NULL)
	{
		perror("fopen error");
		Press
			getchar();
		return -1;																		//返回-1权限更改失败:
	}
	fseek(cla, (num - Startusernum)*sizeof(user_t), 0);
	fread(&usert, sizeof(user_t), 1, cla);
#if(rmode)
	printf("用户信息为：NO.%d\t用户名：%s\t登录权限：%d\t用户权限：%d\n", usert.num, usert.name, usert.loginauthorize, usert.force);
#endif
	printf("需要将用户NO.%d权限更改为：(当前用户登录权限为%d)(输入0或1）\n", num, usert.loginauthorize);
	scanf("%d", &level);
	getchar();
	if (level == 0 || level ==1)
	{
		usert.loginauthorize = level;
		fseek(cla, (num - Startusernum)*sizeof(user_t), 0);
		fwrite(&usert, sizeof(user_t), 1, cla);
		printf("当前登录权限为：%d\n", usert.loginauthorize);
		Press
			getchar();
		fclose(cla);
		return 0;																		//返回0权限更改成功；
	}
	else
	{
		printf("输入的权限有误\n");
		fclose(cla);
		Press
			getchar();
		return -1;
	}

}


int  User_NumSearch()
{
	FILE *pui;
	user_t usert;
	int Num;

	if ((pui = fopen(userfilename, "rb")) == NULL)
	{
		perror("fopen error");
		Press
			getchar();
			return -1;																		//返回-1搜索失败；
	}

	fseek(pui, -(int)sizeof(user_t), 2);
	fread(&usert, sizeof(user_t), 1, pui);

	printf("输入用户编号：(当前用户最高编号为：%d)\n",usert.num);
	scanf("%d", &Num);
	getchar();

	if (Num > usert.num || Num<Startusernum)
	{
		printf("没有这个用户，当前用户最高编号为：%d,最低为：%d\n", usert.num,Startusernum);
		fclose(pui);
		Press
			getchar();
		printf("是否重新搜索？（y/n)");
		char ch = getchar();
		switch (ch)
		{
		case 'y':fclose(pui); return User_NumSearch();
		case 'n':fclose(pui); return -1;													//返回-1搜索失败；
		default:printf("没有这个命令；");
			Press
			fclose(pui);
			break;
		}
	}
//	fseek(pui, 0, 0);														//文件位置标记回零；
	fseek(pui, (Num - Startusernum)*sizeof(user_t), 0);
	fread(&usert, sizeof(user_t), 1, pui);
	printf("用户信息为：NO.%d\t用户名：%s\t登录权限：%d\t用户权限：%d\n", usert.num, usert.name, usert.loginauthorize, usert.force);
	fclose(pui);
	return usert.num;
}

int User_NameSearch()
{
	FILE *pui;
	user_t usert;
	char s[50];

	if ((pui = fopen(userfilename, "rb")) == NULL)
	{
		perror("fopen error");
		Press
			getchar();
		return -1;
	}

	printf("输入需要搜索的用户名：\n");
	scanf("%s", s);
	getchar();
	fseek(pui, 0, 0);
	while (!feof(pui))
	{
		fread(&usert, sizeof(user_t), 1, pui);
		if (!strcmp(usert.name, s))
		{
			printf("用户信息为：NO.%d\t用户名：%s\t登录权限：%d\t用户权限：%d\n", usert.num, usert.name, usert.loginauthorize, usert.force);
			fclose(pui);
			return usert.num;
		}
	}
	printf("没有这个用户；是否继续搜索？（y/n）");
	char ch = getchar();
	switch (ch)
	{
	case 'y':fclose(pui); return User_NameSearch();
	case 'n':fclose(pui); return -1;													//返回-1搜索失败；
	default:printf("没有这个命令；");
		Press
		fclose(pui);
		break;
	}
}

int User_PrintAll()
{
	FILE *pui;
	user_t usert;

	if ((pui = fopen(userfilename, "rb")) == NULL)
	{
		perror("fopen error");
		Press
			getchar();
			return -1;
	}
	rewind(pui);
	while (1)
	{
		memset(&usert, 0,sizeof(usert));
		fread(&usert, sizeof(user_t), 1, pui);
		if (feof(pui))break;
		printf("用户信息为：NO.%d\t用户名：%s\t登录权限：%d\t用户权限：%d\n", usert.num, usert.name, usert.loginauthorize, usert.force);
	}
	fclose(pui);
	return 0;
}

void PrintUserInfo()
{
	FILE *pui;
	int renum = 0;
	int rechg = 0;

	if ((pui = fopen(userfilename, "rb")) == NULL)
	{
		perror("fopen error");
		printf("用户信息打印失败。\n");
		system("pause");
		return;
	}

	fseek(pui, 0, 2);
	int tlen = ftell(pui);
	if (tlen == 0)																			//	数据库为空时
	{
		printf("暂无用户信息。\n");
		Press
		getchar();
		return;
	}
	fclose(pui);																				//确定文件不为空后关闭文件；

	printf("编号搜索/用户名搜索/全部打印（n/s/a）：\n");
	char ch = getchar();
	switch (ch)
	{
	case 'n':renum=User_NumSearch(); fclose(pui); break;
	case 's':renum=User_NameSearch(); fclose(pui); break;
	case 'a':getchar(); renum = User_PrintAll(); fclose(pui); break;			//此函数没有输入函数所以需要使用getchar接受一个回车；
	default:
		printf("没有这条命令。\n");
		Press
		getchar();
		PrintUserInfo();
	}
	if (renum == -1)return;
	Press																						//搜索结束后的停顿;
		getchar();

CHANGEAUTHORITY:
	if (ch == 'a')system("cls");
	else
	{
		printf("选择需要进行的操作：\n");
		printf("改变用户操作权限：c\n");
		printf("改变用户登录权限：l\n");
		printf("重新选择搜索功能：r\n");
		printf("打印该用户所有借书信息：q\n");
		printf("不进行操作：e\n");
		ch = getchar();
		switch (ch)
		{
		case 'c':rechg = ChangeExecutiveAuthority(renum); break;
		case 'l':rechg = ChangeLoginAuthority(renum); break;
		case 'r':getchar(); system("cls"); PrintUserInfo();
		case 'e':getchar(); return;
		case 'q':getchar(); PrintAllLR(renum); break;
		default:
			printf("暂无该操作；\n");
			goto CHANGEAUTHORITY;
			break;
		}
		if (!rechg)printf("更改成功！\n");
		else printf("更改失败！\n");
	}
	return;
}

