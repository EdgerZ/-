#include "head.h"

int CheckMessage(user_t *usert)
{
	FILE* cm;
	int nowmon = 0, nowday = 0;
	time_t t;
	struct tm *pt;
	lr_t lr;
	int subday = 0, retmon = 0, retday = 0;

	if ((cm = fopen(usert->name, "rb")) == NULL)
	{
		perror("fopen error");
		Press
			getchar();
		return -1;
	}
	time(&t);
	pt = localtime(&t);
	nowmon = pt->tm_mon;
	nowday = pt->tm_mday;															//当前登录时的时间；

	rewind(cm);
	while (1)
	{
		memset(&lr, 0, sizeof(lr_t));
		fread(&lr, sizeof(lr_t), 1, cm);
		if (feof(cm))break;
		if (lr.lr == 'L' && lr.useful == 1)																							//阉割版每个月按30天计算;
		{
			if (lr.lrt.year == (pt->tm_year +1900))
			{
				subday = (pt->tm_mon - lr.lrt.month) * 30 + (pt->tm_mday - lr.lrt.day);
				retmon = lr.lrt.month + 1; retday = lr.lrt.day + 7;
				if (retday > 30)
				{
					retday -= 30;
					retmon += 1;
					if (retmon > 12)retmon -= 12;
				}
				if (subday >Borrowtime)printf("有逾期未还书籍：NO.%d\t逾期时间为：%d天\n", lr.bnum, subday-Borrowtime);
				if ((Borrowtime-subday ) <= 7)printf("书号为NO.%d的书籍将在7天内到期,请及时还书！\n最后还书日期为：%d/%d/%d\n", lr.bnum,lr.lrt.year,retmon,retday);				//最后还书日期有问题！
			}
			else printf("太多不爱算！\n");
		}
	}
	fclose(cm);
	return 0;
}