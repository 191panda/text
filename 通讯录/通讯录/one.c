#define _CRT_SECURE_NO_WARNINGS

#include<stdio.h>
#include<string.h>
#include<errno.h>
#include<stdlib.h>
#include <windows.h>//Sleep

#define MAX 100
#define NAME 20
#define NUB 13
#define PHONE 13
#define SEX 10
#define IP 20
#define AGE 10

void caidan();
void addren(int* conut);
void seeren(int* conut);
void deleteren(int* conut);
void findren(int* conut);
void modifyren(int* conut);
void sortren(int* conut);
void TongJi(int* conut);//ͳ���ļ�����
void find_nub(int* conut);
void find_name(int* conut);
int cpy_str(const void* e1, const void* e2);


struct s
{
	char nub[NUB];//ѧ��
	char name[NAME];//����
	char sex[SEX];//�Ա�
	char age[AGE];//����
	char phone[PHONE];//�绰
	char ip[IP];//��ַ


}ren[MAX];


enum
{
	EXIT,
	ADD,
	SHOW,
	DEL,
	FIND,
	MODIFY,
	SORT
};

int main()
{   
	
	int conut = 0;//ͳ���˵�����
	int  input = 0;//��ѡ����

	do
	{   
		caidan();//�˵�
		printf("\n ��ѡ��(0-6):\n");
		printf("��ѡ����:");
		scanf("%d", &input);

		switch (input)
		{
		case ADD://����
			addren(&conut);
			break;
		case SHOW://�鿴
			seeren(&conut);
			break;
		case DEL:
			deleteren(&conut);
			break;
		case FIND:
			findren(&conut);
			break;
		case MODIFY:
			modifyren(&conut);
			break;
		case SORT:
			sortren(&conut);
			break;
		case EXIT:
			printf("�˳�\n");
			break;
		default:
			printf("�������\n");
			break;
		}

	} while (input);

	return 0;
}

#include"TongXunLu.h"



void caidan()
{
	printf("\n***************************************************************\n");
	printf("               0-------------------------------�˳� \n");
	printf("               1-------------------------------�����ϵ��\n");
	printf("               2-------------------------------�鿴ͨѶ¼����ϵ��\n");
	printf("               3-------------------------------ɾ��ָ������\n");
	printf("               4-------------------------------����ָ������\n");
	printf("               5-------------------------------�޸�ָ���˵���Ϣ  \n");
	printf("               6-------------------------------ͨѶ¼����\n");
	printf("\n================================================================\n");
}


void TongJi(int* conut)
{
	*conut = 0;
	struct s temp = { 0 };
	FILE* pfread = fopen("ͨѶ¼.txt", "rb");
	if (pfread == NULL)
	{
		printf("%s", strerror(errno));
		return;
	}
	while (fread(&temp, sizeof(struct s), 1, pfread))
	{
		(*conut)++;
	}
	//�ر��ļ�
	fclose(pfread);
	pfread = NULL;

}

//�����ϵ�˵��ļ�
void addren(int* conut)
{
	TongJi(conut);
	if (*conut == MAX)
	{
		printf("ͨѶ¼����");

	}
	else
	{
		printf("����ѧ�ţ�");
		scanf("%s", ren[*conut].nub);
		printf("����������");
		scanf("%s", (ren[*conut].name));
		printf("�����Ա�");
		scanf("%s", (ren[*conut].sex));
		printf("�������䣺");
		scanf("%s", (ren[*conut].age));
		printf("������ϵ��ʽ��");
		scanf("%s", ren[*conut].phone);
		printf("�����ͥ��ַ��");
		scanf("%s", ren[*conut].ip);


		(*conut)++;
		//д���ļ�
		FILE* pfwrite = fopen("ͨѶ¼.txt", "wb");
		if (pfwrite == NULL)
		{
			printf("%s", strerror(errno));
		}
		//д��
		else
		{
			for (int i = 0; i < *conut; i++)
			{
				fwrite(&ren[i], sizeof(struct s), 1, pfwrite);
			}
			fclose(pfwrite); pfwrite = NULL;
			printf("\n��ӳɹ�\n");


		}

	}


}


