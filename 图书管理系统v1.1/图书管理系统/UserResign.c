#include "head.h"

int  USERREG(char *String)
{
	char ch;
	system("cls");
	printf("�û��������ڣ��Ƿ�ע�᣿��y/n)\n");
	ch = getchar();
	if (ch == 'n' || ch == 'y')
	{
		if (ch == 'n')return 0;
	}
	else
	{
		printf("���������������");
		Press
		getchar();
		return 0;
	}
	FILE *user;
	user_t usert, temp;
	char rec[50] = { 0 };
	if ((user = fopen(userfilename, "ab+")) == NULL)
	{
		perror("fopen error");
		return -1;						//����-1ע��ʧ��;
	}
	fseek(user, 0, 2);
	int tlen = ftell(user);
	if (tlen == 0)usert.num = Startusernum;
	else
	{
		fseek(user, -(int)sizeof(user_t), 2);
		fread(&temp, sizeof(user_t), 1, user);
		usert.num = temp.num + 1;
	}

	printf("������Ҫע����û�����\n");
	strcpy(usert.name,String);
	printf("%s\n", usert.name);
	getchar();
REC:
	printf("�������룺\n");
	scanf("%s", usert.pswd);
	getchar();
	printf("�ٴ��������룺\n");
	scanf("%s", rec);
	getchar();
	if (strcmp(usert.pswd, rec))
	{
		printf("�������벻ͬ;");
		goto REC;
	}
	usert.force = 1;
	usert.bbn = 0;
	usert.loginauthorize = 1;
	fseek(user, 0, 2);
	fwrite(&usert, sizeof(user_t), 1, user);
	fclose(user);

	FILE *creat;
	if ((creat = fopen(usert.name, "wb")) == NULL)
	{
		perror("fcreate error");
		Press
			getchar();
		return -1;
	}
	fclose(creat);
	printf("ע��ɹ���\n");
	return 1;
}
