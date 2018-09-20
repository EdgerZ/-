#include "head.h"

void PrintBorrowedBook(user_t * usert)
{
	FILE *pbb;
	lr_t lr;
	book_t bookt;
	int i = 0;
	FILE *bk;
	if ((bk = fopen(filename, "rb")) == NULL)
	{
		perror("fopen error");
		Press
			getchar();
		exit(0);
	}

	if ((pbb = fopen(usert->name, "rb")) == NULL)
	{
		perror("fopen error");
		Press
			getchar();
		exit(0);
	}
	rewind(pbb);
	while (1)
	{
		memset(&lr, 0, sizeof(lr_t));
		if (feof(pbb))break;
		fread(&lr, sizeof(lr_t), 1, pbb);
		if (lr.lr == 'L' && lr.useful == 1)
		{
			i++;
			rewind(bk);
			fseek(bk,sizeof(book_t)*(lr.bnum - Startnum), 0);
			fread(&bookt, sizeof(book_t), 1, bk);
			printf("第%d条信息：NO.%d  %s 借阅时间：%d/%d/%d 借阅周期：%d\n", i, lr.bnum,bookt.name, lr.lrt.year, lr.lrt.month+1, lr.lrt.day,Borrowtime);
		}
	}
	fclose(pbb);
	fclose(bk);
	return;
}