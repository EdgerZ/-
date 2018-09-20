#include "head.h"
//录入信息；
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
			printf("以标准格式输入书籍信息：当前位置为：%d\n", MaxBookNum + 1);
			printf("例：10000 《红与黑》 5 5\n");
		}
		scanf("%d %s %d %d", &(s->num), s->name, &(s->tcount), &(s->count));
		getchar();
		if (s->num == 0)
		{
			system("cls");
			break;		//信息录入结束；
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
					if(scmp->tcount)printf("书籍信息 :NO.%d \t书名 : %s \t馆藏总量 : %d \t可借数量 : %d\n", scmp->num, scmp->name, scmp->tcount, scmp->count);
					else printf("（已删除）书籍信息 :NO.%d \t书名 : %s \t馆藏总量 : %d \t可借数量 : %d\n", scmp->num, scmp->name, scmp->tcount, scmp->count);
				}
			}
			goto RELOAD;
		}
		if (s->num != num + 1)
		{
			printf("输入编号有误!\n");
			loadok = 0;
			goto RELOAD;
		}
		rewind(li);
		while (!feof(li))
		{
			fread(scmp, len, 1, li);
#if(rmode)
			printf("\t读出的scmp:%d %s %d %d\n", scmp->num, scmp->name, scmp->tcount, scmp->count);
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
			int ifret = fwrite(scmp, len, 1, li);																	//数据覆盖;
#if(rmode)
			book_t temp;
			printf("\trmode:ret(fwrite) =  %d\n", ifret);
			fseek(li, -len, 1);
			fread(&temp, len, 1, li);
			printf("\t%d %s %d %d\n", temp.num, temp.name, temp.tcount, temp.count);
			int ret_ftell = ftell(li) / len;
			printf("\tret_ftell = %d\n", ret_ftell);
#endif
			printf("录入书籍名重复，信息更新为：\n%d %s %d %d\n", scmp->num, scmp->name, scmp->tcount, scmp->count);		//此时文件位置标记指向相同数据；
			printf("成功!  当前位置为：%d\n", num + 1);
		}
		else
		{
			fseek(li, 0L, 2);
			fwrite(s, len, 1, li);
			printf("成功当前位置为：%d\n", num + 2);
			loadok = 1;
		}
	}
	printf("数据录入结束;\n");
	free(s);
	free(scmp);
	fclose(li);
}
