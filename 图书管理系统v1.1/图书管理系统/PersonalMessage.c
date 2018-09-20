#include "head.h"

int PersonalMessageManagement(user_t *usert , char ch , int bnum)																//存放用户的借存信息；
{
	FILE *pmm;
	time_t t;
	lr_t lr;
	struct tm *pt;
	char s[50];

	if ((pmm = fopen(usert->name, "rb+")) == NULL)
	{
		perror("fopen error");
		Press
			getchar();
		return -1;
	}

	time(&t);
	pt = localtime(&t);
	//sprintf(s, "%d/%d/%d %d:%d:%d", pt->tm_year + 1900, pt->tm_mon, pt->tm_mday, pt->tm_hour, pt->tm_min, pt->tm_sec);
	lr.lrt.year = pt->tm_year + 1900; lr.lrt.month = pt->tm_mon; lr.lrt.day = pt->tm_mday; lr.lrt.hour = pt->tm_hour; lr.lrt.min = pt->tm_min; lr.lrt.sec = pt->tm_sec;

#if(rmode)
	printf("%d/%d/%d %d:%d:%d", lr.lrt.year,lr.lrt.month,lr.lrt.day,lr.lrt.hour,lr.lrt.min,lr.lrt.sec);
#endif
	switch (ch)
	{	
	case 'L':
	{
				rewind(pmm);
				while (!feof(pmm))
				{
					fread(&lr, sizeof(lr_t), 1, pmm);
					if (lr.bnum == bnum && lr.useful == 1 && lr.lr=='L')
					{
						printf("您已经借过这本书且尚未归还！\n");
						Press
							getchar();
						fclose(pmm);
						return -1;
					}
				}
				lr.useful = 1;
				lr.lr = 'L';
				lr.bnum = bnum;
				lr.lrt.year = pt->tm_year + 1900; lr.lrt.month = pt->tm_mon; lr.lrt.day = pt->tm_mday; lr.lrt.hour = pt->tm_hour; lr.lrt.min = pt->tm_min; lr.lrt.sec = pt->tm_sec;
				fseek(pmm, 0, 2);
				fwrite(&lr, sizeof(lr_t), 1, pmm);
				fclose(pmm);
				return 0;
				break;
	}
	case 'R':
	{
				rewind(pmm);
				while (!feof(pmm))
				{
					fread(&lr, sizeof( lr_t), 1, pmm);
					if (lr.bnum == bnum && lr.useful == 1 && lr.lr=='L')
					{
						int rerb=ReturnBook(usert,lr.bnum);																//函数将其书数量+1；
						if (!rerb)
						{
							lr.useful = 0;
							fseek(pmm, -(int)sizeof(lr_t), 1);
							fwrite(&lr, sizeof(lr_t), 1, pmm);
							lr.lr = 'R';
							lr.lrt.year = pt->tm_year + 1900; lr.lrt.month = pt->tm_mon; lr.lrt.day = pt->tm_mday; lr.lrt.hour = pt->tm_hour; lr.lrt.min = pt->tm_min; lr.lrt.sec = pt->tm_sec;
							fseek(pmm, 0, 2);
							fwrite(&lr, sizeof(lr_t), 1, pmm);
							fclose(pmm);
							return 0;																								//返回0表示成功；
						}
						else if (rerb = -2)
						{
							lr.useful = -1;
							fseek(pmm, -(int)sizeof(lr_t), 1);
							fwrite(&lr, sizeof(lr_t), 1, pmm);
							lr.lr = 'R';
							lr.lrt.year = pt->tm_year + 1900; lr.lrt.month = pt->tm_mon; lr.lrt.day = pt->tm_mday; lr.lrt.hour = pt->tm_hour; lr.lrt.min = pt->tm_min; lr.lrt.sec = pt->tm_sec;
							fseek(pmm, 0, 2);
							fwrite(&lr, sizeof(lr_t), 1, pmm);
							fclose(pmm);
							return -2;																								//返回-2表示对已删除书籍的处理；
						}
						else
						{
							fclose(pmm);
							return -1;
						}
					}
				}
				printf("您没有此本书的借书记录！\n");
				Press
					getchar();
				fclose(pmm);
				return -1;																							//返回-1表示失败；
	}
	default:
		fclose(pmm);
		return -1;
		break;
	}
}