//��ʾ��ϵ��
void seeren(int* conut)
{
	printf("\n--------------------------------------------------------------------------\n");
	printf("ѧ��\t\t����\t�Ա�\t����\t�绰\t\t��ͥ��ַ\n");
	FILE* pfshow = fopen("ͨѶ¼.txt", "rb");
	if (pfshow == NULL)
	{
		printf("%s", strerror(errno));
		return;
	}
	else
	{
		TongJi(conut);
		for (int i = 0; i < *conut; i++)
			fread(&ren[i], sizeof(struct s), 1, pfshow);

		for (int i = 0; i < *conut; i++)
		{
			printf("%-16s%-8s%-8s%-8s%-16s%-16s\n", ren[i].nub, ren[i].name, ren[i].sex, ren[i].age, ren[i].phone, ren[i].ip);
		}
		fclose(pfshow);
		pfshow = NULL;
		printf("��ȡ���\n");
	}
}


//����ѧ��ɾ��
void deleteren(int* conut)
{
	printf("������Ҫɾ���˵�ѧ�ţ�");
	char nubarr[NUB] = { 0 };
	int i = 0, j = 0;
	scanf("%s", nubarr);
	TongJi(conut);

	if (*conut == 0)
	{
		printf("ͨѶ¼Ϊ�գ�\n");
	}
	else
	{
		for (i = 0; i < *conut; i++)
		{
			if (0 == strcmp(nubarr, ren[i].nub))
			{
				for (j = i; j < *conut; j++)
				{
					ren[j] = ren[j + 1];

				}
			}
			if (j == *conut)
			{
				printf("ɾ���ɹ�\n");
				(*conut)--;
			}
			else if (i == *conut - 1)
				printf("�Ҳ�����");

		}

		//���ļ�
		FILE* pfwrite = fopen("ͨѶ¼.txt", "wb");
		if (pfwrite == NULL)
		{
			printf("%s", strerror(errno));
			return;
		}

		for (i = 0; i < *conut; i++)
		{
			fwrite(&ren[i], sizeof(struct s), 1, pfwrite);
		}

		fclose(pfwrite);
		pfwrite = NULL;
	}

}

//����
void findren(int* conut)
{
	int b = 0;
	do
	{

		printf("\n***********************MENU********************\n");
		printf("    1---------------��ѧ�Ų���.\n");
		printf("    2---------------����������.\n");
		printf("    0---------------��ȫ�˳�.\n");
		printf("\n***********************************************\n");
		printf("\n ��ѡ��(0-2):\n");
		scanf("%d", &b);
		switch (b)
		{
		case 1:find_nub(conut); break;
		case 2:find_name(conut); break;
		case 0:printf("�˳���"); break;
		default:
			printf("�������");
			break;
		}


	} while (b);

}

//��ѧ�Ų��� 
void find_nub(int* conut)
{
	printf("������ѧ�ţ�");
	char temp[20] = { 0 };
	scanf("%s", temp);
	printf("���ڲ���~\n");
	Sleep(2000);

	//���ļ�
	FILE* pfread = fopen("ͨѶ¼.txt", "rb");
	if (pfread == NULL)
	{
		printf("%s", strerror(errno));
		return;
	}
	TongJi(conut);
	int i = 0;
	for (i = 0; i < *conut; i++)
	{
		fread(&ren[i], sizeof(struct s), 1, pfread);
		if (strcmp(ren[i].nub, temp) == 0)
		{
			printf("���ҳɹ�\n��Ҫ�ҵ��˵���Ϣ��\n");
			printf("\n--------------------------------------------------------------------------\n");
			printf("ѧ��\t\t����\t�Ա�\t����\t�绰\t\t��ͥ��ַ\n");
			printf("\n--------------------------------------------------------------------------\n");
			printf("%-16s%-8s%-8s%-8s%-16s%-16s\n", ren[i].nub, ren[i].name, ren[i].sex, ren[i].age, ren[i].phone, ren[i].ip);
			break;

		}
	}
	if (i == *conut)
	{
		printf("����ʧ��\n�������ҵ��˲���ͨѶ¼��\n");
	}
	//�ر��ļ�
	fclose(pfread);
	pfread = NULL;
}


