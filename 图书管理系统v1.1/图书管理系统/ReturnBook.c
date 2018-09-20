#include "head.h"

int ReturnBook(user_t *usert,int bnum)
{
	FILE * rb;
	FILE *user;
	book_t bookt;
	user_t userr;

	if ((rb = fopen(filename, "rb+")) == NULL)
	{
		perror("fopen error");
		Press
			getchar();
		fclose(rb);
		return -1;
	}

	if ((user = fopen(userfilename, "rb+")) == NULL)
	{
		perror("fopen error");
		Press
			getchar();
		fclose(user);
		return -1;
	}

	fseek(user, sizeof(user_t)*(usert->num - Startusernum), 0);												//对用户的bbn重写;
	fread(&userr, sizeof(user_t), 1, user);
	userr.bbn--;
	fseek(user, sizeof(user_t)*(usert->num - Startusernum), 0);
	fwrite(&userr, sizeof(user_t), 1, user);
	fclose(user);

	fseek(rb, sizeof(book_t)*(bnum - Startnum), 0);												//对book的count重写;
	fread(&bookt, sizeof(book_t), 1, rb);
	if (bookt.tcount == 0)
	{
		printf("书籍信息已被删除！对！你没看错！这本书送你了！\n");
		return -2;
	}
	bookt.count++;
	fseek(rb, sizeof(book_t)*(bnum - Startnum), 0);
	fwrite(&bookt, sizeof(book_t), 1, rb);
	fclose(rb);


	return 0;
}