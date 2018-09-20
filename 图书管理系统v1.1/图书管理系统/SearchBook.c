#include "head.h"

//按书号查询；
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
		return -2;																	//NO RECORD 返回；
	}
	fseek(sn, (-(int)sizeof(book_t)), 2);
	fread(s, sizeof(book_t), 1, sn);

	printf("输入索书号(最大为%d)：", s->num);
	scanf("%d", &schnum);
	getchar();														//用来输入回车；

	if (s->num < schnum)
	{
		printf("NO RECORD! Max Num : %d\n", s->num);
		free(s);
		fclose(sn);
		return -1;												//表示表内没有这本书  返回；
	}
	else if (schnum < Startnum)printf("输入书号有误：最小书号为10000。\n");
	else
	{
		stlen = schnum - Startnum;
		fseek(sn, stlen*(sizeof(book_t)), 0);
		fread(s, sizeof(book_t), 1, sn);
		if (s->tcount == 0)
		{
			printf("该书信息已被删除！\n");
			return -1;
		}
		else	printf("NO.%d 书名:%s 馆藏总量:%d 可借数量:%d\n", s->num, s->name, s->tcount, s->count);
		if (s->count)
		{
			BOOKNUM = s->num;
			free(s);
			fclose(sn);
			return 1;								//返回1表示查询信息结束：有书；
		}
		else{
			free(s);
			fclose(sn);
			return 0;						//返回2表示无书；
		}
	}
	return 0;
}
//改变借出信息；
void DATACHANGE()
{
	return;
}


//按书名索引
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
		return -1;								//返回-1文件打开失败；
	}
	printf("输入检索书名：");
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
		return -2;																	//NO RECORD 返回；
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
		return 0;							//返回0没有该文件；
	}
	else
	{
		if (scmp.tcount == 0)
		{
			printf("该书籍信息已被删除！\n");
			return 0;
		}
		printf("书籍信息：NO.%d 书名 : %s 馆藏总量 : %d 可借数量 : %d\n", scmp.num, scmp.name, scmp.tcount, scmp.count);
		BOOKNUM = scmp.num;
		fclose(sn);
		return 1;							//返回1找到检索书籍；
	}
}
