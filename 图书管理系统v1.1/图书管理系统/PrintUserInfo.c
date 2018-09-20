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
	while (1)																						//��ӡ�û������н軹���¼;
	{
		i++;
		memset(&lr, 0, sizeof(lr_t));
		fread(&lr, sizeof(lr_t), 1, palr);
		if (feof(palr))break;
		printf("��¼%d�����NO.%d\t%c\t%d/%d/%d\t��¼��Ч�ԣ�%d\n", i, lr.bnum, lr.lr, lr.lrt.year, lr.lrt.month + 1, lr.lrt.day, lr.useful);
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
		return -1;																		//����-1Ȩ�޸���ʧ��:
	}
	fseek(cea, (num - Startusernum)*sizeof(user_t), 0);
	fread(&usert, sizeof(user_t), 1, cea);
#if(rmode)
	printf("�û���ϢΪ��NO.%d\t�û�����%s\t��¼Ȩ�ޣ�%d\t�û�Ȩ�ޣ�%d\n", usert.num, usert.name, usert.loginauthorize, usert.force);
#endif
	printf("��Ҫ���û�NO.%dȨ�޸���Ϊ��(��ǰ�û�����Ȩ��Ϊ%d)(����С��5����������\n",num,usert.force);
	scanf("%d", &level);
	getchar();
	if (level>=0 && level <5)
	{
		usert.force = level;
		fseek(cea, (num - Startusernum)*sizeof(user_t), 0);
		fwrite(&usert, sizeof(user_t), 1, cea);
		printf("��ǰ����Ȩ��Ϊ��%d\n", usert.force);
		Press
			getchar();
		fclose(cea);
		return 0;																		//����0Ȩ�޸��ĳɹ���
	}
	else
	{
		printf("�����Ȩ������\n");
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
		return -1;																		//����-1Ȩ�޸���ʧ��:
	}
	fseek(cla, (num - Startusernum)*sizeof(user_t), 0);
	fread(&usert, sizeof(user_t), 1, cla);
#if(rmode)
	printf("�û���ϢΪ��NO.%d\t�û�����%s\t��¼Ȩ�ޣ�%d\t�û�Ȩ�ޣ�%d\n", usert.num, usert.name, usert.loginauthorize, usert.force);
#endif
	printf("��Ҫ���û�NO.%dȨ�޸���Ϊ��(��ǰ�û���¼Ȩ��Ϊ%d)(����0��1��\n", num, usert.loginauthorize);
	scanf("%d", &level);
	getchar();
	if (level == 0 || level ==1)
	{
		usert.loginauthorize = level;
		fseek(cla, (num - Startusernum)*sizeof(user_t), 0);
		fwrite(&usert, sizeof(user_t), 1, cla);
		printf("��ǰ��¼Ȩ��Ϊ��%d\n", usert.loginauthorize);
		Press
			getchar();
		fclose(cla);
		return 0;																		//����0Ȩ�޸��ĳɹ���
	}
	else
	{
		printf("�����Ȩ������\n");
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
			return -1;																		//����-1����ʧ�ܣ�
	}

	fseek(pui, -(int)sizeof(user_t), 2);
	fread(&usert, sizeof(user_t), 1, pui);

	printf("�����û���ţ�(��ǰ�û���߱��Ϊ��%d)\n",usert.num);
	scanf("%d", &Num);
	getchar();

	if (Num > usert.num || Num<Startusernum)
	{
		printf("û������û�����ǰ�û���߱��Ϊ��%d,���Ϊ��%d\n", usert.num,Startusernum);
		fclose(pui);
		Press
			getchar();
		printf("�Ƿ�������������y/n)");
		char ch = getchar();
		switch (ch)
		{
		case 'y':fclose(pui); return User_NumSearch();
		case 'n':fclose(pui); return -1;													//����-1����ʧ�ܣ�
		default:printf("û��������");
			Press
			fclose(pui);
			break;
		}
	}
//	fseek(pui, 0, 0);														//�ļ�λ�ñ�ǻ��㣻
	fseek(pui, (Num - Startusernum)*sizeof(user_t), 0);
	fread(&usert, sizeof(user_t), 1, pui);
	printf("�û���ϢΪ��NO.%d\t�û�����%s\t��¼Ȩ�ޣ�%d\t�û�Ȩ�ޣ�%d\n", usert.num, usert.name, usert.loginauthorize, usert.force);
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

	printf("������Ҫ�������û�����\n");
	scanf("%s", s);
	getchar();
	fseek(pui, 0, 0);
	while (!feof(pui))
	{
		fread(&usert, sizeof(user_t), 1, pui);
		if (!strcmp(usert.name, s))
		{
			printf("�û���ϢΪ��NO.%d\t�û�����%s\t��¼Ȩ�ޣ�%d\t�û�Ȩ�ޣ�%d\n", usert.num, usert.name, usert.loginauthorize, usert.force);
			fclose(pui);
			return usert.num;
		}
	}
	printf("û������û����Ƿ������������y/n��");
	char ch = getchar();
	switch (ch)
	{
	case 'y':fclose(pui); return User_NameSearch();
	case 'n':fclose(pui); return -1;													//����-1����ʧ�ܣ�
	default:printf("û��������");
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
		printf("�û���ϢΪ��NO.%d\t�û�����%s\t��¼Ȩ�ޣ�%d\t�û�Ȩ�ޣ�%d\n", usert.num, usert.name, usert.loginauthorize, usert.force);
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
		printf("�û���Ϣ��ӡʧ�ܡ�\n");
		system("pause");
		return;
	}

	fseek(pui, 0, 2);
	int tlen = ftell(pui);
	if (tlen == 0)																			//	���ݿ�Ϊ��ʱ
	{
		printf("�����û���Ϣ��\n");
		Press
		getchar();
		return;
	}
	fclose(pui);																				//ȷ���ļ���Ϊ�պ�ر��ļ���

	printf("�������/�û�������/ȫ����ӡ��n/s/a����\n");
	char ch = getchar();
	switch (ch)
	{
	case 'n':renum=User_NumSearch(); fclose(pui); break;
	case 's':renum=User_NameSearch(); fclose(pui); break;
	case 'a':getchar(); renum = User_PrintAll(); fclose(pui); break;			//�˺���û�����뺯��������Ҫʹ��getchar����һ���س���
	default:
		printf("û���������\n");
		Press
		getchar();
		PrintUserInfo();
	}
	if (renum == -1)return;
	Press																						//�����������ͣ��;
		getchar();

CHANGEAUTHORITY:
	if (ch == 'a')system("cls");
	else
	{
		printf("ѡ����Ҫ���еĲ�����\n");
		printf("�ı��û�����Ȩ�ޣ�c\n");
		printf("�ı��û���¼Ȩ�ޣ�l\n");
		printf("����ѡ���������ܣ�r\n");
		printf("��ӡ���û����н�����Ϣ��q\n");
		printf("�����в�����e\n");
		ch = getchar();
		switch (ch)
		{
		case 'c':rechg = ChangeExecutiveAuthority(renum); break;
		case 'l':rechg = ChangeLoginAuthority(renum); break;
		case 'r':getchar(); system("cls"); PrintUserInfo();
		case 'e':getchar(); return;
		case 'q':getchar(); PrintAllLR(renum); break;
		default:
			printf("���޸ò�����\n");
			goto CHANGEAUTHORITY;
			break;
		}
		if (!rechg)printf("���ĳɹ���\n");
		else printf("����ʧ�ܣ�\n");
	}
	return;
}

