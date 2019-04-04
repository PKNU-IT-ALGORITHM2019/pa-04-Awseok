#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#pragma warning(disable:4013)
#pragma warning(disable:4996)

char opcode[30] = { 0 }, *token, *sort_token, time_cmp[22], month[4], day[3], check_sort_type;
int arr_max;
FILE *file = NULL;

void *file_open();
void file_close();
void GetData();
void sort(int val);
int cmp_time(const void* p, const void* q);
int cmp_ip(const void* p, const void* q);
void month_to_Num();
void Run();
void print();

typedef struct log
{
	char IP[16];
	char Time[22];
	char Url[80];
	char Status[5];
	char time[15];
}Log;

Log LogSet[20000] = { 0 };

int main()
{
	file_open();

	GetData();

	Run();

	file_close();
	return 0;
}

void *file_open()
{

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

		token = strtok(data, ","); // IP
		strcpy(LogSet[i].IP, data);

		token = strtok(NULL, ","); // Time
		strcpy(LogSet[i].Time, token + 1);
		strcpy(time_cmp, LogSet[i].Time);

		token = strtok(NULL, ","); // Url
		strcpy(LogSet[i].Url, token);

		token = strtok(NULL, "\n"); // Status
		strcpy(LogSet[i].Status, token);

		token = strtok(time_cmp, "/"); // 일
		strcpy(day, token);

		token = strtok(NULL, "/"); // 달
		strcpy(month, token);
		month_to_Num();
		
		token = strtok(NULL, ":"); // 년
		strcat(LogSet[i].time, token);
		strcat(LogSet[i].time, month);
		strcat(LogSet[i].time, day);

		token = strtok(NULL, ":"); // 시
		strcat(LogSet[i].time, token);

		token = strtok(NULL, ":"); // 분
		strcat(LogSet[i].time, token);

		token = strtok(NULL, "\n"); // 초
		strcat(LogSet[i].time, token);

		i++;
	}
	arr_max = --i;
}

void sort(int val)
{
	if (val == 0)
		qsort(LogSet, arr_max, sizeof(Log), cmp_time);

	else
		qsort(LogSet, arr_max, sizeof(Log), cmp_ip);
}

int cmp_time(const void *p, const void *q)
{
	return (strcmp(((Log*)p)->time, ((Log*)q)->time));
}

int cmp_ip(const void* p, const void* q)
{
	return strcmp(((Log*)p)->IP, ((Log*)q)->IP);
}

void month_to_Num()
{
	if (strcmp(month, "Jan") == 0)
		strcpy(month, "01");
	else if (strcmp(month, "Feb") == 0)
		strcpy(month, "02");
	else if (strcmp(month, "Mar") == 0)
		strcpy(month, "03");
	else if (strcmp(month, "Apr") == 0)
		strcpy(month, "04");
	else if (strcmp(month, "May") == 0)
		strcpy(month, "05");
	else if (strcmp(month, "Jun") == 0)
		strcpy(month, "06");
	else if (strcmp(month, "Jul") == 0)
		strcpy(month, "07");
	else if (strcmp(month, "Aug") == 0)
		strcpy(month, "08");
	else if (strcmp(month, "Sep") == 0)
		strcpy(month, "09");
	else if (strcmp(month, "Oct") == 0)
		strcpy(month, "10");
	else if (strcmp(month, "Nov") == 0)
		strcpy(month, "11");
	else if (strcmp(month, "Dec") == 0)
		strcpy(month, "12");
}

void Run()
{
	while (strcmp(opcode, "exit"))
	{
		printf("$ ");
		gets(opcode);
		token = strtok(opcode, " ");
		sort_token = strtok(NULL, "\n");
		if (strcmp(token, "sort") == 0 && sort_token != NULL)
		{
			//token = strtok(NULL, "\n");
			if (strcmp(sort_token + 1, "t") == 0)
			{
				sort(0); // 0 = t, 1 = ip
				check_sort_type = 0;
			}
			else
			{
				sort(1);
				check_sort_type = 1;
			}
		}
		else if (strcmp(token, "print") == 0)
			print();
		else
			puts("명령어를 확인해 주세요");
	}
}

void print()
{
	int i;

	if (check_sort_type == 0)
	{
		for (i = 0; i < arr_max; i++)
		{
			puts(LogSet[i].Time);
			printf("\t%s\n\t%s\n\t%s\n", LogSet[i].IP, LogSet[i].Url, LogSet[i].Status);
		}
	}
	else
	{
		for (i = 0; i < arr_max; i++)
		{
			puts(LogSet[i].IP);
			printf("\t%s\n\t%s\n\t%s\n", LogSet[i].Time, LogSet[i].Url, LogSet[i].Status);
		}
	}
}