#include "head.h"

//����Ų�ѯ��
int SearchNum(void)
{
	BOOKNUM = 0;
	FILE *sn;
	book_t *s = malloc(sizeof(book_t));
	int stlen = 0, tlen = 0, schnum = 0;


	if ((sn = fopen(filename, "rb")) == NULL)
	{
		perror("fileopen error");
		exit(0);
	}
	fseek(sn, 0, 2);
	tlen = ftell(sn);
	if (tlen == 0)
	{
		printf("NO RECORD!\n");
		Press
			getchar();
		fclose(sn);
		return -2;																	//NO RECORD ���أ�
	}
	fseek(sn, (-(int)sizeof(book_t)), 2);
	fread(s, sizeof(book_t), 1, sn);

	printf("���������(���Ϊ%d)��", s->num);
	scanf("%d", &schnum);
	getchar();														//��������س���

	if (s->num < schnum)
	{
		printf("NO RECORD! Max Num : %d\n", s->num);
		free(s);
		fclose(sn);
		return -1;												//��ʾ����û���Ȿ��  ���أ�
	}
	else if (schnum < Startnum)printf("�������������С���Ϊ10000��\n");
	else
	{
		stlen = schnum - Startnum;
		fseek(sn, stlen*(sizeof(book_t)), 0);
		fread(s, sizeof(book_t), 1, sn);
		if (s->tcount == 0)
		{
			printf("������Ϣ�ѱ�ɾ����\n");
			return -1;
		}
		else	printf("NO.%d ����:%s �ݲ�����:%d �ɽ�����:%d\n", s->num, s->name, s->tcount, s->count);
		if (s->count)
		{
			BOOKNUM = s->num;
			free(s);
			fclose(sn);
			return 1;								//����1��ʾ��ѯ��Ϣ���������飻
		}
		else{
			free(s);
			fclose(sn);
			return 0;						//����2��ʾ���飻
		}
	}
	return 0;
}
//�ı�����Ϣ��
void DATACHANGE()
{
	return;
}


//����������
int SearchName(void)
{
	BOOKNUM = 0;
	FILE *sn;
	char s[50];
	book_t scmp;
	int fok = 0;
	if ((sn = fopen(filename, "rb")) == NULL)
	{
		perror("fopen error");
		return -1;								//����-1�ļ���ʧ�ܣ�
	}
	printf("�������������");
	scanf("%s", s);
	getchar();
	fseek(sn, 0, 2);
	int tlen = ftell(sn);
	if (tlen == 0)
	{
		printf("NO RECORD!\n");
		fclose(sn);
		Press
			getchar();
		return -2;																	//NO RECORD ���أ�
	}
	rewind(sn);
	while (!feof(sn))
	{
		fread(&scmp, sizeof(book_t), 1, sn);
		if (!strcmp(scmp.name, s))
		{
			fok = 1;
			break;
		}
	}
	if (fok == 0)
	{
		printf("NO RECORD!\n");
		fclose(sn);
		return 0;							//����0û�и��ļ���
	}
	else
	{
		if (scmp.tcount == 0)
		{
			printf("���鼮��Ϣ�ѱ�ɾ����\n");
			return 0;
		}
		printf("�鼮��Ϣ��NO.%d ���� : %s �ݲ����� : %d �ɽ����� : %d\n", scmp.num, scmp.name, scmp.tcount, scmp.count);
		BOOKNUM = scmp.num;
		fclose(sn);
		return 1;							//����1�ҵ������鼮��
	}
}
