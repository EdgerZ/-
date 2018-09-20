#include "head.h"

int DeleteMessage(int bnum)
{
	FILE *dm;
	book_t bookt;
	FILE *dmf;
	dbm_t dbm;

	if ((dm = fopen(filename, "rb+")) == NULL)
	{
		perror("fopen error");
		Press
			getchar();
		return -1;
	}

	fseek(dm, sizeof(book_t)*(bnum - Startnum), 0);
	fread(&bookt, sizeof(book_t), 1, dm);
	if (bookt.tcount == 0)
	{
		printf("该书籍信息已被删除！\n");
		fclose(dm);
		return -1;
	}

	if ((dmf = fopen(Deletefilename, "rb+")) == NULL)
	{
		perror("fopen error");
		Press
			getchar();
		return -1;
	}


	printf("需要删除的书籍信息为：NO.%d\t书名：%s\t馆藏总量：%d\t馆内数量：%d\n", bookt.num, bookt.name, bookt.tcount, bookt.count);
#if(rmode)
	printf("NO.%d\t%s\t%d\t%d\n", bookt.num, bookt.name, bookt.tcount, bookt.count);
#endif
	dbm.bookmessage.num = bookt.num; strcpy(dbm.bookmessage.name, bookt.name); dbm.bookmessage.tcount = bookt.tcount; dbm.bookmessage.count = bookt.count;
	dbm.time = *(my_GetCurrentTime());
	dbm.useful = 1;
#if(rmode)
	printf("NO.%d\t书名：%s\t%d/%d/%d %d:%d:%d\t删除有效性：%d\n", dbm.bookmessage.num, dbm.bookmessage.name, dbm.time.year, dbm.time.month, dbm.time.day, dbm.time.hour, dbm.time.min, dbm.time.sec, dbm.useful);
#endif
	fseek(dmf, 0, 2);
	fwrite(&dbm, sizeof(dbm_t), 1, dmf);																						//将原始数据备份到deletemessage文件中；
	bookt.tcount = 0; bookt.count = 0;
#if(rmode)
	printf("NO.%d\t%s\t%d\t%d\n", bookt.num, bookt.name, bookt.tcount, bookt.count);
#endif
	fseek(dm, sizeof(book_t)*(bnum - Startnum), 0);
	fwrite(&bookt, sizeof(book_t), 1, dm);																					//将清零后的记录覆盖到源数据的位置；
	fclose(dm);
	fclose(dmf);
	return 0;
}