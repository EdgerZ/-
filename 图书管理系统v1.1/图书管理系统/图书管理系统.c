#include "head.h"

//���ܣ��û���¼ ע�� ����ѯ(���롢����)���޸ġ�ɾ����׷�ӣ�

extern  BOOKNUM=0;								//����BOOKNUM������Ž�����鼮��

//�û�Ȩ�ޣ�	1�������鼮��Ϣ��
//						2�����黹�飻
//						3��


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
	root = 0;																//root��0��
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
			printf("�������\n");
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
		if (tlen == 0)									//��һ���û���ע��;
		{
			temp = USERREG(&Client_name);					//�û���ע�᣻
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
			printf("�������룺\n");
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
							printf("\n������˺�������ȷ,������Ա�������ķ��ʣ�\n");
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
						printf("�������\n");
						Press
						getchar();						//�������������
						goto CLIENTLOG;
					}
				}
			}
			temp=USERREG(&Client_name);				//���ݿ���û�и��û���Ϣ����ʼ�û�ע�᣻
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
		if (root)printf("����Ա�˺ţ�root Ȩ�޵ȼ�Ϊ5\n");
		else
		{
			printf("�û���Ϣ��NO.%d %s Ȩ�޵ȼ�Ϊ��%d �ѽ�������Ϊ��%d\n", Client_message->num, Client_message->name, Client_message->force,Client_message->bbn);
			putchar(10);
			retcheck=CheckMessage(Client_message);
			putchar(10);
		}
	}
	printf("�����������n\n");
	printf("������������s\n");
	if (login && Client_message->bbn &&!root )printf("���飺r\n");
	if (root)printf("¼����Ϣ��l\n");
	if (root)printf("ɾ���鼮��Ϣ��d\n");
	if (root)printf("��ʾ������ɾ���鼮��Ϣ��m\n"); 
	if (root)printf("��ʾ�û���Ϣ��p\n");
	if (login)printf("�˳���¼��e\n");
	printf("�˳���t\n");

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
					printf("��û�в���Ȩ��;\n");
					Press
					getchar();
					goto START;
				}
	}
	case 'd':
	{
				if (root)
				{
					printf("�����鼮��Ϣ���£�\n");
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
							if (scmp->tcount)printf("�鼮��Ϣ :NO.%d \t���� : %s \t�ݲ����� : %d \t�ɽ����� : %d\n", scmp->num, scmp->name, scmp->tcount, scmp->count);
							else printf("����ɾ�����鼮��Ϣ :NO.%d \t���� : %s \t�ݲ����� : %d \t�ɽ����� : %d\n", scmp->num, scmp->name, scmp->tcount, scmp->count);
						}
					}
					fclose(li);
					printf("��������Ҫɾ������ţ�");
					dnum = 0;
					scanf("%d", &dnum);
					if (dnum < 10000 || dnum > MaxBookNum)
					{
						printf("�޴���ţ�\n");
						getchar();
						goto START;
					}
					getchar();
					retdelete=DeleteMessage(dnum);
					if (!retdelete)printf("ɾ���ɹ���\n");
					else printf("ɾ��ʧ�ܣ�\n");
					Press
						getchar();
					goto START;
				}
				else
				{
					printf("��û�в���Ȩ��;\n");
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
					printf("��û�в���Ȩ��;\n");
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
					printf("��û�в���Ȩ��;\n");
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
					printf("δ��¼��\n");
					Press
					getchar();
					goto START;
				}
	}
	case 't':exit(0);
	default:
				printf("�޸ù��ܣ�\n");
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
	//	if(rets==0)																//������
	//{
	//	printf("�Ȿ��������޿ɽ衣�Ƿ��ӡ������Ϣ��y/n\n");
	//	scanf("%c", &chsys);
	//	if (chsys == 'y')
	//		PTDATA();
	//	BOOKNUM=0;
	//	printf("���� ��Ŀ¼:\n");
	//}
	if (rets == 1&& Client_message->force >1 &&!root)
	{
		printf("�Ƿ�Ҫ������飿y/n\n");
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
	//	printf("�Ȿ��������޿ɽ衣�Ƿ��ӡ������Ϣ��y/n\n");
	//	scanf("%c", &chnys);
	//	if (chnys == 'y')
	//		PTDATA();
	//	BOOKNUM=0;
	//	printf("���� ��Ŀ¼:\n");
	//}
	if (retn == 1 && Client_message->force >1 &&!root)
	{
		printf("�Ƿ�Ҫ������飿y/n\n");
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
	printf("����Ҫ���鼮��ţ�\n	");
	j=scanf("%d", &bnm);
	getchar();
	if (!j)
	{
		printf("������Ϣ����\n");
		Press
			getchar();
		goto START;
	}
	rereturn=PersonalMessageManagement(Client_message, 'R', bnm);
	if (!rereturn)
	{
		Client_message->bbn--;
		printf("����ɹ���\n");
	}
	else if (rereturn == -2)
	{
		printf("emmmmm���ǻ���ɹ��˰ɣ�\n");
		Client_message->bbn--;
	}
	else printf("����ʧ�ܣ�\n");
	Press
		getchar();
	goto START;

	system("pause");
	return EXIT_SUCCESS;
}