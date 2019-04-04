#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#pragma warning(disable:4013)
#pragma warning(disable:4996)

char *token, time_cmp[22], time_mer[7];
FILE *file = NULL;

void *file_open();
void file_close();
void GetData();

typedef struct log
{
	char IP[16];
	char Time[22];
	char Url[80];
	char Status[5];
	char year[5];
	char month[4];
	char day[3];
	char time[7];
}Log;

Log LogSet[20000] = { 0 };

int main()
{
	FILE *f;
	f = file_open();

	GetData();

	file_close(f);
	return 0;
}

void *file_open()
{
	char opcode[30];

	while (file == NULL)
	{
		printf("$ ");
		gets(opcode);
		token = strtok(opcode, " ");

		if (strcmp("read", token) == 0)
		{
			token = strtok(NULL, " ");
			file = fopen(token, "r");
			if (file == NULL)
			{
				printf("파일 열기 실패");
				exit(1);
			}
		}
		else
			printf("파일 이름을 확인해 주세요\n");
	}

	return file;
}

void file_close()
{
	fclose(file);
}

void GetData()
{
	char data[130];
	int i = 0, j = 0;

	fgets(data, sizeof(data), file);
	while (fgets(data, sizeof(data), file) != NULL)
	{

		token = strtok(data, ",");
		strcpy(LogSet[i].IP, data);

		token = strtok(NULL, ",");
		strcpy(LogSet[i].Time, token + 1);
		strcpy(time_cmp, LogSet[i].Time);

		token = strtok(NULL, ",");
		strcpy(LogSet[i].Url, token);

		token = strtok(NULL, "\n");
		strcpy(LogSet[i].Status, token);

		token = strtok(time_cmp, "/");
		strcpy(LogSet[i].day, token);

		token = strtok(NULL, "/");
		strcpy(LogSet[i].month, token);
		
		token = strtok(NULL, ":");
		strcpy(LogSet[i].year, token);

		token = strtok(NULL, ":");
		strcat(time_mer, token);

		token = strtok(NULL, ":");
		strcat(time_mer, token);

		token = strtok(NULL, "\n");
		strcat(time_mer, token);

		strcpy(LogSet[i].time, time_mer);
		i++;
	}

	printf("%s ", LogSet[0].Time);
}

void sort_by_time()
{
	


}

int cmp_fun(const void *p, const void *q)
{
	
}