#include"head.h"

void PrintDeleteMessage()
{
	FILE *pdm;
	dbm_t dbmt;
	int i = 0;

	if ((pdm = fopen(Deletefilename, "rb")) == NULL)
	{
		perror("fopen error");
		Press
			getchar();
		return;
	}
	rewind(pdm);

	while (1)
	{
		i++;
		fread(&dbmt, sizeof(dbm_t), 1, pdm);
		if (feof(pdm))break;
		printf("��%d��ɾ����Ϣ��NO.%d\t������%s\t%d/%d/%d %d:%d:%d\tɾ����Ч�ԣ�%d\n", i, dbmt.bookmessage.num, dbmt.bookmessage.name, dbmt.time.year, dbmt.time.month, dbmt.time.day, dbmt.time.hour, dbmt.time.min, dbmt.time.sec, dbmt.useful);
	}
	fclose(pdm);
	return;
}