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
	nowday = pt->tm_mday;															//��ǰ��¼ʱ��ʱ�䣻

	rewind(cm);
	while (1)
	{
		memset(&lr, 0, sizeof(lr_t));
		fread(&lr, sizeof(lr_t), 1, cm);
		if (feof(cm))break;
		if (lr.lr == 'L' && lr.useful == 1)																							//�˸��ÿ���°�30�����;
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
				if (subday >Borrowtime)printf("������δ���鼮��NO.%d\t����ʱ��Ϊ��%d��\n", lr.bnum, subday-Borrowtime);
				if ((Borrowtime-subday ) <= 7)printf("���ΪNO.%d���鼮����7���ڵ���,�뼰ʱ���飡\n���������Ϊ��%d/%d/%d\n", lr.bnum,lr.lrt.year,retmon,retday);				//��������������⣡
			}
			else printf("̫�಻���㣡\n");
		}
	}
	fclose(cm);
	return 0;
}