#include "head.h"
//¼����Ϣ��
void Loadin(void)
{
	FILE *li;
	int num = 0, same = 0, len = sizeof(book_t), tlen = 0, loadok = 0, ret = 0;
	book_t *s = malloc(sizeof(book_t));
	book_t *scmp = malloc(sizeof(book_t));
	extern int MaxBookNum;

	if ((li = fopen(filename, "rb+")) == NULL)
	{
		perror("open file error");
		exit(0);
	}
	while (1)
	{
		same = 0;
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
	RELOAD:
		if (!loadok)
		{
			printf("�Ա�׼��ʽ�����鼮��Ϣ����ǰλ��Ϊ��%d\n", MaxBookNum + 1);
			printf("����10000 ������ڡ� 5 5\n");
		}
		scanf("%d %s %d %d", &(s->num), s->name, &(s->tcount), &(s->count));
		getchar();
		if (s->num == 0)
		{
			system("cls");
			break;		//��Ϣ¼�������
		}
		else if (s->num == 1)
		{
			rewind(li);
			while (1)
			{
				memset(scmp, 0, len);
				fread(scmp, len, 1, li);
				if (feof(li))break;
				if (scmp->num)
				{
					if(scmp->tcount)printf("�鼮��Ϣ :NO.%d \t���� : %s \t�ݲ����� : %d \t�ɽ����� : %d\n", scmp->num, scmp->name, scmp->tcount, scmp->count);
					else printf("����ɾ�����鼮��Ϣ :NO.%d \t���� : %s \t�ݲ����� : %d \t�ɽ����� : %d\n", scmp->num, scmp->name, scmp->tcount, scmp->count);
				}
			}
			goto RELOAD;
		}
		if (s->num != num + 1)
		{
			printf("����������!\n");
			loadok = 0;
			goto RELOAD;
		}
		rewind(li);
		while (!feof(li))
		{
			fread(scmp, len, 1, li);
#if(rmode)
			printf("\t������scmp:%d %s %d %d\n", scmp->num, scmp->name, scmp->tcount, scmp->count);
#endif
			if (strcmp(scmp->name, s->name) == 0)
			{
				same = 1;
#if(rmode)
				printf("\tsame=1\n");
#endif
				break;
			}
			memset(scmp, 0, len);
		}
		if (same == 1)
		{
			loadok = 1;
			scmp->count += s->count;
			scmp->tcount += s->tcount;
			fseek(li, -len, 1);
			int ifret = fwrite(scmp, len, 1, li);																	//���ݸ���;
#if(rmode)
			book_t temp;
			printf("\trmode:ret(fwrite) =  %d\n", ifret);
			fseek(li, -len, 1);
			fread(&temp, len, 1, li);
			printf("\t%d %s %d %d\n", temp.num, temp.name, temp.tcount, temp.count);
			int ret_ftell = ftell(li) / len;
			printf("\tret_ftell = %d\n", ret_ftell);
#endif
			printf("¼���鼮���ظ�����Ϣ����Ϊ��\n%d %s %d %d\n", scmp->num, scmp->name, scmp->tcount, scmp->count);		//��ʱ�ļ�λ�ñ��ָ����ͬ���ݣ�
			printf("�ɹ�!  ��ǰλ��Ϊ��%d\n", num + 1);
		}
		else
		{
			fseek(li, 0L, 2);
			fwrite(s, len, 1, li);
			printf("�ɹ���ǰλ��Ϊ��%d\n", num + 2);
			loadok = 1;
		}
	}
	printf("����¼�����;\n");
	free(s);
	free(scmp);
	fclose(li);
}
