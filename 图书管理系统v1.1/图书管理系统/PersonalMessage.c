#include "head.h"

int PersonalMessageManagement(user_t *usert , char ch , int bnum)																//����û��Ľ����Ϣ��
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
						printf("���Ѿ�����Ȿ������δ�黹��\n");
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
						int rerb=ReturnBook(usert,lr.bnum);																//��������������+1��
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
							return 0;																								//����0��ʾ�ɹ���
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
							return -2;																								//����-2��ʾ����ɾ���鼮�Ĵ���
						}
						else
						{
							fclose(pmm);
							return -1;
						}
					}
				}
				printf("��û�д˱���Ľ����¼��\n");
				Press
					getchar();
				fclose(pmm);
				return -1;																							//����-1��ʾʧ�ܣ�
	}
	default:
		fclose(pmm);
		return -1;
		break;
	}
}