void find_name(int* conut)
{

	printf("���������֣�");
	char temp[20] = { 0 };
	scanf("%s", temp);
	printf("���ڲ���~\n");
	Sleep(2000);
	//���ļ�
	FILE* pfread = fopen("ͨѶ¼.txt", "rb");
	if (pfread == NULL)
	{
		printf("%s", strerror(errno));
		return;
	}
	TongJi(conut);
	int i = 0;
	for (i = 0; i < *conut; i++)
	{
		fread(&ren[i], sizeof(struct s), 1, pfread);
		if (strcmp(ren[i].name, temp) == 0)
		{
			printf("���ҳɹ�\n��Ҫ�ҵ��˵���Ϣ��\n");
			printf("\n--------------------------------------------------------------------------\n");
			printf("ѧ��\t\t����\t�Ա�\t����\t�绰\t\t��ͥ��ַ\n");
			printf("%-16s%-8s%-8s%-8s%-16s%-16s\n", ren[i].nub, ren[i].name, ren[i].sex, ren[i].age, ren[i].phone, ren[i].ip);
			printf("\n--------------------------------------------------------------------------\n");
			break;

		}
	}
	if (i == *conut)
	{
		printf("����ʧ��\n�������ҵ��˲���ͨѶ¼��\n");
	}
	//�ر��ļ�
	fclose(pfread);
	pfread = NULL;
}

//��ѧ������
void sortren(int* conut)
{
	TongJi(conut);
	FILE* pfread = fopen("ͨѶ¼.txt", "rb");
	if (pfread == NULL)
	{
		printf("%s", strerror(errno));
		return;
	}
	for (int i = 0; i < *conut; i++)
	{
		fread(&ren[i], sizeof(struct s), 1, pfread);
	}

	fclose(pfread);
	pfread = NULL;

	//����
	qsort(ren, *conut, sizeof(struct s), cpy_str);


	FILE* pfwrite = fopen("ͨѶ¼.txt", "wb");
	if (pfwrite == NULL)
	{
		printf("sortren_pfread:%s", strerror(errno));
		return;
	}

	for (int i = 0; i < *conut; i++)
	{
		fwrite(&ren[i], sizeof(struct s), 1, pfwrite);
	}

	fclose(pfwrite);
	pfwrite = NULL;

	printf("����ɹ�\n");

}

int cpy_str(const void* e1, const void* e2)
{
	return  strcmp((*(struct s*)e1).nub, (*(struct s*)e2).nub);

}

//�޸���Ϣ

void modifyren(int* conut)
{
	printf("�����޸��˵�ѧ�ţ�");
	char temp[20] = { 0 };
	scanf("%s", temp);

	FILE* pfread = fopen("ͨѶ¼.txt", "rb");
	if (pfread == NULL)
	{
		printf("%s", strerror(errno));
		return;
	}
	TongJi(conut);
	int i = 0;
	for (i = 0; i < *conut; i++)
	{
		fread(&ren[i], sizeof(struct s), 1, pfread);
		if (strcmp(ren[i].nub, temp) == 0)
		{
			printf("���ҳɹ�\n��Ҫ�ҵ��˵���Ϣ��\n");
			printf("\n--------------------------------------------------------------------------\n");
			printf("ѧ��\t\t����\t�Ա�\t����\t�绰\t\t��ͥ��ַ\n");
			printf("\n--------------------------------------------------------------------------\n");
			printf("%-16s%-8s%-8s%-8s%-16s%-16s\n", ren[i].nub, ren[i].name, ren[i].sex, ren[i].age, ren[i].phone, ren[i].ip);
			printf("=============================��ʼ�޸�=======================================\n");
			printf("����ѧ�ţ�");
			scanf("%s", ren[i].nub);
			printf("����������");
			scanf("%s", (ren[i].name));
			printf("�����Ա�");
			scanf("%s", (ren[i].sex));
			printf("�������䣺");
			scanf("%s", (ren[i].age));
			printf("������ϵ��ʽ��");
			scanf("%s", ren[i].phone);
			printf("�����ͥ��ַ��");
			scanf("%s", ren[i].ip);
			printf("�޸ĳɹ�\n");
			break;

		}
	}
	if (i == *conut)
	{
		printf("����ʧ��\n�������ҵ��˲���ͨѶ¼��\n");
	}
	//�ر��ļ�
	fclose(pfread);
	pfread = NULL;


	FILE* pfwrite = fopen("ͨѶ¼.txt", "wb");
	if (pfwrite == NULL)
	{
		printf("%s", strerror(errno));
		return;
	}

	for (int i = 0; i < *conut; i++)
	{
		fwrite(&ren[i], sizeof(struct s), 1, pfwrite);
	}
	fclose(pfwrite);
	pfwrite = NULL;
}