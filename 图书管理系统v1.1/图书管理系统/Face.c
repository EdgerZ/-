#include "head.h"

extern MaxBookNum = 0;

void Face()
{
	FILE *li;
	int num = 0, len = sizeof(book_t), ret = 0;
	book_t *s = malloc(sizeof(book_t));
	extern int MaxBookNum;
	//��ʼǰ�Լ��鼮����Ƿ�����
	if ((li = fopen(filename, "rb+")) == NULL)
	{
		perror("open file error");
		exit(0);
	}
		if ((ret = fseek(li, 0, 2)) == -1)
		{
			perror("fseek error");
			return;
		}
		if (ftell(li) == 0)num = 9999;
		else {
			fseek(li, -len, 2);
			fread(s, len, 1, li);
			num = s->num;
			MaxBookNum = num;
		}

	for (int i = 0; i < Round; i++)
	{
		printf("ͼ�����ϵͳ�����У�\\");
		Sleep(Sleeptime);
		system("cls");
		printf("ͼ�����ϵͳ�����У�|");
		Sleep(Sleeptime);
		system("cls");
		printf("ͼ�����ϵͳ�����У�/");
		Sleep(Sleeptime);
		system("cls");
		printf("ͼ�����ϵͳ�����У���");
		Sleep(Sleeptime);
		system("cls");
	}
	fclose(li);
	return;
}