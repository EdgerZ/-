#include "head.h"

//���鹦��
int REND(user_t * usert)			//ͨ���������ʵ�ֽ��鹦��
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
		printf("�����ɽ�������%d��Ȩ�޿ɽ�������Ϊ��%d��\n", usert->force, maxnum);
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
	printf("��ǰ�����ֵΪ��%d\n", BOOKNUM);
#endif
	int stlen = BOOKNUM - Startnum;
	fseek(rend, stlen*(sizeof(book_t)), 0);
	fread(&s, sizeof(book_t), 1, rend);
	s.count--;
	if (s.count < 0)
	{
		printf("�����������㣡��ѡ�������鼮��\n");
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
		printf("����ʧ�ܣ�\n");
		fclose(user);
		fclose(rend);
		return -1;
	}
	else
	{
		printf("�ɹ�!\n");
		printf("�鼮��Ϣ��NO.%d ���� : %s �ݲ����� : %d �ɽ����� : %d\n", s.num, s.name, s.tcount, s.count);

		rewind(user);																								//���û���bnnֵ������д;
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
