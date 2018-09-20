#include "head.h"

//功能：用户登录 注册 、查询(号码、书名)、修改、删除、追加；

extern  BOOKNUM=0;								//定义BOOKNUM用来存放借出的书籍；

//用户权限：	1：查阅书籍信息；
//						2：借书还书；
//						3：


int main()
{	
	Face();
	char Client_name[10] = { 0 };
	char Client_password[50] = { 0 };
	user_t* Client_message = malloc(sizeof(user_t));
	COORD coord;
	char s = 0, chnys = 0, chsys = 0,psch=0;
	int retn = 0, rets = 0, root = 0, temp = 0, login = 0, i = 0, retcheck = 1, rerend = 0, rereturn = 0, bnm = 0, j = 0, dnum = 0, retdelete = 0;


CLIENTLOG:
	i = 0;
	system("cls");
	root = 0;																//root回0；
	printf("Client name:");
	scanf("%s", &Client_name);
	getchar();
	if (!strcmp(Client_name, "root"))
	{
		printf("password:\n");
		i = 0;
		while (1)
		{
			if (_kbhit())
			{
				if (i <= 0)
				{
					i = 0;
					coord.Y = 2;
					coord.X = i;
				}
				Client_password[i] = _getch(); 
				if (Client_password[i] == '\0')
				{
					continue;
				}
				if (i>0)
				{
					coord.Y = 2;
					coord.X = i-1;
				}
				if (Client_password[i] == 8)
				{
					SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
					printf(" ");
					SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
					i-=2;
				}
				else putchar('*');
				i++;
			}
			if (Client_password[i-1] == '\r')
			{
				Client_password[i-1] = '\0';
				break;
			}
		}
		//scanf("%s", &Client_password);
		//getchar();
		if (!strcmp(Client_password, rootpswd))
		{
			system("cls"); root = 1; login = 1;
		}
		else
		{
			putchar(10);
			printf("密码错误。\n");
			Press
			getchar();
			goto CLIENTLOG;
		} 
	}
	else
	{
		FILE * rec;
		user_t usert;
		rec = fopen(userfilename, "rb");
		fseek(rec, 0, 2);
		int tlen = ftell(rec);
		if (tlen == 0)									//第一个用户的注册;
		{
			temp = USERREG(&Client_name);					//用户名注册；
			if (!temp)
			{
				fclose(rec);
				Press
				getchar();
				goto CLIENTLOG;
			}
			fseek(rec, -(int)sizeof(user_t), 2);
			fread(Client_message, sizeof(user_t), 1, rec);
			login = 1;
		}
		else
		{
			rewind(rec);
			printf("输入密码：\n");
			i = 0;
			while (1)
			{
				if (_kbhit())
				{
					if (i <= 0)
					{
						i = 0;
						coord.Y = 2;
						coord.X = i;
					}
					Client_password[i] = _getch();

					if (Client_password[i] == '\0')
					{
						continue;
					}
					if (i>0)
					{
						coord.Y = 2;
						coord.X = i - 1;
					}
					if (Client_password[i] == 8)
					{
						SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
						printf(" ");
						SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
						i -= 2;
					}
					else putchar('*');
					i++;
				}
				if (Client_password[i - 1] == '\r')
				{
					Client_password[i - 1] = '\0';
					break;
				}
			}
//			scanf("%s", Client_password);
//			getchar();
			while (!feof(rec))
			{
				fread(&usert, sizeof(user_t), 1, rec);
				if (!strcmp(Client_name, usert.name))
				{
					if (!strcmp(Client_password, usert.pswd))
					{
						fclose(rec);
						if (!usert.loginauthorize)
						{
							printf("\n输入的账号密码正确,但管理员限制您的访问！\n");
							Press
							getchar();
							goto CLIENTLOG;
						}
						login = 1;
						*Client_message = usert;
						goto START;
					}
					else
					{
						putchar(10);
						printf("密码错误\n");
						Press
						getchar();						//按任意键继续；
						goto CLIENTLOG;
					}
				}
			}
			temp=USERREG(&Client_name);				//数据库中没有该用户信息，开始用户注册；
			if (!temp)
			{
				fclose(rec);
				goto CLIENTLOG;
			}
			login = 1;
			rewind(rec);
			fseek(rec, -(int)sizeof(user_t), 2);
			fread(Client_message, sizeof(user_t), 1, rec);
		}
		fclose(rec);
	}							


START:
	system("cls");
	if (login)
	{
		if (root)printf("管理员账号：root 权限等级为5\n");
		else
		{
			printf("用户信息：NO.%d %s 权限等级为：%d 已借书数量为：%d\n", Client_message->num, Client_message->name, Client_message->force,Client_message->bbn);
			putchar(10);
			retcheck=CheckMessage(Client_message);
			putchar(10);
		}
	}
	printf("按编号索引：n\n");
	printf("按书名索引：s\n");
	if (login && Client_message->bbn &&!root )printf("还书：r\n");
	if (root)printf("录入信息：l\n");
	if (root)printf("删除书籍信息：d\n");
	if (root)printf("显示所有已删除书籍信息：m\n"); 
	if (root)printf("显示用户信息：p\n");
	if (login)printf("退出登录：e\n");
	printf("退出：t\n");

	scanf("%c", &s);
	getchar();
	switch (s)
	{
	case 'n':goto SEARCHNUM; 
	case 's':goto SEARCHNAME;
	case 'r':goto RETURNBOOK;
	case 'l':
	{
				if (root)goto LOADIN;
				else
				{
					printf("您没有操作权限;\n");
					Press
					getchar();
					goto START;
				}
	}
	case 'd':
	{
				if (root)
				{
					printf("所有书籍信息如下：\n");
					FILE *li;
					if ((li = fopen(filename, "rb+")) == NULL)
					{
						perror("open file error");
						exit(0);
					}

					int  len = sizeof(book_t);
					book_t *scmp = malloc(sizeof(book_t));
					rewind(li);
					while (1)
					{
						memset(scmp, 0, len);
						fread(scmp, len, 1, li);
						if (feof(li))break;
						if (scmp->num)
						{
							if (scmp->tcount)printf("书籍信息 :NO.%d \t书名 : %s \t馆藏总量 : %d \t可借数量 : %d\n", scmp->num, scmp->name, scmp->tcount, scmp->count);
							else printf("（已删除）书籍信息 :NO.%d \t书名 : %s \t馆藏总量 : %d \t可借数量 : %d\n", scmp->num, scmp->name, scmp->tcount, scmp->count);
						}
					}
					fclose(li);
					printf("请输入需要删除的书号：");
					dnum = 0;
					scanf("%d", &dnum);
					if (dnum < 10000 || dnum > MaxBookNum)
					{
						printf("无此书号！\n");
						getchar();
						goto START;
					}
					getchar();
					retdelete=DeleteMessage(dnum);
					if (!retdelete)printf("删除成功！\n");
					else printf("删除失败！\n");
					Press
						getchar();
					goto START;
				}
				else
				{
					printf("您没有操作权限;\n");
					Press
						getchar();
					goto START;
				}
	}

	case 'm':
	{
				if (root)
				{
					PrintDeleteMessage();
					Press
						getchar();
					goto START;
				}
				else
				{
					printf("您没有操作权限;\n");
					Press
						getchar();
				}
				goto START;
	}

	case 'p':
	{
				if (root)PrintUserInfo();
				else
				{
					printf("您没有操作权限;\n");
					Press
						getchar();
				}
				goto START;
	}
	case 'e':
	{
				if (login)
				{
					login = 0;
					goto CLIENTLOG;
				}
				else
				{
					printf("未登录；\n");
					Press
					getchar();
					goto START;
				}
	}
	case 't':exit(0);
	default:
				printf("无该功能！\n");
				Press
				getchar();
				goto START;
		break;
	}

LOADIN:
	if (root)
	{
		Loadin();
		Press
		getchar();
	}
	goto CLIENTLOG;

SEARCHNAME:
	chsys = 0;
	rets = SearchName();
	//	if(rets==0)																//有问题
	//{
	//	printf("这本书管内暂无可借。是否打印借阅信息：y/n\n");
	//	scanf("%c", &chsys);
	//	if (chsys == 'y')
	//		PTDATA();
	//	BOOKNUM=0;
	//	printf("返回 主目录:\n");
	//}
	if (rets == 1&& Client_message->force >1 &&!root)
	{
		printf("是否要借出该书？y/n\n");
		scanf("%c", &chsys);
		getchar();
		if (chsys == 'y')
		{
			rerend=REND(&Client_message);
			if (!rerend)Client_message->bbn++;
			BOOKNUM = 0;
		}
	}
	Press
	getchar();
	goto START;

SEARCHNUM:
	chnys = 0;
	retn = SearchNum();
	//	if(retn==0)
	//{
	//	printf("这本书管内暂无可借。是否打印借阅信息：y/n\n");
	//	scanf("%c", &chnys);
	//	if (chnys == 'y')
	//		PTDATA();
	//	BOOKNUM=0;
	//	printf("返回 主目录:\n");
	//}
	if (retn == 1 && Client_message->force >1 &&!root)
	{
		printf("是否要借出该书？y/n\n");
		scanf("%c", &chnys);
		getchar();
		if (chnys == 'y')
		{
			rerend=REND(Client_message);
			if (!rerend)Client_message->bbn++;
			BOOKNUM = 0;
		}
	}
	Press
	getchar();
	goto START;

RETURNBOOK:
	PrintBorrowedBook(Client_message);
	printf("输入要还书籍编号：\n	");
	j=scanf("%d", &bnm);
	getchar();
	if (!j)
	{
		printf("输入信息有误！\n");
		Press
			getchar();
		goto START;
	}
	rereturn=PersonalMessageManagement(Client_message, 'R', bnm);
	if (!rereturn)
	{
		Client_message->bbn--;
		printf("还书成功！\n");
	}
	else if (rereturn == -2)
	{
		printf("emmmmm算是还书成功了吧！\n");
		Client_message->bbn--;
	}
	else printf("还书失败！\n");
	Press
		getchar();
	goto START;

	system("pause");
	return EXIT_SUCCESS;
}